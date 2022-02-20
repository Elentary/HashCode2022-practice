#pragma once

#include <algorithm>
#include <random>
#include <queue>
#include <vector>

#include "data.h"

using namespace std;

using edges = std::vector<std::vector<int> >;

int get_leaves(const edges &e, unordered_set<int> &s) {
    int n = e.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (s.find(i) != s.end()) {
            continue;
        }
        int cnt = 0;
        int last = -1;
        for (int j : e[i]) {
            if (s.find(j) == s.end()) {
                last = j;
                ++cnt;
            }
        }
        if (cnt == 1) {
            s.insert(last);
            ++res;
        }
    }
    return res;
}

bool is_isolated(const edges &e, const unordered_set<int> &s) {
    int n = e.size();
    for (int i = 0; i < n; ++i) {
        if (s.find(i) != s.end()) {
            continue;
        }
        for (int j : e[i]) {
            if (s.find(j) == s.end()) {
                return false;
            }
        }
    }
    return true;
}

int random_from_vector(const vector<int> &v, mt19937 &r) {
    uniform_int_distribution<int> dist(0, v.size() - 1);
    int i = dist(r);
    return v[i];
}

int get_vertex(const edges &e, const unordered_set<int> &s, mt19937 &r) {
    int n = e.size();
    vector<int> good;
    vector<int> bad;
    for (int i = 0; i < n; ++i) {
        for (int j : e[i]) {
            if (s.find(j) == s.end()) {
                if (s.find(i) != s.end()) {
                    good.push_back(i);
                } else {
                    bad.push_back(i);
                }
                break;
            }
        }
    }
    if (good.size() > 0) {
        return random_from_vector(good, r);
    }
    return random_from_vector(bad, r);
}

int dijkstra(const edges &e, const unordered_set<int> &s, int start, mt19937& r) {
    int n = e.size();
    int max_d = 0;
    vector<int> d(n, -1);
    queue<int> q;
    d[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i : e[v]) {
            if (s.find(i) == s.end() && d[i] == -1) {
                d[i] = d[v] + 1;
                max_d = d[i];
                q.push(i);
            }
        }
    }
    if (max_d > 1) {
        vector<int> good;
        for (int i = 0; i < n; ++i) {
            if (d[i] + 1 == max_d) {
                good.push_back(i);
            }
        }
        // TODO: check connected components
        // TODO: check degree
        return random_from_vector(good, r);
    }
    vector<int> good;
    for (int i = 0; i < n; ++i) {
        if (d[i] == 1) {
            good.push_back(i);
        }
    }
    // TODO: check degree
    return random_from_vector(good, r);
}

Solution graph_solve(const Task &task) {
    int n = task.clients.size();
    auto c = task.clients;
    edges e(n);
    mt19937 r;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int inter = 0;
            for (auto like : c[i].likes) {
                if (c[j].dislikes.find(like) != c[j].dislikes.end()) {
                    inter = 1;
                    break;
                }
            }
            for (auto dislike : c[i].dislikes) {
                if (c[j].likes.find(dislike) != c[j].likes.end()) {
                    inter = 1;
                    break;
                }
            }
            if (inter) {
                e[i].push_back(j);
                e[j].push_back(i);
            }
        }
    }
    unordered_set<int> s;
    get_leaves(e, s);
    if (s.size() == 0 && !is_isolated(e, s)) {      
        vector<int> good;
        for (int i = 0; i < n; ++i) {
            if (e[i].size() > 0) {
                good.push_back(i);
            }
        }
        s.insert(random_from_vector(good, r));
    }
    int iter = 0;
    while (!is_isolated(e, s)) {
        int res = get_leaves(e, s);
        if (res > 0) {
            continue;
        }
        int v = get_vertex(e, s, r);
        if (s.find(v) == s.end()) {
            s.insert(v);
            continue;
        }
        v = dijkstra(e, s, v, r);
        s.insert(v);
    }
    Solution res;
    for (int i = 0; i < n; ++i) {
        if (s.find(i) == s.end()) {
            for (string j : c[i].likes) {
                res.ingredients.insert(j);
            }
        }
    }
    return res;
}