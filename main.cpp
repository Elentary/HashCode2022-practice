#include <iostream>
#include <fstream>
#include <cassert>

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

  const std::vector<std::string> output_files = {
      "a_an_example.in",
      "b_basic.in",
      "c_coarse.in",
      "d_difficult.in",
      "e_elaborate.in"
  };
  assert(files.size() == output_files.size());

  bool read_output_from_files = false;

  for (size_t i = 0; i < files.size(); ++i) {
    std::ifstream in(files[i]);
    Task task;
    in >> task;

    Solution solution;
    if (read_output_from_files) {
      std::ifstream in2(output_files[i]);
      in2 >> solution;
    }

    std::cout << files[i] << ": " << Scorer::Score(task, solution) << "\n";

    if (!read_output_from_files) {
      std::ofstream out(files[i].substr(0, files[i].size() - 3) + ".out");
      out << solution;
    }
  }
  return 0;
}