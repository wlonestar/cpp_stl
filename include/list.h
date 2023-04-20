//
// Created by wjl on 2023/4/17.
//

#ifndef CPP_STL_LIST_H
#define CPP_STL_LIST_H

#pragma once

#include "util.h"

#include <cstddef>
#include <iostream>
#include <iterator>

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

  list_node();
  explicit list_node(const T &value);

  void insert(list_node<T> *_prev, list_node<T> *_next);

  void remove(list_node<T> *_prev, list_node<T> *_next);
};

template<class T>
list_node<T>::list_node() {
  this->prev = this;
  this->next = this;
}

template<class T>
list_node<T>::list_node(const T &value) {
  data = value;
  this->prev = this;
  this->next = this;
}

template<class T>
void list_node<T>::insert(list_node<T> *_prev, list_node<T> *_next) {
  this->prev = _prev;
  _prev->next = this;
  this->next = _next;
  _next->prev = this;
}

template<class T>
void list_node<T>::remove(list_node<T> *_prev, list_node<T> *_next) {
  _prev->next = _next;
  _next->prev = _prev;
  this->prev = this;
  this->next = this;
}

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

public:
  /**
   * Member functions
   */

  list();
  explicit list(size_type count, const T &value);
  explicit list(size_type count);
  list(const list &other);
  list(list &&other) noexcept;
  list(std::initializer_list<T> init);

  ~list();

  list &operator=(const list &other);
  list &operator=(list &&other) noexcept;
  list &operator=(std::initializer_list<T> ilist);

  void assign(size_type count, const T &value);
  void assign(std::initializer_list<T> ilist);

  /**
   * Element access
   */

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  /**
   * Iterators
   */

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  const_reverse_iterator crbegin() const noexcept;

  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crend() const noexcept;

  /**
   * Capacity
   */

  [[nodiscard]] bool empty() const noexcept;

  [[nodiscard]] size_type size() const noexcept;

  /**
   * Modifiers
   */

  void clear() noexcept;

  iterator insert(const_iterator pos, const T &value);
  iterator insert(const_iterator pos, T &&value);
  iterator insert(const_iterator pos, size_type count, const T &value);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);


  void print() {
    std::cout << "list: [ ";
    for (auto p = begin(); p != end(); ++p) {
      std::cout << *p << " ";
    }
    std::cout << "]\n";
  }
};

template<class T>
list<T>::list() {
  _head = new list_node<T>();
  _size = 0;
}

template<class T>
list<T>::list(list::size_type count, const T &value) {
  _head = new list_node<T>();
  _size = count;
  for (size_type i = 0; i < count; i++) {
    node *_node = new list_node<T>(value);
    _node->insert(_head->prev, _head);
  }
}

template<class T>
list<T>::list(list::size_type count) {
  _head = new list_node<T>();
  _size = count;
  for (size_type i = 0; i < count; i++) {
    node *_node = new list_node<T>();
    _node->insert(_head->prev, _head);
  }
}

template<class T>
list<T>::list(const list &other) {
  _head = new list_node<T>();
  _size = other._size;
  for (auto *p = other._head->next; p != other._head; p = p->next) {
    auto *newp = new list_node<T>(p->data);
    newp->insert(_head->prev, _head);
  }
}

template<class T>
list<T>::list(list &&other) noexcept : _head(other._head) {
  _size = other._size;
  other._size = 0;
  other._head = nullptr;
}

template<class T>
list<T>::list(std::initializer_list<T> init) {
  _head = new list_node<T>();
  _size = init.size();
  for (auto it = init.begin(); it != init.end(); ++it) {
    node *_node = new list_node<T>(*it);
    _node->insert(_head->prev, _head);
  }
}

template<class T>
list<T>::~list() {
  delete _head;
}

template<class T>
list<T> &list<T>::operator=(const list &other) {
  _head = new list_node<T>();
  _size = other._size;
  for (auto *p = other._head->next; p != other._head; p = p->next) {
    auto *newp = new list_node<T>(p->data);
    newp->insert(_head->prev, _head);
  }
  return *this;
}

template<class T>
list<T> &list<T>::operator=(list &&other) noexcept {
  _size = other._size;
  _head = std::move(other._head);
  other._size = 0;
  other._head = nullptr;
  return *this;
}

template<class T>
list<T> &list<T>::operator=(std::initializer_list<T> ilist) {
  _head = new list_node<T>();
  _size = ilist.size();
  for (auto it = ilist.begin(); it != ilist.end(); ++it) {
    node *_node = new list_node<T>(*it);
    _node->insert(_head->prev, _head);
  }
  return *this;
}

template<class T>
void list<T>::assign(list::size_type count, const T &value) {
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

template<class T>
void list<T>::assign(std::initializer_list<T> ilist) {
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

template<class T>
list<T>::reference list<T>::front() {
  return _head->next->data;
}

template<class T>
list<T>::const_reference list<T>::front() const {
  return _head->next->data;
}

template<class T>
list<T>::reference list<T>::back() {
  return _head->prev->data;
}

template<class T>
list<T>::const_reference list<T>::back() const {
  return _head->prev->data;
}

template<class T>
list<T>::iterator list<T>::begin() noexcept {
  return iterator(_head->next);
}

template<class T>
list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator(_head->next);
}

template<class T>
list<T>::const_iterator list<T>::cbegin() const noexcept {
  return const_iterator(_head->next);
}

template<class T>
list<T>::iterator list<T>::end() noexcept {
  return iterator(_head);
}

template<class T>
list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator(_head);
}

template<class T>
list<T>::const_iterator list<T>::cend() const noexcept {
  return const_iterator(_head);
}

template<class T>
list<T>::reverse_iterator list<T>::rbegin() noexcept {
  return reverse_iterator(end());
}

template<class T>
list<T>::const_reverse_iterator list<T>::rbegin() const noexcept {
  return const_reverse_iterator(end());
}

template<class T>
list<T>::const_reverse_iterator list<T>::crbegin() const noexcept {
  return const_reverse_iterator(cend());
}

template<class T>
list<T>::reverse_iterator list<T>::rend() noexcept {
  return reverse_iterator(begin());
}

template<class T>
list<T>::const_reverse_iterator list<T>::rend() const noexcept {
  return const_reverse_iterator(begin());
}

template<class T>
list<T>::const_reverse_iterator list<T>::crend() const noexcept {
  return const_reverse_iterator(cbegin());
}

template<class T>
bool list<T>::empty() const noexcept {
  return begin() == end();
}

template<class T>
list<T>::size_type list<T>::size() const noexcept {
  return std::distance(begin(), end());
}

template<class T>
void list<T>::clear() noexcept {
  size_type oldSize = _size;
  for (size_type i = 0; i < oldSize; i++) {
    auto p = _head->next;
    p->remove(_head, p->next);
  }
  _size = 0;
}

template<class T>
list<T>::iterator list<T>::insert(list::const_iterator pos, const T &value) {
  TODO();
}

template<class T>
list<T>::iterator list<T>::insert(list::const_iterator pos, T &&value) {
  TODO();
}

template<class T>
list<T>::iterator list<T>::insert(list::const_iterator pos, list::size_type count, const T &value) {
  TODO();
}

template<class T>
list<T>::iterator list<T>::insert(list::const_iterator pos, std::initializer_list<T> ilist) {
  TODO();
}

}// namespace stl

#endif//CPP_STL_LIST_H
