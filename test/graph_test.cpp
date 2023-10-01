#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE graph_test
#include <boost/test/included/unit_test.hpp>

#include <graph.h>

BOOST_AUTO_TEST_CASE(simple_init) {
  srand(time(NULL));

  stl::graph<int, int> g;
  for (int i = 1; i < 6; i++) {
    g.insert_vertex(i);
  }
  g.insert_arc( 1, 1-1, 2-1);
  g.insert_arc( 2, 1-1, 5-1);
  g.insert_arc( 3, 2-1, 1-1);
  g.insert_arc( 4, 2-1, 5-1);
  g.insert_arc( 5, 2-1, 3-1);
  g.insert_arc( 6, 2-1, 4-1);
  g.insert_arc( 7, 3-1, 2-1);
  g.insert_arc( 8, 3-1, 4-1);
  g.insert_arc( 9, 4-1, 2-1);
  g.insert_arc(10, 4-1, 5-1);
  g.insert_arc(11, 4-1, 3-1);
  g.insert_arc(12, 5-1, 4-1);
  g.insert_arc(13, 5-1, 1-1);
  g.insert_arc(14, 5-1, 2-1);

  g.print();

  auto res1 = g.bfs();
  for (int &elem : res1) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
  
  auto res2 = g.dfs();
  for (int &elem : res2) {
    std::cout << elem << " ";
  }
  std::cout << "\n";

}
