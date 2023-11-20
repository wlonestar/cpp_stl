//
// Created by wjl on 2023/8/10.
//

#include <iostream>

#include <sort.h>

template<class T>
bool exists(stl::vector<T> &v, T val) {
  for (T &item: v) {
    if (item == val) {
      return true;
    }
  }
  return false;
}

template<class T>
void random_vector(stl::vector<T> &v, int size) {
  while (v.size() < size) {
    T val = stl::random_data((T) size * 2.0);
    if (!exists(v, val)) {
      v.push_back(val);
    }
  }
}

template<class T>
void common_test(int times, void (*sort)(stl::vector<T> &v),
                 stl::vector<int> test_range, const char *name) {
  stl::simple_timer timer;
  for (int &range: test_range) {
    timer.reset(times);
    stl::vector<T> v;
    random_vector(v, range);
    timer.continu();
    sort(v);
    timer.pause();
    auto [count, total, avg] = timer.stop();
    printf("[%s]: %8d %s elements, %4ld times, total time: %15.8fms, average "
           "time: %15.8fms.\n",
           name, range, typeid(T).name(), count, total, avg);
  }
}

int main() {
  int times = 100;
  stl::vector<int> range{5, 10, 100, 1000, 10000, 20000, 30000, 40000, 50000};

  common_test<int>(times, stl::sort::insertion_sort, range, "insert sort");
  common_test<float>(times, stl::sort::insertion_sort, range, "insert sort");
  common_test<double>(times, stl::sort::insertion_sort, range, "insert sort");

  common_test<int>(times, stl::sort::merge_sort, range, " merge sort");
  common_test<float>(times, stl::sort::merge_sort, range, " merge sort");
  common_test<double>(times, stl::sort::merge_sort, range, " merge sort");

  common_test<int>(times, stl::sort::quick_sort, range, " quick sort");
  common_test<float>(times, stl::sort::quick_sort, range, " quick sort");
  common_test<double>(times, stl::sort::quick_sort, range, " quick sort");
}
