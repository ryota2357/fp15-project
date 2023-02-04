cmake_minimum_required(VERSION 3.25)

project(fp_movie
  DESCRIPTION "Fundamental Programming 15 (comprehensive practice)"
  LANGUAGES C
)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR
    "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. "
  )
endif()

add_subdirectory(./movie)
add_subdirectory(./badapple)
add_executable(main main.c)

target_link_libraries(main movie badapple)
target_compile_options(main PRIVATE -O2 -Wall -Wextra -Wpedantic)
target_compile_features(main PRIVATE c_std_17)
