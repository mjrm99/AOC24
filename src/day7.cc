#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

#include "day_utils.h"

struct Solution {
  long total;
  int last_op;
  int lenght;
  std::vector<int> operands;
};

long SolveDay7(int part, bool is_example) {
  long result = 0;

  std::filesystem::path input_path = GetInputPath(7, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    constexpr std::string_view separator = " ";
    constexpr std::string_view start_mark = ": ";

    std::string line;
    while (std::getline(input_file, line)) {
      size_t start_mark_pos = line.find(start_mark);
      long target = std::stol(line.substr(0, start_mark_pos));
      std::string current_line = line.substr(start_mark_pos + ssize(start_mark));

      std::vector<long> numbers;
      size_t separator_pos = current_line.find(separator);
      while (separator_pos != current_line.npos) {
        numbers.emplace_back(std::stol(current_line.substr(0, separator_pos)));
        current_line = current_line.substr(separator_pos + separator.size());
        separator_pos = current_line.find(separator);
      }
      numbers.emplace_back(std::stol(current_line));

      std::stack<Solution> solutions;
      solutions.emplace(numbers[0], 0, 1);
      while (ssize(solutions) > 0) {
        Solution current_solution = solutions.top();
        solutions.pop();

        if (current_solution.last_op < part) {
          // Next time check other operand
          solutions.emplace(current_solution.total, current_solution.last_op + 1, current_solution.lenght);
        }

        long new_total = -1;
        if (current_solution.last_op == 0) {
          new_total = current_solution.total + numbers[current_solution.lenght];
        } else if (current_solution.last_op == 1) {
          new_total = current_solution.total * numbers[current_solution.lenght];
        } else {
          new_total = std::stol(std::to_string(current_solution.total) + std::to_string(numbers[current_solution.lenght]));
        }

        // New total can't be lower than current total (long multiplication over/under flow)
        // if (new_total < current_solution.total) {
        // break;
        //}

        if (new_total == target && current_solution.lenght + 1 == ssize(numbers)) {
          result += target;
          break;
        } else if (new_total <= target && current_solution.lenght + 1 < ssize(numbers)) {
          solutions.emplace(new_total, 0, current_solution.lenght + 1, current_solution.operands);
          solutions.top().operands.emplace_back(current_solution.last_op);
        }
      }
    }

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
