#include <filesystem>

// Returns path to corresponding input file
std::filesystem::path GetInputPath(int day, int part, bool is_example);

// Gets the solution for day 1.
int SolveDay1(int part, bool is_example);
