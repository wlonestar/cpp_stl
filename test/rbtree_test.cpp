//
// Created by wjl on 2023/5/8.
//

#include "rbtree.h"
#include <gtest/gtest.h>

TEST(tree_test, tree_insert) {
  Log("==> test tree insert()");
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

  stl::vector<int> v;
  t2.in_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";

  Log("==> pass!");
}

TEST(tree_test, tree_erase) {
  Log("==> test tree erase()");
  stl::rbtree<int> t;
  stl::vector<int> v;
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.print();
  t.erase(t._root);
  t.erase(t._root->left);
  t.print();

  t.erase(0);
  t.erase(12);
  t.clear();
  EXPECT_EQ(t.size(), 0);
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.insert(1);
  t.in_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
  Log("==> pass!");
}

TEST(tree_test, tree_traverse) {
  Log("==> test tree insert()");
  stl::rbtree<int> t;
  stl::vector<int> v;

  for (int i = 1; i <= 7; i++) {
    t.insert(i);
  }
  t.print();

  EXPECT_EQ(t.size(), 7);

  t.pre_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
  v.clear();

  t.in_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
  v.clear();

  t.post_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
  v.clear();

  t.level_order(v);
  v.for_each(v.begin(), v.end(), [](const int &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
  v.clear();

  Log("==> pass!");
}
