#include "disp_manager.hpp"
#include "font_manager.hpp"
#include "input_manager.hpp"
#include "page_manager.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "need 2 arguments\n";
    return -1;
  }

  try {
    auto disp_info_ptr = std::make_unique<DispInfo>();

    std::cout << "初始化显示系统完成" << std::endl;

    auto input_ptr = std::make_unique<Input>();

    std::cout << "初始化输入系统完成" << std::endl;

    auto font_ptr = std::make_unique<Font>("freetype", argv[1]);

    std::cout << "初始化文字系统完成" << std::endl;

    auto page_ptr = std::make_unique<Page>("main");

    // 所有权转移
    page_ptr->run(std::move(disp_info_ptr), std::move(input_ptr), std::move(font_ptr));

    std::cout << "初始化页面系统完成" << std::endl;

  } catch (const char *str) {
    std::cout << str << std::endl;
    return EXIT_FAILURE;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cout << "unknown error" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}