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
  stl::graph_matrix<char, int> g;
  generate_bfs_graph(g);
  g.print();
  g.bfs(0);
  g.print();
  g.print_path(0, 7);
}

TEST(graph_test, graph_dfs) {
  srand(time(NULL));
  stl::graph_matrix<char, int> g;
  generate_dfs_graph(g);
  g.print();
  g.dfs();
  g.print();
  g.print_path(0, 6);
}
