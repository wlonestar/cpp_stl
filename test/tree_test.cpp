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

TEST(tree_test, tree_test_pre_order) {
  Log("==> test tree preorder()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
//  t.root()->left->insert_left('D');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');
  t.root()->right->insert_right('G');
  t.preorder();
  Log("==> pass!");
}

TEST(tree_test, tree_test_in_order) {
  Log("==> test tree preorder()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  //  t.root()->left->insert_left('D');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');
  t.root()->right->insert_right('G');
  t.inorder();
  Log("==> pass!");
}

TEST(tree_test, tree_test_post_order) {
  Log("==> test tree preorder()");
  stl::tree<char> t;
  t.insert_root('A');
  t.root()->insert_left('B');
  t.root()->insert_right('C');
  //  t.root()->left->insert_left('D');
  t.root()->left->insert_right('E');
  t.root()->right->insert_left('F');
  t.root()->right->insert_right('G');
  t.postorder();
  Log("==> pass!");
}