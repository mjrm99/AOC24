#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "days.h"

bool ValidDiff(int diff, int diff0, int minChange, int maxChange) {
  int diff_abs = std::abs(diff);
  // Same sing differences should multiply to a positive number
  return (diff * diff0 > 0) && diff_abs <= maxChange && diff_abs >= minChange;
}

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
      bool is_safe = true;
      std::vector<int> differences;

      std::string current_line = line;
      int current_number = 0;
      int prev_number = 0;
      do {
        delimiter_position = current_line.find(delimiter);
        current_number = std::stoi(current_line.substr(0, delimiter_position));
        current_line = current_line.substr(delimiter_position + delimiter.length());

        differences.emplace_back(current_number - prev_number);
        prev_number = current_number;
      } while (delimiter_position != current_line.npos);

      differences.erase(differences.begin());  // First difference is not real (prev_number starts as 0)

      bool can_tolerate = true;
      for (int i = 0; i < ssize(differences); i++) {
        if (!ValidDiff(differences[i], differences[0], kMinChange, kMaxChange)) {
          if (can_tolerate && (part == 2)) {
            can_tolerate = false;
            if (i > 0) {
              int adding_prev_diff = differences[i - 1] + differences[i];
              int adding_next_diff = differences[i] + differences[i + 1];
              if (ValidDiff(adding_prev_diff, differences[0], kMinChange, kMaxChange)) {
                differences[i - 1] = adding_prev_diff;
                differences[i] = adding_prev_diff;
              } else if (ValidDiff(adding_next_diff, differences[0], kMinChange, kMaxChange)) {
                differences[i] = adding_next_diff;
                differences[i + 1] = adding_next_diff;
              } else {
                is_safe = false;
                break;
              }
            } else {
              int adding_next_diff = differences[i] + differences[i + 1];
              if (ValidDiff(adding_next_diff, adding_next_diff, kMinChange, kMaxChange)) {
                differences[i + 1] = adding_next_diff;
                differences[i] = adding_next_diff;
              } else {
                differences[0] = differences[1];
              }
            }
          } else {
            is_safe = false;
          }
        }
      }

      if (is_safe) {
        if (!can_tolerate) {
          std::cout << line << "\n";
          for (auto c : differences) {
            std::cout << c << " ";
          }
          std::cout << "\n";
        }
        result += 1;
      }
    }
  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }

  return result;
}
