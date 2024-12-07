#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include "day_utils.h"

struct Coord {
  int x;
  int y;
};

constexpr std::array<Coord, 8> directions = {Coord{1, 0}, Coord{1, 1}, Coord{0, 1}, Coord{-1, 1}, Coord{-1, 0}, Coord{-1, -1}, Coord{0, -1}, Coord{1, -1}};

int CheckDirection(std::vector<std::string> grid, Coord coord, int direction_index, std::string pattern) {
  Coord direction = directions[direction_index];
  int minLength = (ssize(pattern) - 1);

  Coord final_coord = {coord.x + minLength * direction.x, coord.y + minLength * direction.y};

  if (final_coord.x >= 0 && final_coord.x < ssize(grid[0])) {
    if (final_coord.y >= 0 && final_coord.y < ssize(grid)) {
      for (int i = 1; i < ssize(pattern); i++) {
        Coord current_coord = {coord.x + i * direction.x, coord.y + i * direction.y};
        if (grid[current_coord.y][current_coord.x] != pattern[i]) {
          return 0;
        }
      }
      return 1;
    }
  }

  return 0;
}

int CheckX(std::vector<std::string> grid, Coord coord) {
  if (coord.x - 1 >= 0 && coord.x + 1 < ssize(grid[0])) {
    if (coord.y - 1 >= 0 && coord.y + 1 < ssize(grid)) {
      char top_left = grid[coord.y - 1][coord.x - 1];
      char top_right = grid[coord.y - 1][coord.x + 1];
      char bottom_left = grid[coord.y + 1][coord.x - 1];
      char bottom_right = grid[coord.y + 1][coord.x + 1];

      if ((top_left == top_right && bottom_left == bottom_right) || (top_left == bottom_left && top_right == bottom_right)) {
        if ((top_left == 'S' && bottom_right == 'M') || (top_left == 'M' && bottom_right == 'S')) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int SolveDay4(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(4, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(input_file, line)) {
      lines.emplace_back(line);
    }

    if (part == 1) {
      const std::string pattern = "XMAS";
      const char start_char = pattern[0];
      for (int y = 0; y < ssize(lines); y++) {
        std::string current_line = lines[y];
        size_t x = current_line.find(start_char);
        while (x != current_line.npos) {
          current_line.replace(x, 1, 1, '.');
          for (int i = 0; i < ssize(directions); i++) {
            result += CheckDirection(lines, Coord(x, y), i, pattern);
          }
          x = current_line.find(start_char);
        }
      }
    } else {
      const char target_char = 'A';
      for (int y = 0; y < ssize(lines); y++) {
        std::string current_line = lines[y];
        size_t x = current_line.find(target_char);
        while (x != current_line.npos) {
          current_line.replace(x, 1, 1, '.');
          result += CheckX(lines, Coord(x, y));
          x = current_line.find(target_char);
        }
      }
    }
  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
