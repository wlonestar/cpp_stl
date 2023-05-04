//
// Created by wjl on 2023/5/4.
//

#include "graph.h"
#include <fstream>
#include <gtest/gtest.h>

void init_graph(stl::graph<char, int> &graph) {
  int n = 5;
  int e = 10;
  for (int i = 0; i < n; i++) {
    graph.insert('a' + i);
  }
  int k = 0;
  while (graph.e_num < e) {
    int i = rand() % n;
    int j = rand() % n;
    if (i != j) {
      int weight = rand() % 100;
      graph.insert(k++, weight, i, j);
    }
  }
}

TEST(graph_test, graph_test_init) {
  stl::graph<char, int> g;
  init_graph(g);
  std::cout << g;
//  g.bfs(0);
}
