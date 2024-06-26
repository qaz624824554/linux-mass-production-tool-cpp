#ifndef PAGE_H
#define PAGE_H

#include "disp_manager.hpp"
#include "input_manager.hpp"
#include <memory>
#include <string>
#include <utility>
class PageOpr {
protected:
public:
  std::string name;
  virtual void run(std::unique_ptr<DispInfo> disp_info_ptr,
           std::unique_ptr<Input> input_ptr, std::unique_ptr<Font> font_ptr) = 0;
  PageOpr *next;
};

using PageOprPtr = PageOpr *;

class Page {
private:
  PageOprPtr current_page = nullptr;

public:
  PageOprPtr page_ptr = nullptr;
  Page(const char *page_name);
  void run(std::unique_ptr<DispInfo> disp_info_ptr,
           std::unique_ptr<Input> input_ptr, std::unique_ptr<Font> font_ptr) {
    current_page->run(std::move(disp_info_ptr), std::move(input_ptr), std::move(font_ptr));
  };
};

class MainPage : public PageOpr {
private:
public:
  MainPage(Page *page_ptr);
  void run(std::unique_ptr<DispInfo> disp_info_ptr,
           std::unique_ptr<Input> input_ptr, std::unique_ptr<Font> font_ptr) override;
};

#endif