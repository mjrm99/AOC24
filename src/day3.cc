#include <algorithm>
#include <fstream>
#include <string_view>

#include "days.h"

int SolveDay3(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(3, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::string line;
    constexpr std::string_view mul_token = "mul(";
    constexpr std::string_view closing_token = ")";
    constexpr std::string_view separator_token = ",";
    constexpr int kMaxInsideSize = 7;

    while (std::getline(input_file, line)) {
      std::string current_line = line;

      size_t mult_pos = current_line.npos;
      do {
        mult_pos = current_line.find((mul_token));
        if (mult_pos == current_line.npos) {
          break;
        }
        current_line = current_line.substr(mult_pos + mul_token.size());

        size_t closing_pos = current_line.find(closing_token);
        if (closing_pos != current_line.npos && closing_pos <= kMaxInsideSize) {
          std::string inside = current_line.substr(0, closing_pos);

          size_t separator_pos = inside.find(separator_token);
          if (separator_pos != inside.npos && separator_pos != 0 && separator_pos != inside.length() - 1) {
            std::string first_str = inside.substr(0, separator_pos);
            int first = -1;
            if (std::all_of(first_str.begin(), first_str.end(), ::isdigit)) {
              first = std::stoi(first_str);
            }

            std::string second_str = inside.substr(separator_pos + 1);
            int second = -1;
            if (std::all_of(second_str.begin(), second_str.end(), ::isdigit)) {
              second = std::stoi(second_str);
            }

            if (first >= 0 && second >= 0) {
              result += (first * second);
              current_line = current_line.substr(closing_pos + closing_token.length());
            }
          }
        }
      } while (mult_pos != current_line.npos);
    }
  }

  return result;
}
