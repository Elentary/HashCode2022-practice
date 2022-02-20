#pragma once

#include "data.h"

class Scorer {
 public:
  static uint64_t Score(const Task& task, const Solution& solution) {
    uint64_t result = 0;
    for (const auto& client : task.clients) {
      bool disliked_found = false;
      for (const auto& ingredient : client.dislikes) {
        if (solution.ingredients.count(ingredient)) {
          disliked_found = true;
          break;
        }
      }

      if (disliked_found) {
        continue;
      }

      bool liked_not_found = false;
      for (const auto& ingredient : client.likes) {
        if (!solution.ingredients.count(ingredient)) {
          liked_not_found = true;
          break;
        }
      }

      if (liked_not_found) {
        continue;
      }

      ++result;
    }

    return result;
  }
};