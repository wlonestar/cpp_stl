//
// Created by wjl on 2023/4/24.
//

#include "tree.h"
#include <gtest/gtest.h>

TEST(tree_test, test_tree_pre_order) {
  Log("==> test tree pre_order()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');

  stl::list<char> l;
  auto lambda = [&l](const char &value) {
    l.push_back(value);
  };
  t.pre_order(lambda);
  stl::list<char> l1{'A', 'B', 'E', 'C', 'F'};
  EXPECT_EQ(l1, l);

  Log("==> pass!");
}

TEST(tree_test, test_tree_in_order) {
  Log("==> test tree in_order()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');

  stl::list<char> l;
  auto lambda = [&l](const char &value) {
    l.push_back(value);
  };
  t.in_order(lambda);
  stl::list<char> l1{'B', 'E', 'A', 'F', 'C'};
  EXPECT_EQ(l1, l);

  Log("==> pass!");
}

TEST(tree_test, test_tree_post_order) {
  Log("==> test tree post_order()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');

  stl::list<char> l;
  auto lambda = [&l](const char &value) {
    l.push_back(value);
  };
  t.post_order(lambda);
  stl::list<char> l1{'E', 'B', 'F', 'C', 'A'};
  EXPECT_EQ(l1, l);

  Log("==> pass!");
}

TEST(tree_test, test_tree_level_order) {
  Log("==> test tree level_order()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');

  stl::list<char> l;
  auto lambda = [&l](const char &value) {
    l.push_back(value);
  };
  t.level_order(lambda);
  stl::list<char> l1{'A', 'B', 'C', 'E', 'F'};
  EXPECT_EQ(l1, l);

  t.level_order();
  Log("==> pass!");
}

TEST(bool_test, bool_test_struct) {
  struct node {
    int data;
    node *left;
    node *right;
    node *parent;
  };

  node *p1 = new node{1, nullptr, nullptr, nullptr};
  node *p2 = new node{1, nullptr, nullptr, nullptr};
  node *p3 = new node{1, p1, p2, nullptr};
  std::cout << (!!(p3->left)) << "\n";
  std::cout << (p3->left != nullptr) << "\n";
}
