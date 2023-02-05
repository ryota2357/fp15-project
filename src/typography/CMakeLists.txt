cmake_minimum_required(VERSION 3.24)

project(typography
  DESCRIPTION ""
  LANGUAGES C
)

add_library(typography STATIC
  ./src/font_bitmap.c
)

target_compile_options(typography PRIVATE -O2 -Wall -Wextra -Wpedantic)
target_compile_features(typography PRIVATE c_std_17)
target_include_directories(typography INTERFACE ./include)
