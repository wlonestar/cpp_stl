//
// Created by wjl on 2023/5/8.
//

#include "tree.h"
#include <gtest/gtest.h>

TEST(tree_test, node_functions) {
  Log("==> test node functions...");
  stl::rbtree_node<int> *n = stl::generate_full_tree();
  stl::rbtree_node<int> *min, *max;
  min = stl::rb_min_child(n);
  EXPECT_EQ(min->value, 1);
  max = stl::rb_max_child(n);
  EXPECT_EQ(max->value, 7);
  min = stl::rb_min_child(n->left);
  EXPECT_EQ(min->value, 1);
  max = stl::rb_max_child(n->left);
  EXPECT_EQ(max->value, 3);
  min = stl::rb_min_child(n->right);
  EXPECT_EQ(min->value, 5);
  max = stl::rb_max_child(n->right);
  EXPECT_EQ(max->value, 7);
  Log("==> pass!");
}

TEST(tree_test, node_traverses) {
  Log("==> test node traverses...");
  stl::rbtree_node<int> *n = stl::generate_full_tree();
  stl::vector<int> v, ret;
  stl::rb_pre_order(n, v);
  ret.assign({4, 2, 1, 3, 6, 5, 7});
  EXPECT_EQ(v, ret);
  v.clear();
  stl::rb_in_order(n, v);
  ret.assign({1, 2, 3, 4, 5, 6, 7});
  EXPECT_EQ(v, ret);
  v.clear();
  stl::rb_post_order(n, v);
  ret.assign({1, 3, 2, 5, 7, 6, 4});
  EXPECT_EQ(v, ret);
  v.clear();
  stl::rb_level_order(n, v);
  ret.assign({4, 2, 6, 1, 3, 5, 7});
  EXPECT_EQ(v, ret);
  v.clear();
  Log("==> pass!");
}

TEST(tree_test, tree_insert) {
  Log("==> test tree insert...");

  stl::rbtree<int> t;
  t.insert(1);
  t.print();

  Log("==> pass!");
}
