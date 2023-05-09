//
// Created by wjl on 2023/5/8.
//

#include <gtest/gtest.h>
#include "tree.h"

TEST(tree_test, rb_node_init) {
  stl::rbtree_node<int> t1(1);
  stl::rbtree_node<int> t2(2);
  stl::rbtree_node<int> t3(3);
  stl::rbtree_node<int> t4(4, &t1, &t2, &t3);

  t1.print();
  t2.print();
  t3.print();
  t4.print();
}

TEST(tree_test, rb_node_insert) {
  stl::rbtree_node<int> *n1 = new stl::rbtree_node(1);
  n1->insert(2, stl::RB_LEFT);
  n1->insert(3, stl::RB_RIGHT);
  n1->print();
}

TEST(tree_test, rb_node_incredecre) {
  stl::rbtree_node<char> *n1 = new stl::rbtree_node('b');
  n1->insert('a', stl::RB_LEFT);
  n1->insert('c', stl::RB_RIGHT);
  stl::rbtree_node<char> *n2 = new stl::rbtree_node('f');
  n2->insert('e', stl::RB_LEFT);
  n2->insert('g', stl::RB_RIGHT);
  stl::rbtree_node<char> *n3 = new stl::rbtree_node('d');
  n3->attach(n1, stl::RB_LEFT);
  n3->attach(n2, stl::RB_RIGHT);

  auto *p = stl::rb_increment(n3->left->right);
  char val = static_cast<stl::rbtree_node<char>*>(p)->value;
  EXPECT_EQ(val, 'd');
  p = stl::rb_decrement(n3->left->right);
  val = static_cast<stl::rbtree_node<char>*>(p)->value;
  EXPECT_EQ(val, 'b');
}

TEST(tree_test, rb_node_rotate_left) {
  stl::rbtree_node<int> *n1 = new stl::rbtree_node(2);
  stl::rbtree_node<int> *n2 = new stl::rbtree_node(5);
  stl::rbtree_node<int> *n3 = new stl::rbtree_node(6);
  stl::rbtree_node<int> *n4 = new stl::rbtree_node(8);
  stl::rbtree_node<int> *n5 = new stl::rbtree_node(9);
  stl::rbtree_node<int> *n6 = new stl::rbtree_node(10);
  stl::rbtree_node<int> *n7 = new stl::rbtree_node(12);

  n4->attach(n3, stl::RB_LEFT);
  n4->attach(n5, stl::RB_RIGHT);
  n6->attach(n4, stl::RB_LEFT);
  n6->attach(n7, stl::RB_RIGHT);
  n2->attach(n1, stl::RB_LEFT);
  n2->attach(n6, stl::RB_RIGHT);

  stl::rbtree_node<int> *root = n2;
  stl::rb_print<int>(root);
  root = static_cast<stl::rbtree_node<int> *>(stl::rb_rotate_left(root, root));
  stl::rb_print<int>(root);
}

TEST(tree_test, rb_node_rotate_right) {
  stl::rbtree_node<int> *n1 = new stl::rbtree_node(2);
  stl::rbtree_node<int> *n2 = new stl::rbtree_node(5);
  stl::rbtree_node<int> *n3 = new stl::rbtree_node(6);
  stl::rbtree_node<int> *n4 = new stl::rbtree_node(8);
  stl::rbtree_node<int> *n5 = new stl::rbtree_node(9);
  stl::rbtree_node<int> *n6 = new stl::rbtree_node(10);
  stl::rbtree_node<int> *n7 = new stl::rbtree_node(12);

  n4->attach(n3, stl::RB_LEFT);
  n4->attach(n5, stl::RB_RIGHT);
  n2->attach(n1, stl::RB_LEFT);
  n2->attach(n4, stl::RB_RIGHT);
  n6->attach(n2, stl::RB_LEFT);
  n6->attach(n7, stl::RB_RIGHT);

  stl::rbtree_node<int> *root = n6;
  stl::rb_print<int>(root);
  root = static_cast<stl::rbtree_node<int> *>(stl::rb_rotate_right(root, root));
  stl::rb_print<int>(root);
}

TEST(tree_test, rb_node_traverse) {
  stl::rbtree_node<int> *n1 = new stl::rbtree_node(1);
  n1->insert(2, stl::RB_LEFT);
  n1->insert(3, stl::RB_RIGHT);
  stl::rbtree_node<int> *n2 = new stl::rbtree_node(4);
  n2->insert(5, stl::RB_LEFT);
  n2->insert(6, stl::RB_RIGHT);
  stl::rbtree_node<int> *n3 = new stl::rbtree_node(7);
  n3->attach(n1, stl::RB_LEFT);
  n3->attach(n2, stl::RB_RIGHT);
  stl::vector<int> v, expect;

  stl::rb_pre_order(n3, v);
  expect.assign({7, 1, 2, 3, 4, 5, 6});
  EXPECT_EQ(v, expect);
  v.clear(); expect.clear();

  stl::rb_in_order(n3, v);
  expect.assign({2, 1, 3, 7, 5, 4, 6});
  EXPECT_EQ(v, expect);
  v.clear(); expect.clear();

  stl::rb_post_order(n3, v);
  expect.assign({2, 3, 1, 5, 6, 4, 7});
  EXPECT_EQ(v, expect);
  v.clear(); expect.clear();

  stl::rb_level_order(n3, v);
  expect.assign({7, 1, 4, 2, 3, 5, 6});
  EXPECT_EQ(v, expect);

  std::cout << "level traverse: ";
  v.for_each(v.begin(), v.end(), [](const int &v) {
    std::cout << v << " ";
  });
}

TEST(tree_test, tree_test_insert) {
  stl::rbtree<int> t;
  for (int i = 5; i >= 1; i--) {
    t.insert(i);
  }
  t.pre_order();
  t.in_order();
  t.post_order();
  t.level_order();
  t.print();
}

TEST(tree_test, tree_test_find) {
  stl::rbtree<int> t;
  t.insert(4);
  t.insert(2);
  t.insert(6);
  t.insert(1);
  t.insert(3);
  t.insert(5);
  t.insert(7);
  t.print();
  t.in_order();
//  for (int i = 0; i <= 7; i++) {
//    auto p = t.find(i);
//    if (p != nullptr) {
//      std::cout << p->value << "\n";
//    } else {
//      std::cout << "not exists\n";
//    }
//  }
  t.erase(t.root());
  t.print();
}
