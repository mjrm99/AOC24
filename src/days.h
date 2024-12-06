#include <filesystem>

// TODO: Replace with per-day header to avoid recompile of all files every new day

// Returns path to corresponding input file
std::filesystem::path GetInputPath(int day, int part, bool is_example);

// Gets the solution for day 1.
int SolveDay1(int part, bool is_example);

// Gets the solution for day 2.
int SolveDay2(int part, bool is_example);

// Gets the solution for day 3.
int SolveDay3(int part, bool is_example);

// Gets the solution for day 4.
int SolveDay4(int part, bool is_example);

// Gets the solution for day 5.
int SolveDay5(int part, bool is_example);

// Gets the solution for day 6.
int SolveDay6(int part, bool is_example);
