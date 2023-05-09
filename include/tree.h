//
// Created by wjl on 2023/5/8.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include <initializer_list>
#include <iostream>
#include <tuple>

#include "queue.h"
#include "stack.h"
#include "util.h"
#include "vector.h"

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

/**
 * rbtree node base functions
 */

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
 * rbtree node base traverse
 */

template<class T>
void rb_pre_order(rb_node_base *p, stl::vector<T> &v);
template<class T>
void rb_in_order(rb_node_base *p, stl::vector<T> &v);
template<class T>
void rb_post_order(rb_node_base *p, stl::vector<T> &v);
template<class T>
void rb_level_order(rb_node_base *p, stl::vector<T> &v);
template<class T>
void __rb_print(rb_node_base *p, int prefix);
template<class T>
void rb_print(rb_node_base *p);

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
  rbtree_node<T> *attach(rbtree_node<T> *p, rb_side side);

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
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef rb_node_base base_node_type;
  typedef rbtree_node<T> node_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef std::bidirectional_iterator_tag iterator_category;

public:
  node_type *node;

public:
  rbtree_iterator() : node(NULL) {}

  explicit rbtree_iterator(const node_type *node)
      : node(static_cast<node_type *>(const_cast<node_type *>(node))) {}

  rbtree_iterator(const iterator &x) : node(x.node) {}

  rbtree_iterator &operator=(const iterator &x) {
    node = x.node;
    return *this;
  }

  reference operator*() const { return node->value; }
  pointer operator->() const { return &node->value; }

  rbtree_iterator &operator++() {
    node = static_cast<node_type *>(rb_increment(node));
    return *this;
  }

  rbtree_iterator operator++(int) {
    this_type tmp(*this);
    node = static_cast<node_type *>(rb_increment(node));
    return tmp;
  }

  rbtree_iterator &operator--() {
    node = static_cast<node_type *>(rb_decrement(node));
    return *this;
  }

  rbtree_iterator operator--(int) {
    this_type tmp(*this);
    node = static_cast<node_type *>(rb_decrement(node));
    return tmp;
  }
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

rb_node_base *rb_increment(const rb_node_base *p) {
  if (p->right != nullptr) {
    p = p->right;
    while (p->left != nullptr) {
      p = p->left;
    }
  } else {
    rb_node_base *tmp = p->parent;
    while (p == tmp->right) {
      p = tmp;
      tmp = tmp->parent;
    }
    if (p->right != tmp) {
      p = tmp;
    }
  }
  return const_cast<rb_node_base *>(p);
}

rb_node_base *rb_decrement(const rb_node_base *p) {
  if (p->left != nullptr) {
    p = p->left;
    while (p->right != nullptr) {
      p = p->right;
    }
  } else {
    rb_node_base *tmp = p->parent;
    while (p == tmp->left) {
      p = tmp;
      tmp = tmp->parent;
    }
    if (p->left != tmp) {
      p = tmp;
    }
  }
  return const_cast<rb_node_base *>(p);
}

rb_node_base *rb_min_child(const rb_node_base *p) {
  while (p->left != nullptr) {
    p = p->left;
  }
  return const_cast<rb_node_base *>(p);
}

rb_node_base *rb_max_child(const rb_node_base *p) {
  while (p->right != nullptr) {
    p = p->right;
  }
  return const_cast<rb_node_base *>(p);
}

std::size_t rb_black_count(const rb_node_base *top, const rb_node_base *bottom) {
  size_t count = 0;
  for (; bottom; bottom = bottom->parent) {
    if (bottom->color == RB_BLACK) {
      ++count;
    }
    if (bottom == top) {
      break ;
    }
  }
  return count;
}

rb_node_base *rb_rotate_left(rb_node_base *p, rb_node_base *root) {
  rb_node_base *y = p->right;
  p->right = y->left;
  if (y->left != nullptr) {
    y->left->parent = p;
  }
  y->parent = p->parent;
  if (p == root) {
    root = y;
  } else if (p == p->parent->left) {
    p->parent->left = y;
  } else {
    p->parent->right = y;
  }
  y->left = p;
  p->parent = y;
  return root;
}

rb_node_base *rb_rotate_right(rb_node_base *p, rb_node_base *root) {
  rb_node_base *y = p->left;
  p->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = p;
  }
  y->parent = p->parent;
  if (p == root) {
    root = y;
  } else if (p == p->parent->right) {
    p->parent->right = y;
  } else {
    p->parent->left = y;
  }
  y->right = p;
  p->parent = y;
  return root;
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
 * rbtree node base traverse
 */

template<class T>
void rb_pre_order(rb_node_base *p, stl::vector<T> &v) {
  stack<rb_node_base *> s;
  while (true) {
    while (p != nullptr) {
      T val = static_cast<rbtree_node<T> *>(p)->value;
      v.push_back(val);
      s.push(p->right);
      p = p->left;
    }
    if (s.empty()) {
      break;
    }
    p = s.top();
    s.pop();
  }
}

template<class T>
void rb_in_order(rb_node_base *p, stl::vector<T> &v) {
  stack<rb_node_base *> s;
  while (true) {
    while (p != nullptr) {
      s.push(p);
      p = p->left;
    }
    if (s.empty()) {
      break;
    }
    p = s.top();
    s.pop();
    T val = static_cast<rbtree_node<T> *>(p)->value;
    v.push_back(val);
    p = p->right;
  }
}

static void goto_left(stack<rb_node_base *> &s) {
  while (auto p = s.top()) {
    if (p->left != nullptr) {
      if (p->right != nullptr) {
        s.push(p->right);
      }
      s.push(p->left);
    } else {
      s.push(p->right);
    }
  }
  s.pop();
}

template<class T>
void rb_post_order(rb_node_base *p, stl::vector<T> &v) {
  if (p == nullptr) {
    return;
  }
  stack<rb_node_base *> s;
  s.push(p);
  while (!s.empty()) {
    if (s.top() != p->parent) {
      goto_left(s);
    }
    p = s.top();
    s.pop();
    T val = static_cast<rbtree_node<T> *>(p)->value;
    v.push_back(val);
  }
}

template<class T>
void rb_level_order(rb_node_base *p, stl::vector<T> &v) {
  if (p == nullptr) {
    return;
  }
  stl::queue<rb_node_base *> q;
  q.push(p);
  while (!q.empty()) {
    p = q.front();
    q.pop();
    T val = static_cast<rbtree_node<T> *>(p)->value;
    v.push_back(val);
    if (p->left != nullptr) {
      q.push(p->left);
    }
    if (p->right != nullptr) {
      q.push(p->right);
    }
  }
}

template<class T>
void __rb_print(rb_node_base *p, int prefix) {
  char prefix_str[prefix];
  for (int i = 0; i < prefix; i++) {
    prefix_str[i] = ' ';
  }
  prefix_str[prefix] = '\0';
  if (p == nullptr) {
    return;
  }
  T value = static_cast<rbtree_node<T> *>(p)->value;
  std::cout << prefix_str << value << "\n";
  __rb_print<T>(p->left, prefix + 2);
  __rb_print<T>(p->right, prefix + 2);
}

template<class T>
void rb_print(rb_node_base *p) {
  __rb_print<T>(p, 0);
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
rbtree_node<T> *rbtree_node<T>::attach(rbtree_node<T> *p, rb_side side) {
  p->parent = this;
  if (side == RB_LEFT) {
    left = p;
  } else if (side == RB_RIGHT) {
    right = p;
  }
  return this;
}

template<class T>
void rbtree_node<T>::print() {
  std::cout << "node(" << value << ", " << this << "): parent: "
            << parent << ", left: " << left << ", right: " << right << "\n";
}

/**
 * rbtree implementation
 */


}// namespace stl

#endif//CPP_STL_TREE_H
