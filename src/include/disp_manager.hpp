#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

#include "common.hpp"
#include "font_manager.hpp"

class FrameBuffer;

class DispInfo {
private:
public:
  int x_res;
  int y_res;
  int bpp;
  unsigned char *fb_base;
  int screen_size;
  int pixel_width; // 像素宽度，单位字节，bpp为32，宽度就为4字节
  int line_width;
  FrameBuffer *framebuffer_ptr;
  DispInfo();
  ~DispInfo();
  void setValues(int x_res, int y_res, int bpp, unsigned char *fb_base,
                 int screen_size, int pixel_width, int line_width);
  int flush_region(RegionPtr region, unsigned char *buffer) const;
  void put_pixel(int x, int y, unsigned int color) const;
  int display_init(void);
  int display_exit(void);
  void draw_bitmap(FontBitMapPtr bitmap, unsigned int color) const;
  void draw_region (Region region, int color) const;
  void draw_text_in_region_central(char *name, Region region, int color, const Font &font) const;
};

using DispInfoPtr = DispInfo *;

#endif