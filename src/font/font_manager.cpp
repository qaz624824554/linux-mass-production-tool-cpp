#include "font_manager.hpp"
#include <cstring>
#include <iostream>

Font::Font(const char *fontname, char *filepath) {
  new Freetype(this);

  FontOprPtr ptr = this->font_opr_ptr;
    while (ptr) {
    if (strcmp(ptr->name.c_str(), fontname) == 0) {
      break;
    }
    ptr = ptr->next;
  }

  if (!ptr) {
    throw "font opr not found";
  }

  std::cout << "font opr found: " << ptr->name << "---- filepath:" << filepath << std::endl;

  this->cur_font_opr_ptr = ptr;
  this->cur_font_opr_ptr->font_init(filepath);
}