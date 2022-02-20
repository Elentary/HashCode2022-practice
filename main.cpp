#include <iostream>
#include <fstream>

#include "data.h"
#include "scorer.h"


int main() {
  const std::vector<std::string> files = {
   "a_an_example.in",
   "b_basic.in",
   "c_coarse.in",
   "d_difficult.in",
   "e_elaborate.in"
  };
  
  for (const auto& file : files) {
    std::ifstream in(file);
    Task task;
    in >> task;

    Solution solution;

    std::ofstream out(file.substr(0, file.size() - 3) + ".out");
    out << solution;
    std::cout << file << ": " << Scorer::Score(task, solution) << "\n";
  }
  return 0;
}