//
// Created by wjl on 2023/5/29.
//

#ifndef CPP_STL_PRIORITY_QUEUE_H
#define CPP_STL_PRIORITY_QUEUE_H

#pragma once

#include <util.h>
#include <vector.h>

namespace stl {

#define _heap_left(i) (2 * (i) + 1)
#define _heap_right(i) (2 * (i) + 2)
#define _heap_parent(i) ((i - 1) / 2)

template<class T>
static void max_heapify(T *a, int heap_size, int i) {
  int l = _heap_left(i);
  int r = _heap_right(i);
  int largest = i;
  if (l < heap_size && a[l] > a[i]) {
    largest = l;
  }
  if (r < heap_size && a[r] > a[largest]) {
    largest = r;
  }
  if (largest != i) {
    std::swap(a[i], a[largest]);
    max_heapify(a, heap_size, largest);
  }
}

template<class T>
static void build_max_heap(T *a, int n) {
  int heap_size = n;
  for (int i = heap_size / 2; i >= -1; i--) {
    max_heapify(a, heap_size, i);
  }
}

template<class T>
static void max_heapify(vector<T> &v, int heap_size, int i) {
  int l = _heap_left(i);
  int r = _heap_right(i);
  int largest = i;
  if (l < heap_size && v[l] > v[i]) {
    largest = l;
  }
  if (r < heap_size && v[r] > v[largest]) {
    largest = r;
  }
  if (largest != i) {
    std::swap(v[i], v[largest]);
    max_heapify(v, heap_size, largest);
  }
}

template<class T>
static T heap_extract_max(vector<T> &v) {
  int heap_size = v.size();
  assert(heap_size >= 1);
  T max = v[0];
  v[0] = v[heap_size - 1];
  heap_size -= 1;
  max_heapify(v, heap_size, 0);
  v.erase(v.end());
  return max;
}

template<class T>
static void heap_increase_key(vector<T> &v, int i, const T &key) {
  assert(key >= v[i]);
  v[i] = key;
  while (i > 0 && v[_heap_parent(i)] < v[i]) {
    std::swap(v[i], v[_heap_parent(i)]);
    i = _heap_parent(i);
  }
}

template<class T>
static void max_heap_insert(vector<T> &v, const T &key) {
  v.push_back(T());
  heap_increase_key(v, v.size() - 1, key);
}

template<class T, class Container = stl::vector<T>,
         class Compare = std::less<typename Container::value_type>>
class priority_queue {
public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

private:
  Container c;
  Compare comp;

public:
  priority_queue()
      : priority_queue(Compare(), Container()) {}

  explicit priority_queue(const Compare &compare)
      : priority_queue(compare, Container()) {}

  priority_queue(const Compare &compare, const Container &cont)
      : comp(compare), c(cont) {}

  priority_queue(const Compare &compare, Container &&cont)
      : comp(compare), c(cont) {}

  priority_queue(const priority_queue &other) {
    c = other.c;
    comp = other.comp;
  }

  priority_queue(priority_queue &&other) {
    c = std::move(other.c);
    comp = std::move(other.comp);
  }

  ~priority_queue() = default;

  priority_queue &operator=(const priority_queue &other) {
    c = other.c;
    comp = other.comp;
    return *this;
  }

  priority_queue &operator=(priority_queue &&other) {
    c = std::move(other.c);
    comp = std::move(other.comp);
    return *this;
  }

  const_reference top() const {
    return c.front();
  }

  bool empty() const {
    return c.empty();
  }

  size_type size() const {
    return c.size();
  }

  void push(const value_type &value) {
    max_heap_insert(c, value);
  }

  void push(value_type &&value) {
    max_heap_insert(c, std::move(value));
  }

  template<class... Args>
  void emplace(Args &&...args) {
    auto value = new T(std::forward<Args>(args)...);
    max_heap_insert(c, *value);
  }

  void pop() {
    heap_extract_max(c);
  }

  void swap(priority_queue &other) noexcept {
    std::swap(c, other.c);
    std::swap(comp, other.comp);
  }
};

template<class T, class Container, class Compare>
void swap(stl::priority_queue<T, Container, Compare> &lhs,
          stl::priority_queue<T, Container, Compare> &rhs) {
  lhs.swap(rhs);
}

}// namespace stl

#endif//CPP_STL_PRIORITY_QUEUE_H
