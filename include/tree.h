//
// Created by wjl on 2023/4/24.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include "queue.h"
#include "stack.h"
#include "util.h"

#include <compare>
#include <iostream>
#include <utility>

namespace stl {

template<class Pair>
struct use_first {
  typedef Pair argument_type;
  typedef typename Pair::first_type result_type;

  const result_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template<class Pair>
struct use_second {
  typedef Pair argument_type;
  typedef typename Pair::second_type result_type;

  const result_type &operator()(const Pair &x) const {
    return x.first;
  }
};

enum RB_COLOR {
  RB_RED,
  RB_BLACK,
};

enum RB_SIDE {
  RB_LEFT,
  RB_RIGHT,
};

/**
 * Define a tree_node_base separately from tree_node (below),
 * because it allows to have non-templated operations.
 */
struct rbtree_node_base {
  typedef rbtree_node_base this_type;

public:
  this_type *right;
  this_type *left;
  this_type *parent;
  char color;
};

template<class Value>
struct rbtree_node : public rbtree_node_base {
  /**
   * For set and multiset, this is the user's value,
   * for map and multimap, this is a pair of key/value.
   */
  Value value;
};

rbtree_node_base *tree_increment(const rbtree_node_base *p);
rbtree_node_base *tree_decrement(const rbtree_node_base *p);
rbtree_node_base *tree_get_min_child(const rbtree_node_base *p);
rbtree_node_base *tree_get_max_child(const rbtree_node_base *p);
rbtree_node_base *tree_get_black_count(const rbtree_node_base *top, const rbtree_node_base *bottom);
rbtree_node_base *tree_insert(rbtree_node_base *p, rbtree_node_base *parent, rbtree_node_base *anchor, RB_SIDE insertion_side);
rbtree_node_base *tree_erase(rbtree_node_base *p, rbtree_node_base *anchor);

template<class T, class Pointer, class Reference>
struct rbtree_iterator {
  typedef rbtree_iterator<T, Pointer, Reference> this_type;
  typedef rbtree_iterator<T, T *, T &> iterator;
  typedef rbtree_iterator<T, const T *, const T &> const_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef rbtree_node_base base_node_type;
  typedef rbtree_node<T> node_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef std::bidirectional_iterator_tag iterator_category;

public:
  node_type *node;

public:
  rbtree_iterator();
  explicit rbtree_iterator(const node_type *p);
  rbtree_iterator(const iterator &x);

  rbtree_iterator &operator=(const iterator &x);

  reference operator*() const;
  pointer operator->() const;

  rbtree_iterator &operator++();
  rbtree_iterator operator++(int);

  rbtree_iterator &operator--();
  rbtree_iterator operator--(int);
};

template<class Compare, bool = std::is_empty<Compare>::value>
struct rb_base_compare_ebo {
private:
  Compare comp;

protected:
  rb_base_compare_ebo() : comp() {}
  rb_base_compare_ebo(const Compare &compare) : comp(compare) {}

  Compare &get_compare() {
    return comp;
  }

  const Compare &get_compare() const {
    return comp;
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) {
    return comp(lhs, rhs);
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) const {
    return comp(lhs, rhs);
  }
};

template<class Compare>
struct rb_base_compare_ebo<Compare, true> : private Compare {
protected:
  rb_base_compare_ebo() {}
  rb_base_compare_ebo(const Compare &compare) : Compare(compare) {}

  Compare &get_compare() {
    return *this;
  }

  const Compare &get_compare() const {
    return *this;
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) {
    return Compare::operator()(lhs, rhs);
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) const {
    return Compare::operator()(lhs, rhs);
  }
};

/**
 * This specialization is used for 'set'
 */
template<class Key, class Value, class Compare, class ExtractKey, bool UniqueKeys, class RBTree>
struct rb_base : public rb_base_compare_ebo<Compare> {
  typedef ExtractKey extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'multiset'
 */
template<class Key, class Value, class Compare, class ExtractKey, class RBTree>
struct rb_base<Key, Value, Compare, ExtractKey, false, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef ExtractKey extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'map'
 */
template<class Key, class Pair, class Compare, class RBTree>
struct rb_base<Key, Pair, Compare, use_first<Pair>, true, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef use_first<Pair> extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'multimap'
 */
template<class Key, class Pair, class Compare, class RBTree>
struct rb_base<Key, Pair, Compare, use_first<Pair>, false, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef use_first<Pair> extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

//TODO
template<class Key, class Value, class Compare, class ExtractKey, bool MutableIterators, bool UniqueKeys>
class rbtree : public rb_base<Key, Value, Compare, ExtractKey, UniqueKeys, rbtree<Key, Value, Compare, ExtractKey, MutableIterators, UniqueKeys>> {
public:
protected:
public:
public:
public:
public:
protected:
};

}// namespace stl

#endif//CPP_STL_TREE_H
