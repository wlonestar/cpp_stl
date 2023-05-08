//
// Created by wjl on 2023/5/8.
//

#include "tree.h"
#include <gtest/gtest.h>
#include <map>

TEST(map_test, test_map_operation) {
  std::map<int, char> m1;
  for (int i = 0; i < 3; i++) {
    m1.insert(std::pair<int, char>(i, 'a' + i));
  }
  std::for_each(m1.begin(), m1.end(), [](const std::pair<int, char> &pair) {
    std::cout << pair.first << ":" << pair.second << "\n";
  });
  std::cout << "\n";
  m1[2] = 'o';
  std::for_each(m1.begin(), m1.end(), [](const std::pair<int, char> &pair) {
    std::cout << pair.first << ":" << pair.second << "\n";
  });
}

TEST(rb_node_test, rb_node_init) {
  stl::rbtree_node<int> t1(1);
  stl::rbtree_node<int> t2(2);
  stl::rbtree_node<int> t3(3);
  stl::rbtree_node<int> t4(4, &t1, &t2, &t3);

  t1.print();
  t2.print();
  t3.print();
  t4.print();
}

TEST(rb_node_test, rb_node_insert) {
  stl::rbtree_node<int> *n1 = new stl::rbtree_node(1);
  n1->insert(2, stl::RB_LEFT);
  n1->insert(3, stl::RB_RIGHT);
  n1->print();
}

TEST(tree_test, tree_test_init) {

}
