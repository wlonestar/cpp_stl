//
// Created by wjl on 2023/5/29.
//

#ifndef CPP_STL_PRIORITY_QUEUE_H
#define CPP_STL_PRIORITY_QUEUE_H

#pragma once

#include <util.h>
#include <vector.h>

namespace stl {

/**
 * A priority queue is a container adaptor that provides constant time
 * lookup of the largest (by default) element, at the expense of
 * logarithmic insertion and extraction.
 *
 * A user-provided Compare can be supplied to change the ordering,
 * e.g. using std::greater<T> would cause the smallest element to
 * appear as the top().
 *
 * Working with a priority_queue is similar to managing a heap
 * in some random access container, with the benefit of not being able to
 * accidentally invalidate the heap.
 */

template<class T, class Container = stl::vector<T>,
         class Compare = std::less<typename Container::value_type>>
class priority_queue {
public:
  /**
   * Member types
   */

  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

private:
  /**
   * Member objects
   */

  Container c;
  Compare comp;

private:
  size_type heap_left(size_type i) { return 2 * i + 1; }
  size_type heap_right(size_type i) { return 2 * i + 2; }
  size_type heap_parent(size_type i) { return (i - 1) / 2; }

  void heapify(int heap_size, int i) {
    int l = heap_left(i);
    int r = heap_right(i);
    int replaced = i;
    if (l < heap_size && !comp(c[l], c[i])) {
      replaced = l;
    }
    if (r < heap_size && !comp(c[r], c[replaced])) {
      replaced = r;
    }
    if (replaced != i) {
      std::swap(c[i], c[replaced]);
      heapify(heap_size, replaced);
    }
  }

  T heap_extract_first() {
    int heap_size = c.size();
    T first = c[0];
    c[0] = c[heap_size - 1];
    heap_size -= 1;
    heapify(heap_size, 0);
    c.erase(c.end());
    return first;
  }

  void heap_increase_key(int i, const T &key) {
    c[i] = key;
    while (i > 0 && comp(c[heap_parent(i)], c[i])) {
      std::swap(c[i], c[heap_parent(i)]);
      i = heap_parent(i);
    }
  }

  void heap_insert(const T &key) {
    c.push_back(T());
    heap_increase_key(c.size() - 1, key);
  }

public:
  /**
   * Member functions
   */

  /**
   * Default constructor. Value-initializes the comparator
   * and the underlying container.
   */
  priority_queue()
      : priority_queue(Compare(), Container()) {}

  /**
   * Copy-constructs the comparison functor comp with the contents of compare.
   * Value-initializes the underlying container c.
   */
  explicit priority_queue(const Compare &compare)
      : priority_queue(compare, Container()) {}

  /**
   * Copy-constructs the underlying container c with the contents of cont.
   * Copy-constructs the comparison functor comp with the contents of compare.
   */
  priority_queue(const Compare &compare, const Container &cont)
      : comp(compare), c(cont) {}

  /**
   * Move-constructs the underlying container c with std::move(cont).
   * Copy-constructs the comparison functor comp with compare.
   */
  priority_queue(const Compare &compare, Container &&cont)
      : comp(compare), c(cont) {}

  /**
   * Copy constructor. The underlying container is copy-constructed with other.c.
   * The comparison functor is copy-constructed with other.comp.
   */
  priority_queue(const priority_queue &other) {
    c = other.c;
    comp = other.comp;
  }

  /**
   * Move constructor. The underlying container is constructed with
   * std::move(other.c).
   * The comparison functor is constructed with std::move(other.comp).
   */
  priority_queue(priority_queue &&other) {
    c = std::move(other.c);
    comp = std::move(other.comp);
  }

  /**
   * Destructs the priority_queue. The destructors of the elements
   * are called and the used storage is deallocated.
   *
   * Note, that if the elements are pointers,
   * the pointed-to objects are not destroyed.
   */
  ~priority_queue() = default;

  /**
   * Copy assignment operator.
   * Replaces the contents with a copy of the contents of other.
   *
   * @other - another container adaptor to be used as source
   * @return - *this
   */
  priority_queue &operator=(const priority_queue &other) {
    c = other.c;
    comp = other.comp;
    return *this;
  }

  /**
   * Move assignment operator.
   * Replaces the contents with those of other using move semantics.
   *
   * @other - another container adaptor to be used as source
   * @return - *this
   */
  priority_queue &operator=(priority_queue &&other) {
    c = std::move(other.c);
    comp = std::move(other.comp);
    return *this;
  }

  /**
   * Returns reference to the top element in the priority queue.
   * This element will be removed on a call to pop().
   * If default comparison function is used, the returned element is
   * also the greatest among the elements in the queue.
   *
   * @return - reference to the top element
   */
  const_reference top() const {
    return c.front();
  }

  /**
   * Checks if the underlying container has no elements.
   *
   * @return - true if the underlying container is empty, false otherwise
   */
  bool empty() const {
    return c.empty();
  }

  /**
   * Returns the number of elements in the underlying container.
   *
   * @return - the number of elements in the container
   */
  size_type size() const {
    return c.size();
  }

  /**
   * Pushes the given element value to the priority queue.
   *
   * @value -the value of the element to push
   */
  void push(const value_type &value) {
    heap_insert(value);
  }

  void push(value_type &&value) {
    heap_insert(std::move(value));
  }

  /**
   * Pushes a new element to the priority queue. The element is constructed
   * in-place, i.e. no copy or move operations are performed.
   * The constructor of the element is called with exactly the same arguments
   * as supplied to the function.
   *
   * @args - arguments to forward to the constructor of the element
   */
  template<class... Args>
  void emplace(Args &&...args) {
    auto value = new T(std::forward<Args>(args)...);
    heap_insert(*value);
  }

  /**
   * Removes the top element from the priority queue.
   */
  void pop() {
    heap_extract_first();
  }

  /**
   * Exchanges the contents of the container adaptor with those of other.
   *
   * @other - container adaptor to exchange the contents with
   */
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
