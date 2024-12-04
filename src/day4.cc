#include "days.h"

#include <fstream>

int SolveDay4(int part, bool is_example) {
  int result = 0;

  std::filesystem::path input_path = GetInputPath(4, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::string line;

    while (std::getline(input_file, line)) {
      std::string current_line = line;
    }
  }

  return result;
}
