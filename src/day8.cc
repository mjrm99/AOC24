#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "day_utils.h"

struct Pos {
  int x;
  int y;
};

Pos operator-(const Pos rhs, const Pos lhs) {
  return {rhs.x - lhs.x, rhs.y - lhs.y};
}
Pos operator+(const Pos rhs, const Pos lhs) {
  return {rhs.x + lhs.x, rhs.y + lhs.y};
}
Pos operator*(const int rhs, const Pos lhs) {
  return {lhs.x * rhs, lhs.y * rhs};
}

int GetCellIndex(Pos pos, int width, int height) {
  if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
    return pos.x + pos.y * width;
  }
  return -1;
}

int SolveDay8(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(8, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    const char empty_mark = '.';
    std::vector<bool> cells;
    std::map<char, std::vector<Pos>> antennas;
    int width;
    int height;

    int y = 0;
    std::string line;
    while (std::getline(input_file, line)) {
      width = ssize(line);
      for (int x = 0; x < width; x++) {
        if (line[x] != empty_mark) {
          antennas[line[x]].emplace_back(x, y);
        }
        cells.emplace_back(false);
      }
      y += 1;
    }
    height = y;

    for (auto& [_, current_antennas] : antennas) {
      for (int i = 0; i < ssize(current_antennas) - 1; i++) {
        for (int j = i + 1; j < ssize(current_antennas); j++) {
          Pos antenna_1 = current_antennas[i];
          Pos antenna_2 = current_antennas[j];
          Pos direction = antenna_2 - antenna_1;
          Pos candidate_1 = antenna_1 - direction;
          Pos candidate_2 = antenna_2 + direction;

          if (part == 2) {
            cells[GetCellIndex(antenna_1, width, height)] = true;
            cells[GetCellIndex(antenna_2, width, height)] = true;
          }

          int candidate_1_index = GetCellIndex(candidate_1, width, height);
          int candidate_2_index = GetCellIndex(candidate_2, width, height);
          while (candidate_1_index != -1) {
            cells[candidate_1_index] = true;
            if (part == 1) {
              break;
            }
            candidate_1 = candidate_1 - direction;
            candidate_1_index = GetCellIndex(candidate_1, width, height);
          }
          while (candidate_2_index != -1) {
            cells[candidate_2_index] = true;
            if (part == 1) {
              break;
            }
            candidate_2 = candidate_2 + direction;
            candidate_2_index = GetCellIndex(candidate_2, width, height);
          }
        }
      }
    }

    result = std::count(cells.begin(), cells.end(), true);
    // for (int i = 0; i < ssize(cells); i++) {
    //   if (cells[i]) {
    //     std::cout << "#";
    //   } else {
    //     std::cout << ".";
    //   }
    //   if (i % width == width - 1) {
    //     std::cout << "\n";
    //   }
    // }
  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
