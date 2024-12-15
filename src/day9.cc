#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "day_utils.h"

struct File {
  int id;
  int size;
};

long CalculateChecksum(std::vector<int> drive) {
  long checksum = 0;
  for (int i = 0; i < ssize(drive); i++) {
    if (drive[i] != -1) {
      checksum += drive[i] * i;
    }
  }

  return checksum;
}

long SolveDay9(int part, bool is_example) {
  long result = 0;
  std::filesystem::path input_path = GetInputPath(9, part, is_example);
  std::ifstream input_file(input_path);
  if (input_file.is_open()) {
    std::vector<int> drive;
    std::deque<File> files;

    std::string line;
    std::getline(input_file, line);

    bool is_file = true;
    int id = 0;
    for (char& digit_character : line) {
      int current_digit = digit_character - '0';  // Hate that stoi doesn't work with chars...
      if (is_file) {
        if (part == 2) {
          files.emplace_back(id, current_digit);
        } else {
          drive.insert(drive.end(), current_digit, id);
        }
        id += 1;
      } else {
        if (part == 2) {
          files.emplace_back(-1, current_digit);
        } else {
          drive.insert(drive.end(), current_digit, -1);
        }
      }
      is_file = !is_file;
    }

    if (part == 1) {
      int front = 0;
      for (int back = ssize(drive) - 1; back >= 0; back--) {
        while (front < back && drive[front] != -1) {
          front += 1;
        }
        if (front == ssize(drive) || front >= back) {
          break;
        }
        if (drive[back] != -1) {
          drive[front] = drive[back];
          drive[back] = -1;
          front += 1;
        }
      }
    } else {
      int front = 0;
      for (int back = ssize(files) - 1; back >= 0; back--) {
        while (front < back && files[front].id != -1) {
          front += 1;
        }
        if (front == ssize(files) || front >= back) {
          break;
        }

        if (files[back].id != -1) {
          int current = front;
          while (current < back && (files[current].id != -1 || files[current].size < files[back].size)) {
            current += 1;
          }
          if (current < back) {
            if (files[current].size == files[back].size) {
              files[current].id = files[back].id;
              files[back].id = -1;
            } else {
              int size_diff = files[current].size - files[back].size;
              files[current] = files[back];
              files[back].id = -1;
              files.insert(files.begin() + current + 1, File(-1, size_diff));
            }
          }
        }
      }

      for (auto [id, size] : files){
        drive.insert(drive.end(), size, id);
      }
    }

    result = CalculateChecksum(drive);

  } else {
    std::cerr << "Failed to open file: " << input_path << "\n";
  }

  return result;
}
