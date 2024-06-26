#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "common.hpp"
#include <ft2build.h>
#include <string>
#include FT_FREETYPE_H
#include FT_GLYPH_H

class FontBitMap {
public:
  Region region;
  int cur_origin_x;
  int cur_origin_y;
  int next_origin_x;
  int next_origin_y;
  unsigned char *font_buffer;
};

using FontBitMapPtr = FontBitMap *;

class FontOpr {
public:
  std::string name;
  FontOpr *next;
  virtual void font_init(char *filepathname) = 0;
  virtual void set_font_size(int size) = 0;
  virtual int get_font_bitmap(unsigned int code,
                              FontBitMapPtr font_bit_map_ptr) = 0;
  virtual int get_string_region_car(char *str,
                                    RegionCartesianPtr region_cartesian_p) = 0;
};

using FontOprPtr = FontOpr *;

class Font {
private:
public:
  Font(const char *name, char *filepath);
  FontOpr *cur_font_opr_ptr = nullptr;
  FontOpr *font_opr_ptr = nullptr;
};

class Freetype : public FontOpr {
private:
  FT_Library library = nullptr;
  FT_Face face = nullptr;

public:
  Freetype(Font *font_ptr);
  ~Freetype();
  void font_init(char *filepathname) override;
  void set_font_size(int size) override;
  int get_font_bitmap(unsigned int code,
                      FontBitMapPtr font_bit_map_ptr) override;
  int get_string_region_car(char *str,
                            RegionCartesianPtr region_cartesian_p) override;
};

#endif