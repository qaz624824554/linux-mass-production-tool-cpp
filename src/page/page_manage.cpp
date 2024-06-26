#include "page_manager.hpp"
#include <iostream>

Page::Page(const char *page_name) {
  new MainPage(this);
  
  this->current_page = this->page_ptr;

  while (this->current_page) {
    if ((strcmp(page_name, this->current_page->name.c_str())) == 0) {
      std::cout << this->current_page->name << "页面匹配成功" << std::endl;
      return;
    }
    this->current_page = this->current_page->next;
  }

  throw "页面匹配失败";
}