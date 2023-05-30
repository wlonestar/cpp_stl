//
// Created by wjl on 2023/5/29.
//

#include "priority_queue.h"
#include <gtest/gtest.h>

TEST(pq_test, stl_pq) {
  stl::priority_queue<int> q;
  for (int i = 0; i < 10; i++) {
    q.push(i);
    int val = q.top();
    std::cout << "max value: " << val << "\n";
  }
  for (int i = 0; i < 10; i++) {
    int val = q.top();
    q.pop();
    std::cout << "del max: " << val << "\n";
  }
  assert(q.size() == 0);
}
