//
// Created by wjl on 2023/4/14.
//

#ifndef CPP_STL_UTIL_H
#define CPP_STL_UTIL_H

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <random>

namespace stl {

#define TODO()                \
  printf("Not implemented!"); \
  exit(-1)

#define Log(format, ...) printf(format "\n", ##__VA_ARGS__)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int random_int(int n) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, n - 1);
  return dist(rng);
}

int random_int(int a, int b) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);
  return dist(rng);
}


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
  explicit simple_timer(size_t count) {
    _count = count;
    _totalTime = 0;
    printf("start count %4zu times ==>\n", _count);
  }

  void reset(size_t count) {
    _count = count;
    _totalTime = 0;
    printf("start count %4zu times ==>\n", _count);
  }

  void continu() {
    _start = std::chrono::high_resolution_clock::now();
  }

  void pause() {
    _end = std::chrono::high_resolution_clock::now();
    _totalTime += std::chrono::duration<double, std::milli>(_end - _start).count();
  }

  void stop() {
    double average = _totalTime / (double) _count;
    printf("end count %4zu times ==> total = %.4f ms, average = %.4f ms\n", _count, _totalTime, average);
  }

  std::tuple<size_t, double, double> stop() const {
    double average = _totalTime / (double) _count;
    return {_count, _totalTime, average};
  }
};

/**
 * for visualization
 */

namespace visual {

/**
 * get formatted current time
 * format: %Y-%m-%d_%H-%M-%S
 */
std::string get_current_time() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
  return oss.str();
}

/**
 * replace file specified char
 */
void replace_string_of_file(const std::string &file, std::string replace, std::string replace_with) {
  std::fstream f(file, std::ios::in);
  if (f.is_open()) {
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(f, line)) {
      std::string::size_type pos = 0;
      while ((pos = line.find(replace, pos)) != std::string::npos) {
        line.replace(pos, line.size(), replace_with);
        pos += replace_with.size();
      }
      lines.push_back(line);
    }
    f.close();
    f.open(file, std::ios::out | std::ios::trunc);
    for (const auto &i: lines) {
      f << i << std::endl;
    }
  }
}

}// namespace visual

}// namespace stl

#endif//CPP_STL_UTIL_H
