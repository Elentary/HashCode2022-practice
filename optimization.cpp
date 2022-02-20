#include <ortools/linear_solver/linear_solver.h>
#include <fstream>
#include <vector>

#include "data.h"

namespace operations_research {
void SimpleMipProgram(const Task& task) {
  // Create the mip solver with the SCIP backend.
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("BOP"));
  if (!solver) {
    LOG(WARNING) << "SCIP solver unavailable.";
    return;
  }
  
  // Variables
  std::vector<MPVariable*> variables;
  for (size_t i = 0; i < task.clients.size(); ++i) {
    variables.push_back(solver->MakeBoolVar(std::to_string(i)));
  }

  LOG(INFO) << "Number of variables = " << solver->NumVariables();
  LOG(INFO) << "Number of variables = " << solver->NumVariables();
  
  // Constraints
  for (size_t i = 0; i < task.clients.size(); ++i) {
    for (size_t j = 0; j < task.clients.size(); ++j) {
      if (i == j) {
        continue;
      }
      bool conflict = false;
      for (const auto& ingredient : task.clients[i].likes) {
        if (task.clients[j].dislikes.count(ingredient)) {
          conflict = true;
          break;
        }
      }
      
      if (conflict) {
        MPConstraint* const c0 = solver->MakeRowConstraint(
            0, 1, std::to_string(i) + "-" + std::to_string(j));
        c0->SetCoefficient(variables[i], 1);
        c0->SetCoefficient(variables[j], 1);     
      }
    }
  }

  LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

  // Objective
  MPObjective* const objective = solver->MutableObjective();
  for (const auto& var : variables) {
    objective->SetCoefficient(var, 1);
  }
  objective->SetMaximization();

  const MPSolver::ResultStatus result_status = solver->Solve();
  // Check that the problem has an optimal solution.
  if (result_status != MPSolver::OPTIMAL) {
    LOG(FATAL) << "The problem does not have an optimal solution!";
  }

  LOG(INFO) << "Solution:";
  LOG(INFO) << "Objective value = " << objective->Value();

  LOG(INFO) << "\nAdvanced usage:";
  LOG(INFO) << "Problem solved in " << solver->wall_time() << " milliseconds";
  LOG(INFO) << "Problem solved in " << solver->iterations() << " iterations";
  LOG(INFO) << "Problem solved in " << solver->nodes()
            << " branch-and-bound nodes";
}
}  // namespace operations_research

int main(int argc, char** argv) {
  std::ifstream in("e_elaborate.in");
  Task task;
  in >> task;
  operations_research::SimpleMipProgram(task);
  return EXIT_SUCCESS;
}