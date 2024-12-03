#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "days.h"

int SolveDay2(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(2, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    constexpr int kMinChange = 1;
    constexpr int kMaxChange = 3;
    constexpr std::string_view delimiter = " ";
    size_t delimiter_position;

    std::string line;
    while (std::getline(input_file, line)) {
      bool is_increasing = false;
      bool is_safe = true;
      int previous_number = -1;
      int current_number = -1;

      std::string current_line = line;

      delimiter_position = current_line.find(delimiter);
      previous_number = std::stoi(current_line.substr(0, delimiter_position));
      current_line = current_line.substr(delimiter_position + delimiter.length());

      delimiter_position = current_line.find(delimiter);
      current_number = std::stoi(current_line.substr(0, delimiter_position));
      current_line = current_line.substr(delimiter_position + delimiter.length());

      int diference = current_number - previous_number;
      if (diference > 0) {
        is_increasing = true;
      } else if (diference < 0) {
        is_increasing = false;
      } else {
        is_safe = false;
      }
      diference = std::abs(diference);
      if (diference < kMinChange || diference > kMaxChange) {
        is_safe = false;
      }

      while (delimiter_position != current_line.npos) {
        previous_number = current_number;

        delimiter_position = current_line.find(delimiter);
        current_number = std::stoi(current_line.substr(0, delimiter_position));
        current_line = current_line.substr(delimiter_position + delimiter.length());

        diference = current_number - previous_number;
        if ((is_increasing && diference < 0) || (!is_increasing && diference > 0)) {
          is_safe = false;
          break;
        }
        diference = std::abs(diference);
        if (diference < kMinChange || diference > kMaxChange) {
          is_safe = false;
          break;
        }
      }
      if (is_safe) {
        result += 1;
      }
    }

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }

  return result;
}
