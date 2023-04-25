//
// Created by wjl on 2023/4/25.
//

#ifndef CPP_STL_STACK_H
#define CPP_STL_STACK_H

#pragma once

#include "list.h"

namespace stl {

/**
 * The stl::stack class is a container adaptor that gives the programmer the
 * functionality of a stack - specifically, a LIFO (last-in, first-out) data
 * structure.
 *
 * The class template acts as a wrapper to the underlying container - only a
 * specific set of functions is provided. The stack pushes and pops the element
 * from the back of the underlying container, known as the top of the stack.
 */

template<class T, class Container = stl::list<T>>
class stack {
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
  stack() : stack(Container()) {}

  /**
   * Copy-constructs the underlying container c with the contents of @cont.
   *
   * @cont - container to be used as source to initialize the underlying
   *         container
   */
  explicit stack(const Container &cont) {
    c = cont;
  }

  /**
   * Move-constructs the underlying container c with std::move(cont).
   *
   * @param cont - container to be used as source to initialize the underlying
*                  container
   */
  explicit stack(Container &&cont) {
    c = std::move(cont);
  }

  /**
   * Destructs the stack.
   */
  ~stack() = default;

  /**
   * Copy assignment operator. Replaces the contents with a copy of the contents
   * of @other. Effectively calls c = other.c.
   *
   * @other - another container adaptor to be used as source
   * @return - *this
   */
  stack &operator=(const stack &other) {
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
  stack &operator=(stack &&other) {
    this->c = std::move(other.c);
    return *this;
  }

  friend bool operator==(const stack &lhs, const stack &rhs) {
    return lhs.c == rhs.c;
  }

  /**
   * Element access
   */

  /**
   * Returns reference to the top element in the stack. This is the most recently
   * pushed element. This element will be removed on a call to pop().
   *
   * Effectively calls c.back().
   *
   * @return - reference to the last element
   */
  reference top() {
    return c.back();
  }
  const_reference top() const {
    return c.back();
  }

  /**
   * Capacity
   */

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
   * Modifiers
   */

  /**
   * Pushes the give element value to the top of the stack.
   *
   * @value - the value of the element to push
   */
  void push(const value_type &value) {
    c.push_back(value);
  }
  void push(value_type &&value) {
    c.push_back(std::move(value));
  }

  /**
   * Pushes a new element on top of the stack. The element is constructed in-place,
   * no copy or move operations are performed. The constructor of the element is
   * called with exactly the same arguments as supplied to the function.
   *
   * @args - arguments to forward to the constructor of the element
   * @return - the value or reference
   */
  template<class... Args>
  decltype(auto) emplace(Args &&...args) {
    return c.emplace_back(std::forward<Args>(args)...);
  }

  /**
   * Removes the top element from the stack
   */
  void pop() {
    c.pop_back();
  }

  /**
   * Exchanges the contents of the container adaptor with those of @other.
   *
   * @other - container adaptor to exchange the contents with
   */
  void swap(stack &other) noexcept {
    std::swap(this->c, other.c);
  }

  void print() {
    std::cout << "stack: [ ";
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
inline bool operator==(const stl::stack<T, Container> &lhs,
                       const stl::stack<T, Container> &rhs) {
  return lhs.c == rhs.c;
}

/**
 * Specializes the stl::swap algorithm for stl::stack.
 *
 * Swaps the contents of @lhs and @rhs.
 *
 * @lhs, @rhs - containers whose contents to swap
 */
template<class T, class Container>
void swap(stl::stack<T, Container> &lhs,
          stl::stack<T, Container> &rhs) {
  lhs.swap(rhs);
}

}// namespace stl

#endif//CPP_STL_STACK_H
