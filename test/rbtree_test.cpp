//
// Created by wjl on 2023/5/8.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE rbtree_test
#include <boost/test/included/unit_test.hpp>

#include <rbtree.h>

BOOST_AUTO_TEST_CASE(tree_insert) {
  Log("==> test tree insert()");
  stl::rbtree<int> t2;
  for (int i = 0; i < 12; i++) {
    t2.insert(i);
  }
  t2.print();

  stl::vector<int> v;
  t2.in_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(tree_erase) {
  Log("==> test tree erase()");
  stl::rbtree<int> t;
  stl::vector<int> v;
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.print();

  t.erase(0);
  t.erase(12);
  t.clear();
  BOOST_CHECK(t.size() == 0);
  for (int i = 0; i < 12; i++) {
    t.insert(i);
  }
  t.insert(1);
  t.in_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(tree_traverse) {
  Log("==> test tree insert()");
  stl::rbtree<int> t;
  stl::vector<int> v;

  for (int i = 1; i <= 7; i++) {
    t.insert(i);
  }
  t.print();

  BOOST_CHECK(t.size() == 7);

  t.pre_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  v.clear();

  t.in_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  v.clear();

  t.post_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  v.clear();

  t.level_order(v);
  v.for_each(v.begin(), v.end(),
             [](const int &value) { std::cout << value << " "; });
  std::cout << "\n";
  v.clear();

  Log("==> pass!");
}
