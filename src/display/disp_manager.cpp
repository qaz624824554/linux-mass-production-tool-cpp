#include "disp_manager.hpp"
#include "font_manager.hpp"
#include "framebuffer.hpp"
#include <cstdio>
#include <cstring>

DispInfo::DispInfo() {
  framebuffer_ptr = new FrameBuffer();
  framebuffer_ptr->combine_disp_info(this);
}

DispInfo::~DispInfo() {
  delete framebuffer_ptr;
}

void DispInfo::setValues(int x_res, int y_res, int bpp, unsigned char *fb_base,
                         int screen_size, int pixel_width, int line_width) {
  this->x_res = x_res;
  this->y_res = y_res;
  this->bpp = bpp;
  this->fb_base = fb_base;
  this->screen_size = screen_size;
  this->pixel_width = pixel_width;
  this->line_width = line_width;
};

int DispInfo::flush_region(RegionPtr region, unsigned char *buffer) const {
  return 0;
}

void DispInfo::put_pixel(int x, int y, unsigned int color) const {
  unsigned char *pen_8 =
      this->fb_base + x * this->pixel_width + y * this->line_width;
  unsigned short *pen_16;
  unsigned int *pen_32;

  unsigned int red, green, blue;

  pen_16 = (unsigned short *)pen_8;
  pen_32 = (unsigned int *)pen_8;

  switch (this->bpp) {
  case 8: {
    *pen_8 = color;
    break;
  }
  case 16: {
    /* 565 */
    red = (color >> 16) & 0xff;
    green = (color >> 8) & 0xff;
    blue = (color >> 0) & 0xff;
    color = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
    *pen_16 = color;
    break;
  }
  case 32: {
    // printf("绘制上去了，颜色:%d\n", color);
    *pen_32 = color;
    break;
  }
  default: {
    printf("can't surport %d bpp\n", this->bpp);
    break;
  }
  }
}

void DispInfo::draw_bitmap(FontBitMapPtr bitmap, unsigned int color) const {
  int i, j, p, q;
  int x = bitmap->region.left_top_x;
  int y = bitmap->region.left_top_y;
  int x_max = x + bitmap->region.width;
  int y_max = y + bitmap->region.height;
  int width = bitmap->region.width;
  unsigned char *buffer = bitmap->font_buffer;

  // printf("x = %d, y = %d\n", x, y);

  for (j = y, q = 0; j < y_max; j++, q++) {
    for (i = x, p = 0; i < x_max; i++, p++) {
      if (i < 0 || j < 0 || i >= this->x_res || j >= this->y_res)
        continue;

      // image[j][i] |= bitmap->buffer[q * bitmap->width + p];
      // 将非零值的像素绘制到屏幕上
      if (buffer[q * width + p]) {
        put_pixel(i, j, color);
      }
    }
  }
}
// 绘制矩形
void DispInfo::draw_region(Region region, int color) const {
  int x = region.left_top_x;
  int y = region.left_top_y;
  int width = region.width;
  int height = region.height;

  int i, j;

  for (j = y; j < y + height; j++) {
    for (i = x; i < x + width; i++) {
      put_pixel(i, j, color);
    }
  }
}

// 在一个矩形中绘制居中文字
void DispInfo::draw_text_in_region_central(char *name, Region region,
                                           int color, const Font &font) const {
  int n = strlen(name);
  FontBitMap font_bit_map;

  RegionCartesian region_cartesian;

  font.cur_font_opr_ptr->get_string_region_car(name, &region_cartesian);

  int origin_x, origin_y;
  int error;

  origin_x = region.left_top_x + (region.width - region_cartesian.width) / 2 -
             region_cartesian.left_top_x;
  origin_y = region.left_top_y + (region.height - region_cartesian.height) / 2 +
             region_cartesian.left_top_y;

  for (int i = 0; i < n; i++) {
    font_bit_map.cur_origin_x = origin_x;
    font_bit_map.cur_origin_y = origin_y;

    error = font.cur_font_opr_ptr->get_font_bitmap(name[i], &font_bit_map);
    if (error) {
      printf("get_font_bitmap err\n");
      return;
    }

    draw_bitmap(&font_bit_map, color);

    origin_x = font_bit_map.next_origin_x;
    origin_y = font_bit_map.next_origin_y;
  }
}
