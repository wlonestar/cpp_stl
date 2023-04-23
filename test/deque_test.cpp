//
// Created by wjl on 2023/4/23.
//

#include "util.h"
#include "deque.h"
#include <cassert>

template<class T>
void test_deque_init() {
  Log("==> test deque constructor");
//  std::deque<T> q1(3, 5);
//  assert(q1.size() == 3 && q1.front() == 5 && q1.back() == 5);
//  std::deque<T> q2(5);
//  assert(q2.size() == 5 && q2.front() == 0 && q2.back() == 0);
//  std::deque<T> q4(q1);
//  assert(q4.size() == 3 && q4.front() == 5 && q4.back() == 5);
//  std::deque<T> q5(std::move(q2));
//  assert(q5.size() == 5 && q5.front() == 0 && q5.back() == 0);
//  std::initializer_list<T> ilist{2, 3, 4, 5};
//  std::deque<T> q6(ilist);
//  assert(q6.size() == 4 && q6.front() == 2 && q6.back() == 5);
  Log("==> pass!");
}

template<class T>
void test_deque() {
  test_deque_init<T>();
}

int main() {
  test_deque<int>();
  return 0;
}
