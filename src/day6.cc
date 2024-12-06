#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "days.h"

struct Cell {
  int x;
  int y;
  bool wall;
  bool visited;
  std::set<int> directions;
};

struct Pos {
  int x;
  int y;
  int direction;
};

constexpr std::array<Pos, 4> directions = {Pos{0, -1, 0}, Pos{1, 0, 1}, Pos{0, 1, 2}, Pos{-1, 0, 3}};

int GetCellIndex(int x, int y, int size) {
  return x + y * size;
}

bool DoesExit(Pos guard, std::vector<Cell>& cells, std::set<int>& visited, int max_x, int max_y) {
  bool exit = false;
  while (!exit) {
    if (guard.x >= 0 && guard.x < max_x && guard.y >= 0 && guard.y < max_y) {
      Cell& current_cell = cells[GetCellIndex(guard.x, guard.y, max_x)];
      if (current_cell.directions.contains(guard.direction)) {
        return false;
      }
      current_cell.visited = true;
      current_cell.directions.insert(guard.direction);
      visited.insert(GetCellIndex(guard.x, guard.y, max_x));

      Pos next_cell = guard;
      next_cell.x += directions[guard.direction].x;
      next_cell.y += directions[guard.direction].y;

      if (next_cell.x >= 0 && next_cell.x < max_x && next_cell.y >= 0 && next_cell.y < max_y && cells[GetCellIndex(next_cell.x, next_cell.y, max_x)].wall) {
        guard.direction = (guard.direction + 1) % 4;
      } else {
        guard.x = next_cell.x;
        guard.y = next_cell.y;
      }

    } else {
      exit = true;
    }
  }
  return exit;
}

int SolveDay6(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(6, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::vector<Cell> cells;

    Pos guard;
    int max_x = -1;
    int y = 0;
    std::string line;
    while (std::getline(input_file, line)) {
      max_x = ssize(line);
      for (int x = 0; x < max_x; x++) {
        bool visited = false;
        if (line[x] == '^') {
          guard = {x, y, 0};
          visited = true;
        }
        cells.emplace_back(x, y, line[x] == '#', visited, std::set<int>{});
      }
      y += 1;
    }
    int max_y = y;

    std::set<int> visited;
    if (part == 1) {
      DoesExit(guard, cells, visited, max_x, max_y);
      result = ssize(visited);
    } else {
      std::vector<Cell> cells_copy = cells;
      DoesExit(guard, cells, visited, max_x, max_y);
      cells = cells_copy;
      for (int cell_id : visited) {
        cells_copy = cells;
        if (cell_id != GetCellIndex(guard.x, guard.y, max_x)) {
          cells_copy[cell_id].wall = true;
          std::set<int> new_visited;
          if (!DoesExit(guard, cells_copy, new_visited, max_x, max_y)) {
            result += 1;
          }
        }
      }
    }

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }
  return result;
}
