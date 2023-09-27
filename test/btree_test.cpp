//
// Created by wjl on 2023/5/21.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE btree_test
#include <boost/test/included/unit_test.hpp>

#include <btree.h>

BOOST_AUTO_TEST_CASE(simple_btree_test) {
  stl::btree<int> t;
  for (int i = 0; i < 10; i++) {
    t.insert(i);
  }
  t.print();
  for (int i = 0; i < 10; i++) {
    auto [node, index] = t.search(i);
    std::cout << node->keys.size() << "-" << node->children.size() << ":" << index << "\n";
  }
  for (int i = 0; i < 10; i++) {
    t.erase(i);
  }
  for (int i = 0; i < 10; i++) {
    t.insert(i);
  }
  t.print();
}
