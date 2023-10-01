//
// Created by wjl on 2023/5/8.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE rbtree_test
#include <boost/test/included/unit_test.hpp>

#include <avl.h>

BOOST_AUTO_TEST_CASE(tree_insert) {
  Log("==> test tree insert()");
  stl::avl<int> t2;
  for (int i = 0; i < 12; i++) {
    t2.insert(i);
  }
  t2.print();

  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(tree_erase) {
  Log("==> test tree erase()");
  stl::avl<int> t;
  stl::vector<int> v;
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.print();
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.insert(1);
  Log("==> pass!");
}
