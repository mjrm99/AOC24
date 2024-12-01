#include "days.h"

#include <filesystem>
#include <string>

std::filesystem::path GetInputPath(int day, int part, bool is_example) {
  std::filesystem::path input_path = "../input/day";
  input_path += std::to_string(day);
  input_path += "-";
  input_path += std::to_string(part);
  if (is_example) {
    input_path += "e.txt";
  } else {
    input_path += "i.txt";
  }

  return input_path;
}

