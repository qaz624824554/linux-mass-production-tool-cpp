#ifndef BUTTON_H
#define BUTTON_H

#include "common.hpp"
#include "disp_manager.hpp"
#include "input_manager.hpp"

#define BUTTON_BG_COLOR 0xff0000
#define BUTTON_TEXT_COLOR 0x00
#define BUTTON_BG_PRESSED_COLOR 0x00ff00
#define BUTTON_PERCENT_COLOR 0x0000ff;

struct Button;

typedef int (*OnDraw)(struct Button *button_ptr, const DispInfo &disp_info, const Font &font);

typedef int (*OnPress)(struct Button *button_ptr, const DispInfo &disp_info,
                       InputEventPtr input_event_ptr, const Font &font);

class Button {
public:
  char *name;
  int status;
  int font_size;
  Region region;
  OnDraw on_draw;
  OnPress on_press;
};

using ButtonPtr = Button *;

void init_button(ButtonPtr button_ptr, char *name, RegionPtr region_ptr,
                 OnDraw on_draw, OnPress on_press);

#endif