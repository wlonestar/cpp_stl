//
// Created by wjl on 2023/4/17.
//

#ifndef CPP_STL_LIST_H
#define CPP_STL_LIST_H

#pragma once

#include "util.h"

#include <cassert>
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

  bool sorted();
  template<class Compare>
  bool sorted(Compare comp);

  iterator select_max(iterator first, iterator last);
  template<class Compare>
  iterator select_max(iterator first, iterator last, Compare comp);

  void remove(iterator pos);

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

  iterator insert(iterator pos, const T &value);
  iterator insert(iterator pos, T &&value);
  iterator insert(iterator pos, size_type count, const T &value);
  iterator insert(iterator pos, std::initializer_list<T> ilist);

  template<class... Args>
  iterator emplace(iterator pos, Args &&...args);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

  void push_back(const T &value);
  void push_back(T &&value);

  template<class... Args>
  reference emplace_back(Args &&...args);

  void pop_back();

  void push_front(const T &value);
  void push_front(T &&value);

  template<class... Args>
  reference emplace_front(Args &&...args);

  void pop_front();

  void resize(size_type count);
  void resize(size_type count, const value_type &value);

  void swap(list &other) noexcept;

  /**
   * Operations
   */

  void merge(list &other);
  void merge(list &&other);
  template<class Compare>
  void merge(list &other, Compare comp);
  template<class Compare>
  void merge(list &&other, Compare comp);

  void splice(iterator pos, list &other);
  void splice(iterator pos, list &&other);
  void splice(iterator pos, list &other, iterator it);
  void splice(iterator pos, list &&other, iterator it);
  void splice(iterator pos, list &other, iterator first, iterator last);
  void splice(iterator pos, list &&other, iterator first, iterator last);

  size_type remove(const T &value);
  template<class UnaryPredicate>
  size_type remove_if(UnaryPredicate p);

  void reverse() noexcept;

  size_type unique();
  template<class BinaryPredicate>
  size_type unique(BinaryPredicate p);

  void sort();
  template<class Compare>
  void sort(Compare comp);

  template<class Lambda>
  void for_each(iterator first, iterator last, Lambda &&lambda);
  template<class Lambda>
  void for_each(const_iterator first, const_iterator last, Lambda &&lambda);
  template<class Lambda>
  void for_each(reverse_iterator first, reverse_iterator last, Lambda &&lambda);
  template<class Lambda>
  void for_each(const_reverse_iterator first, const_reverse_iterator last, Lambda &&lambda);

  template<class Lambda>
  void print(Lambda &&lambda);

  void print() {
    std::cout << "list: [ ";
    for (auto p = begin(); p != end(); ++p) {
      std::cout << *p << " ";
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

template<class T>
bool list<T>::sorted() {
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

template<class T>
template<class Compare>
bool list<T>::sorted(Compare comp) {
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

template<class T>
list<T>::iterator list<T>::select_max(list::iterator first, list::iterator last) {
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

template<class T>
template<class Compare>
list<T>::iterator list<T>::select_max(list::iterator first, list::iterator last, Compare comp) {
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

template<class T>
void list<T>::remove(list::iterator pos) {
  pos._node->remove(pos._node->prev, pos._node->next);
  _size--;
}

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
list<T>::iterator list<T>::insert(list::iterator pos, const T &value) {
  node *newp = new list_node<T>(value);
  newp->insert(pos._node->prev, pos._node);
  _size++;
  return pos;
}

template<class T>
list<T>::iterator list<T>::insert(list::iterator pos, T &&value) {
  node *newp = new list_node<T>(std::move(value));
  newp->insert(pos._node->prev, pos._node);
  _size++;
  return pos;
}

template<class T>
list<T>::iterator list<T>::insert(list::iterator pos, list::size_type count, const T &value) {
  for (size_type i = 0; i < count; i++) {
    node *newp = new list_node<T>(value);
    newp->insert(pos._node->prev, pos._node);
    _size++;
  }
  return pos;
}

template<class T>
list<T>::iterator list<T>::insert(list::iterator pos, std::initializer_list<T> ilist) {
  for (auto it = ilist.begin(); it != ilist.end(); ++it) {
    node *newp = new list_node<T>(*it);
    newp->insert(pos._node->prev, pos._node);
    _size++;
  }
  return pos;
}

template<class T>
template<class... Args>
list<T>::iterator list<T>::emplace(list::iterator pos, Args &&...args) {
  auto value = new T(std::forward<Args>(args)...);
  return insert(pos, *value);
}

template<class T>
list<T>::iterator list<T>::erase(list::iterator pos) {
//  auto removep = pos._node;
  remove(pos);
//  removep->remove(removep->prev, removep->next);
//  _size--;
  return pos == (end()) ? end() : pos;
}

template<class T>
list<T>::iterator list<T>::erase(list::iterator first, list::iterator last) {
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

template<class T>
void list<T>::push_back(const T &value) {
  auto newp = new list_node<T>(value);
  newp->insert(_head->prev, _head);
  _size++;
}

template<class T>
void list<T>::push_back(T &&value) {
  auto newp = new list_node<T>(std::move(value));
  newp->insert(_head->prev, _head);
  _size++;
}

template<class T>
template<class... Args>
list<T>::reference list<T>::emplace_back(Args &&...args) {
  auto value = new T(std::forward<Args>(args)...);
  push_back(*value);
  return *value;
}

template<class T>
void list<T>::pop_back() {
  auto last = _head->prev;
  last->remove(last->prev, last->next);
  _size--;
}

template<class T>
void list<T>::push_front(const T &value) {
  auto newp = new list_node<T>(value);
  newp->insert(_head, _head->next);
  _size++;
}

template<class T>
void list<T>::push_front(T &&value) {
  auto newp = new list_node<T>(std::move(value));
  newp->insert(_head, _head->next);
  _size++;
}

template<class T>
template<class... Args>
list<T>::reference list<T>::emplace_front(Args &&...args) {
  auto value = new T(std::forward<Args>(args)...);
  push_front(*value);
  return *value;
}

template<class T>
void list<T>::pop_front() {
  auto first = _head->next;
  first->remove(first->prev, first->next);
  _size--;
}

template<class T>
void list<T>::resize(list::size_type count) {
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

template<class T>
void list<T>::resize(list::size_type count, const value_type &value) {
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

template<class T>
void list<T>::swap(list &other) noexcept {
  std::swap(_head, other._head);
  std::swap(_size, other._size);
}

template<class T>
void list<T>::merge(list &other) {
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

template<class T>
void list<T>::merge(list &&other) {
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

template<class T>
template<class Compare>
void list<T>::merge(list &other, Compare comp) {
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

template<class T>
template<class Compare>
void list<T>::merge(list &&other, Compare comp) {
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

template<class T>
void list<T>::splice(list::iterator pos, list &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(pos, std::move(*it));
  }
  other.clear();
}

template<class T>
void list<T>::splice(list::iterator pos, list &&other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(pos, std::move(*it));
  }
  other.clear();
}

template<class T>
void list<T>::splice(list::iterator pos, list &other, list::iterator it) {
  this->insert(pos, std::move(*it));
  auto itp = other.begin();
  while (itp != it) {
    itp++;
  }
  itp._node->remove(itp._node->prev, itp._node->next);
}

template<class T>
void list<T>::splice(list::iterator pos, list &&other, list::iterator it) {
  this->insert(pos, std::move(*it));
  auto itp = other.begin();
  while (itp != it) {
    itp++;
  }
  itp._node->remove(itp._node->prev, itp._node->next);
}

template<class T>
void list<T>::splice(list::iterator pos, list &other, list::iterator first, list::iterator last) {
  for (auto it = first; it != last; ++it) {
    this->insert(pos, *it);
  }
  auto p1 = first._node->prev;
  auto p2 = last._node;
  p1->next = p2;
  p2->prev = p1;
}

template<class T>
void list<T>::splice(list::iterator pos, list &&other, list::iterator first, list::iterator last) {
  for (auto it = first; it != last; ++it) {
    this->insert(pos, std::move(*it));
  }
  auto p1 = first._node->prev;
  auto p2 = last._node;
  p1->next = p2;
  p2->prev = p1;
}

template<class T>
list<T>::size_type list<T>::remove(const T &value) {
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

template<class T>
template<class UnaryPredicate>
list<T>::size_type list<T>::remove_if(UnaryPredicate p) {
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

template<class T>
void list<T>::reverse() noexcept {
  auto i = _head->next;
  auto j = _head->prev;
  while (i < j) {
    std::swap(i->data, j->data);
    i = i->next;
    j = j->prev;
  }
}

template<class T>
list<T>::size_type list<T>::unique() {
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

template<class T>
template<class BinaryPredicate>
list<T>::size_type list<T>::unique(BinaryPredicate p) {
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

template<class T>
void list<T>::sort() {
  auto sorted = end();
  while (begin() != sorted) {
    auto max = select_max(begin(), sorted);
    insert(sorted, *max);
    remove(max);
    sorted--;
  }
}

template<class T>
template<class Compare>
void list<T>::sort(Compare comp) {
  auto sorted = end();
  while (begin() != sorted) {
    auto max = select_max(begin(), sorted, comp);
    insert(sorted, *max);
    remove(max);
    sorted--;
  }
}

template<class T>
template<class Lambda>
void list<T>::for_each(list::iterator first, list::iterator last, Lambda &&lambda) {
  for (auto it = first; it != last; ++it) {
    lambda(*it);
  }
}

template<class T>
template<class Lambda>
void list<T>::for_each(list::const_iterator first, list::const_iterator last, Lambda &&lambda) {
  for (auto it = first; it != last; ++it) {
    lambda(*it);
  }
}

template<class T>
template<class Lambda>
void list<T>::for_each(list::reverse_iterator first, list::reverse_iterator last, Lambda &&lambda) {
  for (auto it = first; it != last; ++it) {
    lambda(*it);
  }
}

template<class T>
template<class Lambda>
void list<T>::for_each(list::const_reverse_iterator first, list::const_reverse_iterator last, Lambda &&lambda) {
  for (auto it = first; it != last; ++it) {
    lambda(*it);
  }
}

template<class T>
template<class Lambda>
void list<T>::print(Lambda &&lambda) {
  std::cout << "list(" << _size << "): [ ";
  for (auto it = begin(); it != end(); ++it) {
    lambda(*it);
    std::cout << " ";
  }
  std::cout << "]\n";
}

}// namespace stl

#endif//CPP_STL_LIST_H
