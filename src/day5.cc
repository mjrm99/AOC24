#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "days.h"

int SolveDay5(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(5, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::map<int, std::set<int>> rules;

    std::string line;
    while (std::getline(input_file, line)) {
      if (line == "") {
        break;
      }
      size_t separator = line.find('|');
      int prev = std::stoi(line.substr(0, separator));
      int current = std::stoi(line.substr(separator + 1));
      rules[current].insert(prev);
    }

    while (std::getline(input_file, line)) {
      std::string current_line = line;

      bool valid = true;
      std::vector<int> pages;

      size_t comma_pos = current_line.find(',');
      while (comma_pos != current_line.npos) {
        int current = std::stoi(current_line.substr(0, comma_pos));
        pages.emplace_back(current);
        current_line = current_line.substr(comma_pos + 1);
        comma_pos = current_line.find(',');
      }
      int current = std::stoi(current_line);
      pages.emplace_back(current);

      for (int i = 0; i < ssize(pages); i++) {
        int current = pages[i];
        for (int requirement : rules[current]) {
          // Required page on the line
          if (std::find(pages.begin(), pages.end(), requirement) != pages.end()) {
            // But not before the current page
            if (std::find(pages.begin(), pages.begin() + i, requirement) == pages.begin() + i) {
              valid = false;
              break;
            }
          }
        }
        if (!valid) {
          break;
        }
      }

      if (valid) {
        result += pages[ssize(pages) / 2];
      }
    }

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
