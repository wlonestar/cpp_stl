//
// Created by wjl on 2023/4/14.
//

#ifndef CPP_STL_UTIL_H
#define CPP_STL_UTIL_H

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>

namespace stl {

#define TODO()                \
  printf("Not implemented!"); \
  exit(-1)

#define Log(format, ...) printf(format "\n", ##__VA_ARGS__)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef std::chrono::time_point<
  std::chrono::system_clock,
  std::chrono::duration<double, std::milli>>
  timer_t__;

/**
 * simple_timer: use for time testing
 */
class simple_timer {
private:
  size_t _count;
  timer_t__ _start;
  timer_t__ _end;
  double _totalTime;

public:
  explicit simple_timer(size_t count);

  void reset(size_t count);
  void continu();
  void pause();
  void stop() const;
};

simple_timer::simple_timer(size_t count) {
  _count = count;
  _totalTime = 0;
  printf("start count %4zu times ==>\n", _count);
}

void simple_timer::reset(size_t count) {
  _count = count;
  _totalTime = 0;
  printf("start count %4zu times ==>\n", _count);
}

void simple_timer::continu() {
  _start = std::chrono::high_resolution_clock::now();
}

void simple_timer::pause() {
  _end = std::chrono::high_resolution_clock::now();
  _totalTime += std::chrono::duration<double, std::milli>(_end - _start).count();
}

void simple_timer::stop() const {
  double average = _totalTime / (double) _count;
  printf("end count %4zu times ==> total = %.4f ms, average = %.4f ms\n", _count, _totalTime, average);
}

}// namespace stl

#endif//CPP_STL_UTIL_H
