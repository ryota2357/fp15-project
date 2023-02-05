cmake_minimum_required(VERSION 3.24)

project(badapple_data
  DESCRIPTION ""
  LANGUAGES C
)

add_library(badapple STATIC
  ./src/badapple.c
  ./src/bitset128.c
)

target_compile_options(badapple PRIVATE -O2 -Wall -Wextra -Wpedantic)
target_compile_features(badapple PRIVATE c_std_17)
target_include_directories(badapple INTERFACE ./include)
