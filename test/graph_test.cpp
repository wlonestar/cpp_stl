//
// Created by wjl on 2023/5/22.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE graph_test
#include <boost/test/included/unit_test.hpp>

#include "graph.h"

BOOST_AUTO_TEST_CASE(graph_init) {
  srand(time(NULL));
  stl::graph_matrix<char, char> g;
  int n = 5, e = 10;
  generate_graph(g, n, e);
  g.print();
}

BOOST_AUTO_TEST_CASE(graph_bfs) {
  srand(time(NULL));
  stl::graph_matrix<char, int> g;
  generate_bfs_graph(g);
  g.print();
  g.bfs(0);
  g.print();
  g.print_path(0, 7);
}

BOOST_AUTO_TEST_CASE(graph_dfs) {
  srand(time(NULL));
  stl::graph_matrix<char, int> g;
  generate_dfs_graph(g);
  g.print();
  g.dfs(0);
  g.print();
  g.print_path(0, 6);
}

BOOST_AUTO_TEST_CASE(graph_tsort) {
  stl::graph_matrix<char, int> g;
  generate_tsort_graph(g);
  g.print();
  std::stack<char> *stk = g.tsort(0);
  g.print();
}
