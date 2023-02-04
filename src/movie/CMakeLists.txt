cmake_minimum_required(VERSION 3.25)

project(movie_img
  DESCRIPTION ""
  LANGUAGES C
)

add_library(movie STATIC
  ./src/color.c
  ./src/frame.c
  ./src/movie.c
)

target_compile_options(movie PRIVATE -O2 -Wall -Wextra -Wpedantic)
target_compile_features(movie PRIVATE c_std_17)
target_include_directories(movie INTERFACE ./include)
