#include "disp_manager.hpp"
#include <linux/fb.h>

#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

class FrameBuffer {
  int fd_fb;
  struct fb_var_screeninfo fb_info;
  unsigned char *fb_base;
  int screen_size;
  int pixel_width;
  int line_width;

public:
  FrameBuffer();
  ~FrameBuffer();
  void combine_disp_info(DispInfoPtr p);
};

using FrameBufferPtr = FrameBuffer *;

#endif