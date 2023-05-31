//
// Created by wjl on 2023/5/30.
//

#include "multi_thread.h"
#include <gtest/gtest.h>

TEST(mt_test, mt_init) {
  int count = 1;
  stl::simple_timer t(count);
  for (int i = 0; i < count; i++) {
    t.continu();
    int val = stl::p_fib(10);
    t.pause();
  }
  t.stop();

  t.reset(count);
  for (int i = 0; i < count; i++) {
    t.continu();
    int val = stl::fib(10);
    t.pause();
  }
  t.stop();

}
