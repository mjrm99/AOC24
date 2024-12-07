#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "day_utils.h"

int SolveDay1(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(1, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::vector<int> firsts;
    std::vector<int> seconds;

    std::string line;
    while (std::getline(input_file, line)) {
      std::string delimiter = "   ";
      size_t pos = line.find(delimiter);
      if (pos != line.npos) {
        firsts.emplace_back(std::stoi(line.substr(0, pos)));
        seconds.emplace_back(std::stoi(line.substr(pos + delimiter.size(), line.npos)));
      }
    }

    if (part == 1) {
      std::sort(firsts.begin(), firsts.end());
      std::sort(seconds.begin(), seconds.end());
      for (int i = 0; i < ssize(firsts); i++) {
        result += std::abs(firsts[i] - seconds[i]);
      }
    } else if (part == 2) {
      std::map<int, int> seconds_count;
      for (const int& number : seconds) {
        if (seconds_count.contains(number)) {
          seconds_count[number] += 1;
        } else {
          seconds_count.emplace(number, 1);
        }
      }

      for (const int& number : firsts) {
        if (seconds_count.contains(number)) {
          result += number * seconds_count[number];
        }
      }

    } else {
      std::cerr << "Invalid part: " << part << "\n";
    }
  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }

  return result;
}
