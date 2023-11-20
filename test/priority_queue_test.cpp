//
// Created by wjl on 2023/5/29.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE priority_queue_test
#include <boost/test/included/unit_test.hpp>

#include <priority_queue.h>

BOOST_AUTO_TEST_CASE(stl_pq) {
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
    stl::priority_queue<int, stl::vector<int>, std::greater<int>> q;
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
