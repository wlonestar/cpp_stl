//
// Created by wjl on 2023/9/29.
//

#ifndef CPP_STL_GRAPH_H
#define CPP_STL_GRAPH_H

#pragma once

#include <vector>
#include <queue>
#include <iostream>

namespace stl {

/**
 * 
 * graph structure represented by adjacency list
 * 
 */

/**
 * arc node
 */
template<class Te>
struct arc_node {
  Te data;
  int vec;
  arc_node *next_arc;

  arc_node(const Te &e, int v, arc_node<Te> *next = nullptr)
      : data(e), vec(v), next_arc(next) {}
};

/**
 * vertex node
 */
template<class Tv, class Te>
struct vertex_node {
  Tv data;
  arc_node<Tv> *first_arc;

  vertex_node(const Tv &e, arc_node<Tv> *first = nullptr)
      : data(e), first_arc(first) {}
};

/**
 * graph
 */
template<class Tv, class Te>
class arc_graph {
private:
  int n, e;
  std::vector<vertex_node<Tv, Te>> adjlist;

private:
  std::vector<int> visited;

  void reset() {
    visited.assign(n, 0);
  }

public:

  arc_graph() : n(0), e(0) {}

  bool exists(int x, int y) {
    if (x >= n || y >= n) {
      return false;
    }
    arc_node<Te> *first = adjlist[x].first_arc;
    while (first != nullptr) {
      if (first->vec != y) {
        first = first->next_arc;   
      } else {
        return true;
      }
    }
    return false;
  }

  void insert_vertex(const Tv &data) {
    vertex_node<Tv, Te> new_vertex(data);
    adjlist.push_back(new_vertex);
    n++;
  }

  void insert_arc(const Te &data, int from, int to) {
    arc_node<Te> *new_arc = new arc_node(data, to);
    arc_node<Te> *first = adjlist[from].first_arc;
    if (first == nullptr) {
      adjlist[from].first_arc = new_arc;
    } else {
      while (first->next_arc != nullptr) {
        first = first->next_arc;
      }
      first->next_arc = new_arc;
    }
    e++;
  }

  int first_nbr(int x) {
    if (x >= n) {
      return -1;
    }
    return adjlist[x].first_arc->vec;
  }

  int next_nbr(int x, int y) {
    if (x >= n || y >= n) {
      return -1;
    }
    arc_node<Te> *y_arc = adjlist[x].first_arc;
    while (y_arc != nullptr) {
      if (y_arc->vec == y) {
        if (y_arc->next_arc != nullptr) {
          return y_arc->next_arc->vec;
        } else {
          break;
        }
      } else {
        y_arc = y_arc->next_arc;
      }
    }
    return -1;
  }

private:

  void _bfs(int v, std::vector<int> &seq) {
    seq.push_back(v);
    visited[v] = 1;
    std::queue<int> q;
    q.push(v);
    while (!q.empty()) {
      v = q.front();
      q.pop();
      for (int w = first_nbr(v); w >= 0; w = next_nbr(v, w)) {
        if (!visited[w]) {
          seq.push_back(w);
          visited[w] = 1;
          q.push(w);
        }
      }
    }
  }

  void _dfs(int v, std::vector<int> &seq) {
    seq.push_back(v);
    visited[v] = 1;
    for (int w = first_nbr(v); w >= 0; w = next_nbr(v, w)) {
      if (!visited[w]) {
        _dfs(w, seq);
      }
    }
  }

public:

  std::vector<int> bfs() {
    std::vector<int> seq;
    reset();
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        _bfs(i, seq);
      }
    }
    return seq;
  }

  std::vector<int> dfs() {
    std::vector<int> seq;
    reset();
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        _dfs(i, seq);
      }
    }
    return seq;
  }

  // for debug
  void print() {
    printf("graph(n=%d,e=%d)\n", n, e);
    printf("vertex:\n");
    for (int i = 0; i < n; i++) {
      std::cout << i << " ";
    }
    std::cout << "\n";
    printf("arc:\n");
    for (int i = 0; i < n; i++) {
      arc_node<Te> *first = adjlist[i].first_arc;
      std::cout << i << "->";
      while (first != nullptr) {
        std::cout << first->vec << "->";
        first = first->next_arc;
      }
      std::cout << "\n";
    }
  }
};

}// namespace stl

#endif
