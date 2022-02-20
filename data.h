#pragma once

#include <vector>
#include <set>
#include <unordered_set>
#include <ostream>
#include <istream>

struct Solution {
  std::set<std::string> ingredients;

  friend std::ostream& operator<<(std::ostream& stream, const Solution& solution) {
    stream << solution.ingredients.size() << " ";
    for (const auto& ingredient : solution.ingredients) {
      stream << ingredient << " ";
    }
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Solution& solution) {
    uint64_t N;
    stream >> N;
    for (uint64_t i = 0; i < N; ++i) {
      std::string s;
      stream >> s;
      solution.ingredients.insert(std::move(s));
    }
    return stream;
  }
};

struct Task {
  struct Client {
    std::set<std::string> likes;
    std::set<std::string> dislikes;
  };

  std::vector<Client> clients;

  friend std::istream& operator>>(std::istream& stream, Task& task) {
    uint64_t N;
    stream >> N;
    for (uint64_t i = 0; i < N; ++i) {
      uint64_t M;
      Task::Client client;

      stream >> M;
      for (uint64_t j = 0; j < M; ++j) {
        std::string ingredient;
        stream >> ingredient;
        client.likes.insert(std::move(ingredient));
      }
      stream >> M;
      for (uint64_t j = 0; j < M; ++j) {
        std::string ingredient;
        stream >> ingredient;
        client.dislikes.insert(std::move(ingredient));
      }

      task.clients.push_back(std::move(client));
    }

    return stream;
  }
};
