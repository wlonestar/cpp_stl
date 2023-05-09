//
// Created by wjl on 2023/5/4.
//

#include <fstream>
#include <gtest/gtest.h>
#include "graph.h"

void init_graph(stl::graph<char, int> &graph) {

}

TEST(graph_test, graph_test_init) {
  stl::graph<char, char> g;
  int n = 4;
  int e = 8;
  for (int i = 0; i < n; i++) {
    g.insert('a' + i);
  }
  EXPECT_EQ(g.n_num, n);
  int k = 0;
  while (g.e_num < e) {
    int i = rand() % n;
    int j = rand() % n;
    if (!g.exist(i, j)) {
      int weight = rand() % e;
      g.insert('a' + k, weight, i, j);
      k++;
    }
  }
  EXPECT_EQ(g.e_num, e);
  EXPECT_EQ(g.e.size(), n);
  for (int i = 0; i < g.e.size(); i++) {
    EXPECT_EQ(g.e[i].size(), n);
  }
  g.print();
}
