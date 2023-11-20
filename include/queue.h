//
// Created by wjl on 2023/4/25.
//

#ifndef CPP_STL_QUEUE_H
#define CPP_STL_QUEUE_H

#pragma once

#include <list.h>

namespace stl {

/**
 * The stl::queue class is a container adaptor that gives the programmer the
 * functionality of a queue - specifically, a LIFO (last-in, first-out) data
 * structure.
 *
 * The class template acts as a wrapper to the underlying container - only a
 * specific set of functions is provided. The queue pushes and pops the element
 * from the back of the underlying container, known as the top of the queue.
 */

template<class T, class Container = stl::list<T>>
class queue {
public:
  /**
   * Member types
   */

  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

protected:
  /**
   * Member objects
   */

  Container c;

public:
  /**
   * Member functions
   */

  /**
   * Default constructor. Value initializes the container.
   */
  queue() : queue(Container()) {}

  /**
   * Copy-constructs the underlying container c with the contents of @cont.
   *
   * @cont - container to be used as source to initialize the underlying
   *         container
   */
  explicit queue(const Container &cont) { c = cont; }

  /**
   * Move-constructs the underlying container c with std::move(cont).
   *
   * @param cont - container to be used as source to initialize the underlying
   *                  container
   */
  explicit queue(Container &&cont) { c = std::move(cont); }

  /**
   * Destructs the queue.
   */
  ~queue() = default;

  /**
   * Copy assignment operator. Replaces the contents with a copy of the contents
   * of @other. Effectively calls c = other.c.
   *
   * @other - another container adaptor to be used as source
   * @return - *this
   */
  queue &operator=(const queue &other) {
    this->c = other.c;
    return *this;
  }

  /**
   * Move assignment operator. Replaces the contents with a copy of the contents
   * of @other. Effectively calls c = std::move(other.c).
   *
   * @other - another container adaptor to be used as source
   * @return - *this
   */
  queue &operator=(queue &&other) {
    this->c = std::move(other.c);
    return *this;
  }

  friend bool operator==(const queue &lhs, const queue &rhs) {
    return lhs.c == rhs.c;
  }

  /**
   * Element access
   */

  /**
   * Returns reference to the first element in the queue. This element will be
   * the first element to be removed on a call to pop().
   *
   * Effectively calls c.front().
   *
   * @return - reference to the first element
   */
  reference front() { return c.front(); }

  const_reference front() const { return c.front(); }

  /**
   * Returns reference to the last element in the queue. This is the most
   * recently pushed element.
   *
   * Effectively calls c.back().
   *
   * @return - reference to the last element
   */
  reference back() { return c.back(); }

  const_reference back() const { return c.back(); }

  /**
   * Capacity
   */

  /**
   * Checks if the underlying container has no elements.
   *
   * @return - true if the underlying container is empty, false otherwise
   */
  bool empty() const { return c.empty(); }

  /**
   * Returns the number of elements in the underlying container.
   *
   * @return - the number of elements in the container
   */
  size_type size() const { return c.size(); }

  /**
   * Modifiers
   */

  /**
   * Pushes the give element value to the top of the queue.
   *
   * @value - the value of the element to push
   */
  void push(const value_type &value) { c.push_back(value); }

  void push(value_type &&value) { c.push_back(std::move(value)); }

  /**
   * Pushes a new element on top of the queue. The element is constructed
   * in-place, no copy or move operations are performed. The constructor of the
   * element is called with exactly the same arguments as supplied to the
   * function.
   *
   * @args - arguments to forward to the constructor of the element
   * @return - the value or reference
   */
  template<class... Args>
  decltype(auto) emplace(Args &&...args) {
    return c.emplace_back(std::forward<Args>(args)...);
  }

  /**
   * Removes the top element from the queue
   */
  void pop() { c.pop_front(); }

  /**
   * Exchanges the contents of the container adaptor with those of @other.
   *
   * @other - container adaptor to exchange the contents with
   */
  void swap(queue &other) noexcept { std::swap(this->c, other.c); }

  void print() {
    std::cout << "queue: [ ";
    for (auto it = c.begin(); it != c.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << "]\n";
  }
};

/**
 * Compare the contents of the underlying containers of two container adaptors.
 * The comparison is done by applying the corresponding operator to the
 * underlying containers.
 *
 * @lhs, @rhs - container adaptors whose contents to compare
 * @return - true if the corresponding comparison yields true, false otherwise
 */
template<class T, class Container>
inline bool operator==(const stl::queue<T, Container> &lhs,
                       const stl::queue<T, Container> &rhs) {
  return lhs.c == rhs.c;
}

/**
 * Specializes the stl::swap algorithm for stl::queue.
 *
 * Swaps the contents of @lhs and @rhs.
 *
 * @lhs, @rhs - containers whose contents to swap
 */
template<class T, class Container>
void swap(stl::queue<T, Container> &lhs, stl::queue<T, Container> &rhs) {
  lhs.swap(rhs);
}

}// namespace stl

#endif// CPP_STL_QUEUE_H
