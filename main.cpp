#include <iostream>
#include <fstream>

#include "data.h"
#include "scorer.h"


int main() {
  std::ifstream in("a_an_example.in");
  Task task;
  in >> task;
  
  Solution solution;
  solution.ingredients.insert("cheese");
  solution.ingredients.insert("mushrooms");
  solution.ingredients.insert("tomatoes");
  solution.ingredients.insert("peppers");
  
  std::cout << solution << "\n";
  std::cout << Scorer::Score(task, solution);
  return 0;
}