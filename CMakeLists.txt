cmake_minimum_required(VERSION 3.10)

project(OutCheck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER /root/Tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

set(SourceDir "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(main ${src})

target_link_libraries(main freetype pthread ts m)

target_include_directories(main PRIVATE "${SourceDir}/include")