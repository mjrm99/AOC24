#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "days.h"

bool ValidDiff(int diff, int diff0) {
  constexpr int kMinChange = 1;
  constexpr int kMaxChange = 3;
  int diff_abs = std::abs(diff);
  return ((diff > 0) == (diff0 > 0)) && diff_abs <= kMaxChange && diff_abs >= kMinChange;
}

struct CheckSafeResult {
  bool is_safe;
  int error_index;
};

CheckSafeResult CheckSafe(std::vector<int> numbers) {
  bool is_safe = true;
  int initial_diff = numbers[1] - numbers[0];
  int i = 1;
  for (; i < ssize(numbers); i++) {
    int diff = numbers[i] - numbers[i - 1];
    if (!ValidDiff(diff, initial_diff)) {
      is_safe = false;
      break;
    }
  }
  return {is_safe, i};
}

int SolveDay2(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(2, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    constexpr std::string_view delimiter = " ";
    size_t delimiter_position;

    std::string line;
    while (std::getline(input_file, line)) {
      std::vector<int> numbers;

      std::string current_line = line;
      do {
        delimiter_position = current_line.find(delimiter);
        numbers.emplace_back(std::stoi(current_line.substr(0, delimiter_position)));
        current_line = current_line.substr(delimiter_position + delimiter.length());

      } while (delimiter_position != current_line.npos);

      auto [is_safe, error_index] = CheckSafe(numbers);

      if (part == 2) {
        std::vector<int> numbers_copy(numbers);
        // First try to check without firt element
        numbers_copy.erase(numbers_copy.begin());
        std::erase(numbers_copy, 0);
        auto [corrected, error_index] = CheckSafe(numbers_copy);
        if (corrected) {
          is_safe = corrected;
        } else {
          // Next try to check without second element
          numbers_copy = numbers;
          numbers_copy.erase(numbers_copy.begin() + 1);
          auto [corrected, _] = CheckSafe(numbers_copy);
          if (corrected) {
            is_safe = corrected;
          } else {
            // Next try without element at error_index
            numbers_copy = numbers;
            numbers_copy.erase(numbers_copy.begin() + error_index);
            auto [corrected, _] = CheckSafe(numbers_copy);
            if (corrected) {
              is_safe = corrected;
            } else {
              if (error_index > 0) {
                // Next try without element before error_index
                numbers_copy = numbers;
                numbers_copy.erase(numbers_copy.begin() + error_index + 1);
                auto [corrected, _] = CheckSafe(numbers_copy);
                if (corrected) {
                  is_safe = corrected;
                }
              }
            }
          }
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
