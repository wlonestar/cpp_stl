//
// Created by wjl on 2023/4/24.
//

#include "tree.h"
#include <gtest/gtest.h>

TEST(tree_test, tree_test_init) {
  Log("==> test tree");
  stl::tree<int> t;
  t.insert_root(1);
  t.root()->insert_left(2);
  t.root()->insert_right(3);
  t.root()->left->insert_left(4);
  t.preorder();
  t.inorder();
  t.postorder();
  Log("==> pass!");
}
