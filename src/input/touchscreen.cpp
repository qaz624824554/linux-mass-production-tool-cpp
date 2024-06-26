#include "input_manager.hpp"
#include <tslib.h>

TouchScreen::TouchScreen(Input *input_ptr) {
  this->name = "touch_screen";
  // 打开设备
  if (!(this->ts = ts_setup(NULL, 0))) {
    printf("ts_setup err\r");
    throw "ts_setup error";
  }

  this->next = input_ptr->input_device_head;
  input_ptr->input_device_head = this;
}

TouchScreen::~TouchScreen() { ts_close(ts); }

int TouchScreen::get_input_event(InputEvent & input_event) {
  struct ts_sample samp;
  int ret;

  ret = ts_read(ts, &samp, 1);

  if (ret != 1 || samp.pressure == 0) {
    return 1;
  }

  input_event.x = samp.x;
  input_event.y = samp.y;
  input_event.type = INPUT_TYPE_TOUCH;
  input_event.pressure = samp.pressure;
  input_event.t_time = samp.tv;
  return 0;
}