//
// Created by wjl on 2023/5/8.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include "util.h"

#include <initializer_list>
#include <iostream>
#include <tuple>

namespace stl {

/**
 * rbtree color type
 */
enum rb_color {
  RB_RED,
  RB_BLACK,
};

/**
 * rbtree side type
 */
enum rb_side {
  RB_LEFT,
  RB_RIGHT,
};

/**
 * rbtree node base type
 *
 * separate data fom node
 */
struct rb_node_base {
private:
  typedef rb_node_base this_type;

public:
  this_type *parent;
  this_type *left;
  this_type *right;
  char color;
};

rb_node_base *rb_increment(const rb_node_base *p);
rb_node_base *rb_decrement(const rb_node_base *p);
rb_node_base *rb_min_child(const rb_node_base *p);
rb_node_base *rb_max_child(const rb_node_base *p);
std::size_t rb_black_count(const rb_node_base *top, const rb_node_base *bottom);
rb_node_base *rb_rotate_left(rb_node_base *p, rb_node_base *root);
rb_node_base *rb_rotate_right(rb_node_base *p, rb_node_base *root);
void rb_insert(rb_node_base *p, rb_node_base *parent, rb_side side);
void rb_erase(rb_node_base *p, rb_node_base *parent);

/**
 * rbtree node type
 */
template<class T>
struct rbtree_node : rb_node_base {
public:
  T value;

public:
  rbtree_node();
  rbtree_node(const T &val, rbtree_node<T> *parent = nullptr,
              rbtree_node<T> *left = nullptr, rbtree_node<T> *right = nullptr);

  rbtree_node<T> *insert(const T &val, rb_side side);
  rbtree_node<T> *succ();

  /**
   * Debug
   */

  void print();
};

/**
 * rbtree iterator
 */
template<class T, class Pointer, class Reference>
struct rbtree_iterator {
  typedef rbtree_iterator<T, Pointer, Reference> this_type;
  typedef rbtree_iterator<T, T *, T &> iterator;
  typedef rbtree_iterator<T, const T *, const T &> const_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t dirrerence_type;
  typedef T value_type;
  typedef rb_node_base base_node_type;
  typedef rbtree_node<T> node_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef std::bidirectional_iterator_tag iterator_category;

public:
  node_type *node;

public:
  rbtree_iterator();
  explicit rbtree_iterator(const node_type *node);
  rbtree_iterator(const iterator &x);

  rbtree_iterator &operator=(const iterator &x);

  reference operator*() const;
  pointer operator->() const;

  rbtree_iterator &operator++();
  rbtree_iterator operator++(int);

  rbtree_iterator &operator--();
  rbtree_iterator operator--(int);
};

/**
 * rbtree
 */
template<class Key, class T, class Compare>
class rbtree {
public:
  /**
   * Member types
   */

  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Key key_type;
  typedef T value_type;
  typedef rbtree_node<value_type> node_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  typedef Compare key_compare;
  typedef rbtree<Key, T, Compare> this_type;

protected:
  node_type *_root;
  size_type _size;

public:
  /**
   * Member functions
   */

  rbtree();
  rbtree(const Compare &compare);
  rbtree(const this_type &x);
  rbtree(this_type &&x);
  ~rbtree();

  this_type &operator=(const this_type &x);
  this_type &operator=(std::initializer_list<value_type> ilist);
  this_type &operator=(this_type &&x);

  /**
   * Element access
   */

  T &operator[](const key_type &key);
  T &operator[](key_type &&key);

  /**
   * Iterators
   */

  // TODO

  /**
   * Capacity
   */

  bool empty() const;
  size_type size() const;

  /**
   * Modifiers
   */

  void clear() noexcept;
  // TODO: insert

  /**
   * Lookup
   */

  size_type count(const Key &key) const;
  template<class K>
  size_type count(const K &x) const;
  // TODO: find
  bool contains(const Key &key) const;
  template<class K>
  bool contains(const K &x) const;

  /**
   * Traverse
   */

  // TODO
};

/**
 * rbtree node base functions
 */

// TODO
rb_node_base *rb_increment(const rb_node_base *p) {
  TODO();
}

// TODO
rb_node_base *rb_decrement(const rb_node_base *p) {
  TODO();
}

// TODO
rb_node_base *rb_min_child(const rb_node_base *p) {
  TODO();
}

// TODO
rb_node_base *rb_max_child(const rb_node_base *p) {
  TODO();
}

// TODO
std::size_t rb_black_count(const rb_node_base *top, const rb_node_base *bottom) {
  TODO();
}

// TODO
rb_node_base *rb_rotate_left(rb_node_base *p, rb_node_base *root) {
  TODO();
}

// TODO
rb_node_base *rb_rotate_right(rb_node_base *p, rb_node_base *root) {
  TODO();
}

// TODO
void rb_insert(rb_node_base *p, rb_node_base *parent, rb_side side) {
  TODO();
}

// TODO
void rb_erase(rb_node_base *p, rb_node_base *parent) {
  TODO();
}

/**
 * rbtree node implementation
 */

template<class T>
rbtree_node<T>::rbtree_node() : rb_node_base() {}

template<class T>
rbtree_node<T>::rbtree_node(const T &val, rbtree_node<T> *parent,
                            rbtree_node<T> *left, rbtree_node<T> *right)
    : value(val), rb_node_base(parent, left, right) {}

template<class T>
rbtree_node<T> *rbtree_node<T>::insert(const T &val, rb_side side) {
  rbtree_node<T> *new_node = new rbtree_node(val, this);
  if (side == RB_LEFT) {
    left = new_node;
  } else if (side == RB_RIGHT) {
    right = new_node;
  }
  return this;
}

template<class T>
rbtree_node<T> *rbtree_node<T>::succ() {
  return nullptr;
}

template<class T>
void rbtree_node<T>::print() {
  std::cout << "node(" << value << ", " << this << "): parent: " << parent << ", left: " << left << ", right: " << right << "\n";
}

/**
 * rbtree iterator implementation
 */

/**
 * rbtree implementation
 */


}// namespace stl

#endif//CPP_STL_TREE_H
