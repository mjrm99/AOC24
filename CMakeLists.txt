cmake_minimum_required(VERSION 3.23)
cmake_policy(VERSION 3.23)
project(AOC24 VERSION 0.1.0 DESCRIPTION "Advent of code 2024")

add_executable(AOC24
  src/main.cc
  src/day_utils.cc
  src/day1.cc
  src/day2.cc
  src/day3.cc
  src/day4.cc
  src/day5.cc
  src/day6.cc
  src/day7.cc
  src/day8.cc
  src/day9.cc
)

target_compile_features(AOC24 PRIVATE cxx_std_20)

target_compile_options(AOC24 PRIVATE -Wall -Wextra -Wno-unknown-pragmas)

target_include_directories(AOC24 PRIVATE src include)
