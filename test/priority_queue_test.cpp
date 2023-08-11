//
// Created by wjl on 2023/5/29.
//

#include <gtest/gtest.h>
#include <priority_queue.h>

TEST(pq_test, stl_pq) {
  {
    stl::priority_queue<int> q;
    for (int i = 0; i < 10; i++) {
      q.push(i);
    }
    for (int i = 0; i < 10; i++) {
      int val = q.top();
      q.pop();
      std::cout << "del max: " << val << "\n";
    }
    assert(q.size() == 0);
  }

  {
    stl::priority_queue<int, stl::vector<int>,
      std::greater<int>> q;
    for (int i = 0; i < 10; i++) {
      q.push(i);
    }
    for (int i = 0; i < 10; i++) {
      int val = q.top();
      q.pop();
      std::cout << "del max: " << val << "\n";
    }
    assert(q.size() == 0);
  }
}
