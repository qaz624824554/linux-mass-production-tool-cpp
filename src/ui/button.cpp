#include "ui.hpp"

static int on_default_draw(Button *button_ptr,
                           const DispInfo &disp_info,const Font &font) {
  disp_info.draw_region(button_ptr->region, BUTTON_BG_COLOR);

  font.cur_font_opr_ptr->set_font_size(button_ptr->font_size);

  disp_info.draw_text_in_region_central(button_ptr->name, button_ptr->region,
                              BUTTON_TEXT_COLOR, font);

  disp_info.flush_region(&button_ptr->region, disp_info.fb_base);

  return 0;
};

static int on_default_press(ButtonPtr button_ptr, const DispInfo &disp_info,
                            InputEventPtr input_event_ptr, const Font &font) {
  int bg_color = BUTTON_BG_COLOR;
  button_ptr->status = !button_ptr->status;

  if (button_ptr->status) {
    bg_color = BUTTON_BG_PRESSED_COLOR;
  }

  disp_info.draw_region(button_ptr->region, bg_color);

  disp_info.draw_text_in_region_central(button_ptr->name, button_ptr->region,
                              BUTTON_TEXT_COLOR, font);

  disp_info.flush_region(&button_ptr->region, disp_info.fb_base);

  return 0;
};

void init_button(ButtonPtr button_ptr, char *name, RegionPtr region_ptr,
                 OnDraw on_draw, OnPress on_press) {

  button_ptr->name = name;
  button_ptr->status = 0;
  if (region_ptr) {
    button_ptr->region = *region_ptr;
  }
  button_ptr->on_draw = on_draw ? on_draw : on_default_draw;
  button_ptr->on_press = on_press ? on_press : on_default_press;
}