#include <iostream>
#include <fstream>
#include <cassert>

#include "data.h"
#include "scorer.h"
#include "graph.h"

int main() {
  const std::vector<std::string> files = {
      "a_an_example.in",
      "b_basic.in",
      "c_coarse.in",
      "d_difficult.in",
      "e_elaborate.in"
  };

  const std::vector<std::string> output_files = {
      "a_an_example.out",
      "b_basic.out",
      "c_coarse.out",
      "d_difficult.out",
      "e_elaborate.out"
  };
  assert(files.size() == output_files.size());

  bool read_output_from_files = false;

  for (size_t i = 0; i < files.size(); ++i) {
    std::cout << "try solve file " << files[i] << std::endl;
    std::ifstream in(files[i]);
    Task task;
    in >> task;

    Solution solution;
    if (read_output_from_files) {
      std::ifstream in2(output_files[i]);
      in2 >> solution;
    } else {
      solution = graph_solve(task);
    }

    std::cout << files[i] << ": " << Scorer::Score(task, solution) << "\n";

    if (!read_output_from_files) {
      std::ofstream out(output_files[i]);
      out << solution;
    }
  }
  return 0;
}