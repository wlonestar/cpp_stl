//
// Created by wjl on 2023/4/17.
//

#ifndef CPP_STL_LIST_H
#define CPP_STL_LIST_H

#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>

#include "util.h"

namespace stl {

template<class T>
struct list_node {
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  T data;
  list_node *prev;
  list_node *next;

  list_node() {
    this->prev = this;
    this->next = this;
  }

  explicit list_node(const T &value) {
    data = value;
    this->prev = this;
    this->next = this;
  }

  void insert(list_node<T> *_prev, list_node<T> *_next) {
    this->prev = _prev;
    _prev->next = this;
    this->next = _next;
    _next->prev = this;
  }

  void remove(list_node<T> *_prev, list_node<T> *_next) {
    _prev->next = _next;
    _next->prev = _prev;
    this->prev = this;
    this->next = this;
  }
};

template<class T>
struct list_iterator {
  typedef list_iterator<T> self;
  typedef list_node<T> node;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;

  node *_node;

  list_iterator() : _node() {}
  explicit list_iterator(node *n) : _node(n) {}

  self _const_cast() const { return *this; }

  reference operator*() const {
    return _node->data;
  }

  pointer operator->() const {
    return _node->data;
  }

  self &operator++() {
    _node = _node->next;
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    _node = _node->next;
    return tmp;
  }

  self &operator--() {
    _node = _node->prev;
    return *this;
  }

  self operator--(int) {
    self tmp = *this;
    _node = _node->prev;
    return tmp;
  }

  friend bool operator==(const self &x, const self &y) {
    return x._node == y._node;
  }
};

template<class T>
struct list_const_iterator {
  typedef list_const_iterator<T> self;
  typedef const list_node<T> node;
  typedef list_iterator<T> iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;

  node *_node;

  list_const_iterator() : _node() {}
  explicit list_const_iterator(node *x) : _node(x) {}
  explicit list_const_iterator(const iterator &x) : _node(x._node) {}

  iterator _const_cast() const {
    return iterator(const_cast<node *>(_node));
  }

  reference operator*() const {
    return _node->data;
  }

  pointer operator->() const {
    return _node->data;
  }

  self &operator++() {
    _node = _node->next;
    return *this;
  }

  self operator++() const {
    self tmp = *this;
    _node = _node->next;
    return tmp;
  }

  self &operator--() {
    _node = _node->prev;
    return *this;
  }

  self operator--() const {
    self tmp = *this;
    _node = _node->prev;
    return tmp;
  }

  friend bool operator==(const self &x, const self &y) {
    return x._node == y._node;
  }
};

/**
 * stl::list is a container that supports constant time insertion and removal of
 * elements from anywhere in the container. Fast random access is not supported.
 * It is usually implemented as a doubly-linked list.
 *
 * Adding, removing and moving the elements within the list or across several
 * lists does not invalidate the iterators or references. An iterator is
 * invalidated only when the corresponding element is deleted.
 */

template<class T>
class list {
public:
  /**
   * Member types
   */

  typedef T value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef list_iterator<T> iterator;
  typedef list_const_iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef list_node<T> node;

private:
  node *_head;
  size_type _size;

  bool sorted() {
    auto last = end();
    last--;
    for (auto it = begin(); it != last; ++it) {
      auto next = it;
      next++;
      if (*it > *next) {
        return false;
      }
    }
    return true;
  }

  template<class Compare>
  bool sorted(Compare comp) {
    auto last = end();
    last--;
    for (auto it = begin(); it != last; ++it) {
      auto next = it;
      next++;
      if (comp(*next, *it) == true) {
        return false;
      }
    }
    return true;
  }

  iterator select_max(iterator first, iterator last) {
    auto max = first;
    auto it = first;
    it++;
    for (; it != last; ++it) {
      if (*it > *max) {
        max = it;
      }
    }
    return max;
  }

  template<class Compare>
  iterator select_max(iterator first, iterator last, Compare comp) {
    auto max = first;
    auto it = first;
    it++;
    for (; it != last; ++it) {
      if (comp(*max, *it) == true) {
        max = it;
      }
    }
    return max;
  }

  void remove(iterator pos) {
    pos._node->remove(pos._node->prev, pos._node->next);
    _size--;
  }

public:
  /**
   * Member functions
   */

  /**
   * Default constructor. Constructs an empty container.
   */
  list() {
    _head = new list_node<T>();
    _size = 0;
  }

  /**
   * Constructs the container with @count copies of elements with value @value.
   *
   * @count - the size of the container
   * @value - the value to initialize elements of the container with
   */
  explicit list(size_type count, const T &value) {
    _head = new list_node<T>();
    _size = count;
    for (size_type i = 0; i < count; i++) {
      node *_node = new list_node<T>(value);
      _node->insert(_head->prev, _head);
    }
  }

  /**
   * Constructs the container with @count default-inserted instances of T.
   * No copies are made.
   *
   * @count - the size of the container
   */
  explicit list(size_type count) {
    _head = new list_node<T>();
    _size = count;
    for (size_type i = 0; i < count; i++) {
      node *_node = new list_node<T>();
      _node->insert(_head->prev, _head);
    }
  }

  /**
   * Copy constructor. Constructs the container with the copy of the contents
   * of @other.
   *
   * @other - another container to be used as source to initialize the elements
   *          of the container with
   */
  list(const list &other) {
    _head = new list_node<T>();
    _size = other._size;
    for (auto *p = other._head->next; p != other._head; p = p->next) {
      auto *newp = new list_node<T>(p->data);
      newp->insert(_head->prev, _head);
    }
  }

  /**
   * Move constructor. Constructs the container with the contents of @other using
   * move semantics.
   *
   * @other - another container to be used as source to initialize the elements
*             of the container with
   */
  list(list &&other) noexcept : _head(other._head) {
    _size = other._size;
    other._size = 0;
    other._head = nullptr;
  }

  /**
   * Constructs the container with the contents of the initializer list @init.
   *
   * @init - initializer list to initialize the elements of the container with
   */
  list(std::initializer_list<T> init) {
    _head = new list_node<T>();
    _size = init.size();
    for (auto it = init.begin(); it != init.end(); ++it) {
      node *_node = new list_node<T>(*it);
      _node->insert(_head->prev, _head);
    }
  }

  /**
   * Destructs the list. The destructors of the elements are called and the used
   * storage is deallocated.
   *
   * Note, that if the elements are pointers, the pointed-to objects are not
   * destroyed.
   */
  ~list() {
    clear();
    delete _head;
  }

  /**
   * Copy assignment operator. Replaces the contents with a copy of the contents
   * of other.
   *
   * @other - another container to use as data source
   * @return - *this
   */
  list &operator=(const list &other) {
    _head = new list_node<T>();
    _size = other._size;
    for (auto *p = other._head->next; p != other._head; p = p->next) {
      auto *newp = new list_node<T>(p->data);
      newp->insert(_head->prev, _head);
    }
    return *this;
  }

  /**
   * Move assignment operator. Replaces the contents with those of other using
   * move semantics. other is in a valid but unspecified state afterwards.
   *
   * @other - another container to use as data source
   * @return - *this
   */
  list &operator=(list &&other) noexcept {
    _size = other._size;
    _head = std::move(other._head);
    other._size = 0;
    other._head = nullptr;
    return *this;
  }

  /**
   * Replaces the contents with those identified by initializer list @ilist.
   *
   * @ilist - initializer list to use as data source
   * @return - *this
   */
  list &operator=(std::initializer_list<T> ilist) {
    _head = new list_node<T>();
    _size = ilist.size();
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      node *_node = new list_node<T>(*it);
      _node->insert(_head->prev, _head);
    }
    return *this;
  }

  /**
   * Replaces the contents with @count copies of value @value.
   *
   * @count - the new size of the container
   * @value - the value to initialize elementd of the container with
   */
  void assign(size_type count, const T &value) {
    if (count <= _size) {
      size_type i = 0;
      for (auto p = _head->next; i < count; p = p->next, i++) {
        p->data = value;
      }
      for (size_type j = 0; j < (_size - count); j++) {
        _head->prev->remove(_head->prev->prev, _head);
      }
    } else {
      for (auto p = _head->next; p != _head; p = p->next) {
        p->data = value;
      }
      for (size_type i = 0; i < (count - _size); i++) {
        node *newp = new list_node(value);
        newp->insert(_head->prev, _head);
      }
    }
    _size = count;
  }

  /**
   * Replaces the contents with the elements from the initializer list @ilist.
   *
   * @ilist - initializer list to copy the values from
   */
  void assign(std::initializer_list<T> ilist) {
    size_type count = ilist.size();
    if (count <= _size) {
      auto p = _head->next;
      for (auto it = ilist.begin(); it != ilist.end(); ++it, p = p->next) {
        p->data = (*it);
      }
      for (size_type j = 0; j < (_size - count); j++) {
        _head->prev->remove(_head->prev->prev, _head);
      }
    } else {
      auto p = _head->next;
      auto it = ilist.begin();
      size_type i = 0;
      for (; i < _size; ++i, ++it, p = p->next) {
        p->data = (*it);
      }
      for (; i < count; ++i, ++it) {
        auto *newp = new list_node(*it);
        newp->insert(_head->prev, _head);
      }
    }
    _size = count;
  }

  /**
   * Element access
   */

  /**
   * Returns a reference to the first element in the container.
   *
   * @return - reference to the first element
   */
  reference front() {
    return _head->next->data;
  }
  const_reference front() const {
    return _head->next->data;
  }

  /**
   * Returns a reference to the last element in the container.
   * Calling back on an empty container causes undefined behavior.
   *
   * @return - reference to the last element
   */
  reference back() {
    return _head->prev->data;
  }
  const_reference back() const {
    return _head->prev->data;
  }

  /**
   * Iterators
   */

  /**
   * Returns an iterator to the first element of the list.
   * If the list is empty, the returned iterator will be equal to end().
   *
   * @return - iterator to the first element
   */
  iterator begin() noexcept {
    return iterator(_head->next);
  }
  const_iterator begin() const noexcept {
    return const_iterator(_head->next);
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(_head->next);
  }

  /**
   * Returns an iterator to the element following the last element of the list.
   * This element acts as a placeholder; attempting to access it results in
   * undefined behavior.
   *
   * @return - iterator of the element following the lase element
   */
  iterator end() noexcept {
    return iterator(_head);
  }
  const_iterator end() const noexcept {
    return const_iterator(_head);
  }
  const_iterator cend() const noexcept {
    return const_iterator(_head);
  }

  /**
   * Returns a reverse iterator to the first element of the reversed list.
   * It corresponds to the last element of the non-reversed list.
   * If the list is empty, the returned iterator is equal to rend().
   *
   * @return - reverse iterator to the first element
   */
  reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  }

  /**
   * Returns a reverse iterator to the element following the last element of
   * the reversed list. It corresponds to the element preceding the first
   * element of the non-reversed list. This element acts as a placeholder,
   * attempting to access it results in undefined behavior.
   *
   * @return - reversed iterator to the element following the last element
   */
  reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  /**
   * Capacity
   */

  /**
   * Checks if the container has no elements.
   *
   * @return - true if the container is empty, false otherwise
   */
  [[nodiscard]] bool empty() const noexcept {
    return begin() == end();
  }

  /**
   * Returns the number of elements in the container.
   *
   * @return - the number of elements in the container
   */
  [[nodiscard]] size_type size() const noexcept {
    return std::distance(begin(), end());
  }

  /**
   * Modifiers
   */

  /**
   * Erases all elements from the container. After this call,
   * size() returns zero.
   *
   * Invalidates any reference, pointer, or iterators referring to contained
   * elements. Any past-the-end iterator remains valid.
   */
  void clear() noexcept {
    size_type oldSize = _size;
    for (size_type i = 0; i < oldSize; i++) {
      auto p = _head->next;
      p->remove(_head, p->next);
    }
    _size = 0;
  }

  /**
   * Inserts @value before @pos.
   *
   * @pos - iterator before which the content will be inserted
   * @value - element value to insert
   * @return - iterator pointing to the inserted @value
   */
  iterator insert(iterator pos, const T &value) {
    node *newp = new list_node<T>(value);
    newp->insert(pos._node->prev, pos._node);
    _size++;
    return pos;
  }
  iterator insert(iterator pos, T &&value) {
    node *newp = new list_node<T>(std::move(value));
    newp->insert(pos._node->prev, pos._node);
    _size++;
    return pos;
  }

  /**
   * Inserts @count copies of the @value before @pos.
   *
   * @pos - iterator before which the content will be inserted
   * @count - number of elements to insert
   * @value - element value to insert
   * @return - iterator pointing to the first element inserted
   */
  iterator insert(iterator pos, size_type count, const T &value) {
    for (size_type i = 0; i < count; i++) {
      node *newp = new list_node<T>(value);
      newp->insert(pos._node->prev, pos._node);
      _size++;
    }
    return pos;
  }

  /**
   * Inserts elements from initializer list @ilist before @pos.
   *
   * @pos - iterator before which the content will be inserted
   * @ilist - initializer list to insert the values from
   * @return - iterator pointing to the first element inserted
   */
  iterator insert(iterator pos, std::initializer_list<T> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      node *newp = new list_node<T>(*it);
      newp->insert(pos._node->prev, pos._node);
      _size++;
    }
    return pos;
  }

  /**
   * Inserts a new element into the container directly before pos.
   *
   * @pos - iterator before which the new element will be constructed
   * @args - arguments to forward to the constructor of the element
   * @return - iterator pointing to the emplaces element
   */
  template<class... Args>
  iterator emplace(iterator pos, Args &&...args) {
    auto value = new T(std::forward<Args>(args)...);
    return insert(pos, std::move(*value));
  }

  /**
   * Removes the elements at @pos.
   *
   * References and iterators to the erased elements are invalidated.
   * Other references and iterators are not affected.
   *
   * @pos - iterator to the element to remove
   * @return - iterator following the last removed element. if @pos refers to
   *           the last element, then the end() iterator is returned.
   */
  iterator erase(iterator pos) {
    remove(pos);
    return pos == (end()) ? end() : pos;
  }

  /**
   * Removes the elements in the range [@first, @last).
   *
   * References and iterators to the erased elements are invalidated.
   * Other references and iterators are not affected.
   *
   * @first, @last - range of elements to remove
   * @return - iterator following the last removed element.
   *           if @last == end() prior to removal, then the updated end()
   *           iterator is returned.
   *           if [@first, @last) is an empty range, then last is returned.
   */
  iterator erase(iterator first, iterator last) {
    auto firstp = first._node;
    auto lastp = last._node;
    firstp->prev->next = lastp;
    lastp->prev = firstp->prev;
    _size -= std::distance(first, last);
    if (last == end()) {
      return end();
    }
    if (first == last) {
      return last;
    }
    return last;
  }

  /**
   * Appends the given element value to the end of the container.
   * The new element is initialized as a copy of value.
   *
   * @value - the value of the element to append
   */
  void push_back(const T &value) {
    auto newp = new list_node<T>(value);
    newp->insert(_head->prev, _head);
    _size++;
  }

  /**
   * Appends the given element value to the end of the container.
   * value is moved into the new element.
   *
   * @value - the value of the element to append
   */
  void push_back(T &&value) {
    auto newp = new list_node<T>(std::move(value));
    newp->insert(_head->prev, _head);
    _size++;
  }

  /**
   * Appends a new element to the end of the container.
   *
   * @args - arguments to forward to the constructor of the element
   * @return - a reference to the inserted element
   */
  template<class... Args>
  reference emplace_back(Args &&...args) {
    auto value = new T(std::forward<Args>(args)...);
    push_back(std::move(*value));
    return *value;
  }

  /**
   * Removes the last element of the container.
   * Calling pop_back on an empty container results in undefined behavior.
   * References and iterators to the erased element are invalidated.
   */
  void pop_back() {
    auto last = _head->prev;
    last->remove(last->prev, last->next);
    _size--;
  }

  /**
   * Prepends the given element value to the beginning of the container.
   * No iterators of references are invalidated.
   *
   * @value - the value of the element to prepend
   */
  void push_front(const T &value) {
    auto newp = new list_node<T>(value);
    newp->insert(_head, _head->next);
    _size++;
  }
  void push_front(T &&value) {
    auto newp = new list_node<T>(std::move(value));
    newp->insert(_head, _head->next);
    _size++;
  }

  /**
   * Inserts a new element to the beginning of the container.
   *
   * @args - arguments to forward to the constructor of the element
   * @return - a reference to the inserted element
   */
  template<class... Args>
  reference emplace_front(Args &&...args) {
    auto value = new T(std::forward<Args>(args)...);
    push_front(*value);
    return *value;
  }

  /**
   * Removes the first element of the container. If there are no elements in the
   * container, the behavior is undefined.
   * References and iterators to the erased element are invalidated.
   */
  void pop_front() {
    auto first = _head->next;
    first->remove(first->prev, first->next);
    _size--;
  }

  /**
   * Resize the container to contain @count elements,
   * does nothing if @count == size().
   *
   * If the current size is greater than @count, the container is reduced to
   * its first @count element.
   *
   * If the current size is less than @count, additional default-inserted
   * elements are appended.
   *
   * @count - new size of the container
   */
  void resize(size_type count) {
    size_type oldSize = size();
    if (count > oldSize) {
      for (size_type i = 0; i < (count - oldSize); i++) {
        push_back(0);
      }
    } else if (count < oldSize) {
      for (size_type i = 0; i < (oldSize - count); i++) {
        pop_back();
      }
    }
    // else, do nothing
  }

  /**
   * Resize the container to contain @count elements,
   * does nothing if @count == size().
   *
   * If the current size is greater than @count, the container is reduced to
   * its first @count element.
   *
   * If the current size is less than @count, additional copies of @value are
   * appended.
   *
   * @count - new size of the container
   * @value - the value to initialize the new elements with
   */
  void resize(size_type count, const value_type &value) {
    size_type oldSize = size();
    if (count > oldSize) {
      for (size_type i = 0; i < (count - oldSize); i++) {
        push_back(value);
      }
    } else if (count < oldSize) {
      for (size_type i = 0; i < (oldSize - count); i++) {
        pop_back();
      }
    }
  }

  /**
   * Exchanges the contents of the container with those of @other.
   * Does not invoke any move, copy, or swap operations on individual elements.
   *
   * All iterators and references remain valid. It is unspecified whether an
   * iterator holding the end() value in this container will refer to this or
   * the other container after the operation.
   *
   * @other - container to exchange the contents with
   */
  void swap(list &other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
  }

  /**
   * Operations
   */

  /**
   * The function does nothing if @other refers to the same object as @*this.
   *
   * Otherwise, merges two sorted lists into one. The lists should be sorted
   * into ascending order. No elements are copied, and the container @other
   * becomes empty after the merge. No iterators or references become
   * invalidated, except that the iterators of moved elements now refer into
   * @*this, not into @other. The first version uses operator < to compare the
   * elements, the second version uses the given comparison function @comp.
   *
   * @other - another container to merge
   */
  void merge(list &other) {
    if (this->_head != other._head) {
      assert(this->sorted() && other.sorted());
      list<T> old(std::move(*this));
      this->_head = new list_node<T>();
      auto it1 = old.begin();
      auto it2 = other.begin();
      while (it1 != old.end() && it2 != other.end()) {
        if (*it1 < *it2) {
          auto newp = new list_node<T>(*it1);
          newp->insert(this->_head->prev, this->_head);
          it1++;
        } else {
          auto newp = new list_node<T>(*it2);
          newp->insert(this->_head->prev, this->_head);
          other.remove(*it2);
          it2++;
        }
        this->_size++;
      }
      while (it1 != old.end()) {
        auto newp = new list_node<T>(*it1);
        newp->insert(this->_head->prev, this->_head);
        it1++;
        this->_size++;
      }
      while (it2 != other.end()) {
        auto newp = new list_node<T>(*it2);
        newp->insert(this->_head->prev, this->_head);
        other.remove(*it2);
        it2++;
        this->_size++;
      }
    }
    // else, do nothing
  }

  void merge(list &&other) {
    if (this->_head != other._head) {
      assert(this->sorted() && other.sorted());
      list<T> old(std::move(*this));
      this->_head = new list_node<T>();
      auto it1 = old.begin();
      auto it2 = other.begin();
      while (it1 != old.end() && it2 != other.end()) {
        if (*it1 < *it2) {
          auto newp = new list_node<T>(*it1);
          newp->insert(this->_head->prev, this->_head);
          it1++;
        } else {
          auto newp = new list_node<T>(*it2);
          newp->insert(this->_head->prev, this->_head);
          other.remove(*it2);
          it2++;
        }
        this->_size++;
      }
      while (it1 != old.end()) {
        auto newp = new list_node<T>(*it1);
        newp->insert(this->_head->prev, this->_head);
        it1++;
        this->_size++;
      }
      while (it2 != other.end()) {
        auto newp = new list_node<T>(*it2);
        newp->insert(this->_head->prev, this->_head);
        other.remove(*it2);
        it2++;
        this->_size++;
      }
    }
    // else, do nothing
  }

  template<class Compare>
  void merge(list &other, Compare comp) {
    if (this->_head != other._head) {
      assert(this->sorted(comp) && other.sorted(comp));
      list<T> old(std::move(*this));
      this->_head = new list_node<T>();
      auto it1 = old.begin();
      auto it2 = other.begin();
      while (it1 != old.end() && it2 != other.end()) {
        if (comp(*it1, *it2) == true) {
          auto newp = new list_node<T>(*it1);
          newp->insert(this->_head->prev, this->_head);
          it1++;
        } else {
          auto newp = new list_node<T>(*it2);
          newp->insert(this->_head->prev, this->_head);
          other.remove(*it2);
          it2++;
        }
        this->_size++;
      }
      while (it1 != old.end()) {
        auto newp = new list_node<T>(*it1);
        newp->insert(this->_head->prev, this->_head);
        it1++;
        this->_size++;
      }
      while (it2 != other.end()) {
        auto newp = new list_node<T>(*it2);
        newp->insert(this->_head->prev, this->_head);
        other.remove(*it2);
        it2++;
        this->_size++;
      }
    }
    // else, do nothing
  }

  template<class Compare>
  void merge(list &&other, Compare comp) {
    if (this->_head != other._head) {
      assert(this->sorted(comp) && other.sorted(comp));
      list<T> old(std::move(*this));
      this->_head = new list_node<T>();
      auto it1 = old.begin();
      auto it2 = other.begin();
      while (it1 != old.end() && it2 != other.end()) {
        if (comp(*it1, *it2)) {
          auto newp = new list_node<T>(*it1);
          newp->insert(this->_head->prev, this->_head);
          it1++;
        } else {
          auto newp = new list_node<T>(*it2);
          newp->insert(this->_head->prev, this->_head);
          other.remove(*it2);
          it2++;
        }
        this->_size++;
      }
      while (it1 != old.end()) {
        auto newp = new list_node<T>(*it1);
        newp->insert(this->_head->prev, this->_head);
        it1++;
        this->_size++;
      }
      while (it2 != other.end()) {
        auto newp = new list_node<T>(*it2);
        newp->insert(this->_head->prev, this->_head);
        other.remove(*it2);
        it2++;
        this->_size++;
      }
    }
    // else, do nothing
  }

  /**
   * Transfers elements from one list to another.
   *
   * @pos - element before which the content will be inserted
   * @other - another container to transfer the content from
   */
  void splice(iterator pos, list &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, std::move(*it));
    }
    other.clear();
  }

  void splice(iterator pos, list &&other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, std::move(*it));
    }
    other.clear();
  }

  void splice(iterator pos, list &other, iterator it) {
    this->insert(pos, std::move(*it));
    auto itp = other.begin();
    while (itp != it) {
      itp++;
    }
    itp._node->remove(itp._node->prev, itp._node->next);
  }

  void splice(iterator pos, list &&other, iterator it) {
    this->insert(pos, std::move(*it));
    auto itp = other.begin();
    while (itp != it) {
      itp++;
    }
    itp._node->remove(itp._node->prev, itp._node->next);
  }

  void splice(iterator pos, list &other, iterator first, iterator last) {
    for (auto it = first; it != last; ++it) {
      this->insert(pos, *it);
    }
    auto p1 = first._node->prev;
    auto p2 = last._node;
    p1->next = p2;
    p2->prev = p1;
  }

  void splice(iterator pos, list &&other, iterator first, iterator last) {
    for (auto it = first; it != last; ++it) {
      this->insert(pos, std::move(*it));
    }
    auto p1 = first._node->prev;
    auto p2 = last._node;
    p1->next = p2;
    p2->prev = p1;
  }

  /**
   * Removes all elements that are equal to @value
   *
   * @value - value of the elements to remove
   * @return - the number of elements removed
   */
  size_type remove(const T &value) {
    size_type removal = 0;
    auto it = begin();
    while (it != end()) {
      if (*it == value) {
        removal++;
        auto *currp = it._node;
        currp->prev->next = currp->next;
        currp->next->prev = currp->prev;
        _size--;
      }
      it++;
    }
    return removal;
  }

  /**
   * Removes all elements for which predicate p returns true.
   *
   * @p - unary predicate which returns true if the element should be removed
   * @return - the number of elements removed
   */
  template<class UnaryPredicate>
  size_type remove_if(UnaryPredicate p) {
    size_type removal = 0;
    auto it = begin();
    while (it != end()) {
      if (p(*it) == true) {
        removal++;
        auto *currp = it._node;
        currp->prev->next = currp->next;
        currp->next->prev = currp->prev;
        _size--;
      }
      it++;
    }
    return removal;
  }

  /**
   * Reverses the order of the elements in the container. No references or
   * iterators become invalidated.
   */
  void reverse() noexcept {
    auto i = _head->next;
    auto j = _head->prev;
    while (i < j) {
      std::swap(i->data, j->data);
      i = i->next;
      j = j->prev;
    }
  }

  /**
   * Removes all consecutive duplicate elements from the container. Only the
   * first element in each group of equal elements is left. The behavior is
   * undefined if the selected comparator does not establish an equivalence
   * relation.
   *
   * Use operator == to compare the elements
   *
   * @return - the number of elements removed
   */
  size_type unique() {
    size_type count = 0;
    auto it = this->begin();
    while (it != this->end()) {
      auto next = it;
      next++;
      while (next != this->end()) {
        if (*it == *next) {
          next++;
        } else {
          break;
        }
      }
      size_type size = std::distance(it, next);
      if (size > 1) {
        for (size_type i = 0; i < size - 1; i++) {
          auto p = it;
          p++;
          p._node->remove(p._node->prev, p._node->next);
          count++;
        }
      }
      it = next;
    }
    this->_size -= count;
    return count;
  }

  /**
   * Removes all consecutive duplicate elements from the container. Only the
   * first element in each group of equal elements is left. The behavior is
   * undefined if the selected comparator does not establish an equivalence
   * relation.
   *
   * Use the given binary predicate p to compare the elements
   *
   * @p - binary predicate which returns true if the elements should be treated
   *      as equal
   *
   * @return - the number of elements removed
   */
  template<class BinaryPredicate>
  size_type unique(BinaryPredicate p) {
    size_type count = 0;
    auto it = this->begin();
    while (it != this->end()) {
      auto next = it;
      next++;
      while (next != this->end()) {
        if (p(*it, *next) == true) {
          next++;
        } else {
          break;
        }
      }
      size_type size = std::distance(it, next);
      if (size > 1) {
        for (size_type i = 0; i < size - 1; i++) {
          auto currp = it;
          currp++;
          currp._node->remove(currp._node->prev, currp._node->next);
          count++;
        }
      }
      it = next;
    }
    this->_size -= count;
    return count;
  }

  /**
   * Sorts the elements in ascending order.
   *
   * The first version uses operator < to compare the elements.
   * The second version uses the given comparison function comp.
   */
  void sort() {
    auto sorted = end();
    while (begin() != sorted) {
      auto max = select_max(begin(), sorted);
      insert(sorted, *max);
      remove(max);
      sorted--;
    }
  }

  template<class Compare>
  void sort(Compare comp) {
    auto sorted = end();
    while (begin() != sorted) {
      auto max = select_max(begin(), sorted, comp);
      insert(sorted, *max);
      remove(max);
      sorted--;
    }
  }

  template<class Lambda>
  void for_each(iterator first, iterator last, Lambda &&lambda) {
    for (auto it = first; it != last; ++it) {
      lambda(*it);
    }
  }

  template<class Lambda>
  void for_each(const_iterator first, const_iterator last, Lambda &&lambda) {
    for (auto it = first; it != last; ++it) {
      lambda(*it);
    }
  }

  template<class Lambda>
  void for_each(reverse_iterator first, reverse_iterator last, Lambda &&lambda) {
    for (auto it = first; it != last; ++it) {
      lambda(*it);
    }
  }

  template<class Lambda>
  void for_each(const_reverse_iterator first, const_reverse_iterator last, Lambda &&lambda) {
    for (auto it = first; it != last; ++it) {
      lambda(*it);
    }
  }

  void print() {
    std::cout << "list: [ ";
    for (auto p = begin(); p != end(); ++p) {
      std::cout << *p << " ";
    }
    std::cout << "]\n";
  }

  template<class Lambda>
  void print(Lambda &&lambda) {
    std::cout << "list(" << _size << "): [ ";
    for (auto it = begin(); it != end(); ++it) {
      lambda(*it);
      std::cout << " ";
    }
    std::cout << "]\n";
  }
};

/**
 * Non-member functions
 */

template<class T>
bool operator==(const stl::list<T> &lhs, const stl::list<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (auto liter = lhs.begin(), riter = rhs.begin(); liter != lhs.end(); ++liter, ++riter) {
    if (!(*liter == *riter)) {
      return false;
    }
  }
  return true;
}

template<class T>
void swap(stl::list<T> &lhs, stl::list<T> &rhs) noexcept {
  lhs.swap(rhs);
}

template<class T, class U>
typename stl::list<T>::size_type erase(stl::list<T> &c, const U &value) {
  typename stl::list<T>::size_type size = 0;
  auto it = c.begin();
  auto next = it;
  while (it != c.end()) {
    if (*it == value) {
      size++;
      next = it;
      next++;
      c.erase(it);
      it = next;
    } else {
      it++;
    }
  }
  return size;
}

template<class T, class Pred>
typename stl::list<T>::size_type erase_if(stl::list<T> &c, Pred pred) {
  typename stl::list<T>::size_type size = 0;
  auto it = c.begin();
  auto next = it;
  while (it != c.end()) {
    if (pred(*it)) {
      size++;
      next = it;
      next++;
      c.erase(it);
      it = next;
    } else {
      it++;
    }
  }
  return size;
}

}// namespace stl

#endif//CPP_STL_LIST_H
