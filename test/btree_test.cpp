//
// Created by wjl on 2023/5/21.
//

#include "btree.h"
#include <gtest/gtest.h>

TEST(btree_test, btree_init) {
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
