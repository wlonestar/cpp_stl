//
// Created by wjl on 2023/5/22.
//

#include "graph.h"
#include <gtest/gtest.h>

TEST(graph_test, graph_init) {
  srand(time(NULL));
  stl::graph_matrix<char, char> g;
  int n = 5, e = 10;
  generate_graph(g, n, e);
  g.print();
}

TEST(graph_test, graph_bfs) {
  srand(time(NULL));
  stl::graph_matrix<char, char> g;
  generate_example_graph(g);
  g.print();
  g.bfs(1);
  g.print();
}
