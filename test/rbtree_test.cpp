//
// Created by wjl on 2023/5/8.
//

#include "rbtree.h"
#include <gtest/gtest.h>

TEST(tree_test, tree_insert) {
  Log("==> test tree insert...");
  stl::rbtree<int> t1;
  for (int i = 0; i < 18; i++) {
    t1.insert(i);
  }
  t1.print();
  stl::rbtree<int, std::greater<int>> t2;
  for (int i = 0; i < 12; i++) {
    t2.insert(i);
  }
  t2.print();
  t2.in_order();
  Log("==> pass!");
}

TEST(tree_test, tree_erase) {
  Log("==> test tree erase...");
  stl::rbtree<int> t;
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.print();
  t.erase(t._root);
  t.erase(t._root->left);
  t.print();
  t.in_order();
  t.erase(0);
  t.in_order();
  t.erase(12);
  t.in_order();
  t.clear();
  EXPECT_EQ(t.size(), 0);
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.in_order();
  t.insert(1);
  t.in_order();
  Log("==> pass!");
}

TEST(tree_test, tree_traverse) {
  Log("==> test tree insert...");
  stl::rbtree<int> t;
  t.pre_order();
  t.in_order();
  t.post_order();
  t.level_order();
  for (int i = 1; i <= 7; i++) {
    t.insert(i);
  }
  t.print();
  EXPECT_EQ(t.size(), 7);
  t.pre_order();
  t.in_order();
  t.post_order();
  t.level_order();
  Log("==> pass!");
}
