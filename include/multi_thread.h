//
// Created by wjl on 2023/5/30.
//

#ifndef CPP_STL_MULTI_THREAD_H
#define CPP_STL_MULTI_THREAD_H

#pragma once

#include "util.h"
#include <iostream>
#include <thread>
#include <future>

namespace stl {

int p_fib(int n) {
  if (n <= 1) {
    return n;
  }
  std::future<int> t = std::async(&p_fib, n - 1);
  int y = p_fib(n - 2);
  int x = t.get();
  return x + y;
}

int fib(int n) {
  if (n <= 1) {
    return n;
  }
  int y = fib(n - 2);
  int x = fib(n - 1);
  return x + y;
}

}

#endif//CPP_STL_MULTI_THREAD_H
