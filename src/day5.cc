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

      if (part == 1) {
        for (int i = 0; i < ssize(pages); i++) {
          int current = pages[i];
          for (int requirement : rules[current]) {
            if (std::find(pages.begin() + i, pages.end(), requirement) != pages.end()) {
              valid = false;
              break;
            }
          }
          if (!valid) {
            break;
          }
        }

        if (valid) {
          result += pages[ssize(pages) / 2];
        }
      } else {
        for (int i = 0; i < ssize(pages); i++) {
          bool correction = false;
          int current = pages[i];
          for (int requirement : rules[current]) {
            if (std::find(pages.begin() + i, pages.end(), requirement) != pages.end()) {
              valid = false;
              correction = true;

              std::erase(pages, requirement);
              pages.emplace(pages.begin() + i, requirement);
            }
          }
          if (correction) {
            i -= 1;
          }
        }

        if (!valid) {
          result += pages[ssize(pages) / 2];
        }
      }
    }

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
