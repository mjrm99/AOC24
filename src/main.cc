#include <cstdio>
#include <iostream>
#include <string>

#include "days.h"

int main(int argc, char *argv[]) {
  bool exit_status = true;

  int day = 2;
  int part = 2;
  int is_example = false;

  switch (argc) {
    case 4: {
      std::string value = std::string(argv[3]);
      if (value == "True" || value == "true" || value == "T" || value == "t" || value == "1") {
        is_example = true;
      } else if (value == "False" || value == "false" || value == "F" || value == "f" || value == "0") {
        is_example = false;
      } else{
        std::cerr << "Invalid is_example value. \n";
      }
    }
      [[fallthrough]];
    case 3:
      part = std::stoi(argv[2]);
      [[fallthrough]];
    case 2:
      day = std::stoi(argv[1]);
      [[fallthrough]];
    case 1:
      break;
    default:
      std::cerr << "Only 0, 1, 2 or 3 arguments supported. \n";
  }

  int result = 0;

  std::cout << "Solving day " << day << ":\n\n";
  switch (day) {
    case 1:
      result = SolveDay1(part, is_example);
      break;
    case 2:
      result = SolveDay2(part, is_example);
      break;
    default:
      std::cerr << "Invalid day selected. \n";
  }

  std::cout << result << "\n";

  return exit_status;
}
