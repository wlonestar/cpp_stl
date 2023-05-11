//
// Created by wjl on 2023/5/8.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include <cstring>
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
 * rbtree node type
 */
template<class T>
struct rbtree_node {
private:
  typedef rbtree_node<T> this_type;

public:
  this_type *parent;
  this_type *left;
  this_type *right;
  char color;
  T value;

public:
  rbtree_node()
      : parent(nullptr), left(nullptr), right(nullptr), color(RB_RED) {}

  rbtree_node(const T &val, rbtree_node<T> *parent = nullptr,
              rbtree_node<T> *left = nullptr, rbtree_node<T> *right = nullptr,
              rb_color color = RB_RED)
      : value(val), parent(parent), left(left), right(right), color(color) {}
};

/**
 * rbtree
 */
template<class T, class Compare = std::less<T>>
class rbtree {
public:
  /**
   * Member types
   */

  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef rbtree_node<value_type> node_type;
  typedef rbtree<T, Compare> this_type;

private:
  node_type *nil;

public:
  node_type *_root;
  size_type _size;
  Compare comp;

public:
  /**
   * Node operation
   */

  rbtree_node<T> *min_child(rbtree_node<T> *p);
  rbtree_node<T> *max_child(rbtree_node<T> *p);
  void rotate_left(rbtree_node<T> *p);
  void rotate_right(rbtree_node<T> *p);

public:
  /**
   * Member functions
   */

  rbtree();
  rbtree(const Compare &compare);
  rbtree(const this_type &x);
  rbtree(this_type &&x);
  ~rbtree();

  /**
   * Element access
   */

  node_type *root() { return _root; }
  const node_type *root() const { return _root; }

  /**
   * Capacity
   */

  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }

  /**
   * Modifiers
   */

  void clear() noexcept;

  void insert_fixup(rbtree_node<T> *p);
  node_type *insert(rbtree_node<T> *p);
  node_type *insert(const value_type &value);

  void transplant(rbtree_node<T> *u, rbtree_node<T> *v);
  void erase_fixup(rbtree_node<T> *x);
  void erase(node_type *p);
  void erase(const value_type &value);

  /**
   * Lookup
   */

  node_type *find(node_type *p, const value_type &value);
  node_type *find(const value_type &value);

  /**
   * Traverse
   */

  void pre_order();
  void in_order();
  void _post_order(rbtree_node<T> *p, stl::vector<T> &v);
  void post_order();
  void level_order();
  void print(rbtree_node<T> *p, int prefix);
  void print();
};

/**
 * Node operation
 */

template<class T, class Compare>
rbtree_node<T> *rbtree<T, Compare>::min_child(rbtree_node<T> *p) {
  while (p->left != nil) {
    p = p->left;
  }
  return p;
}

template<class T, class Compare>
rbtree_node<T> *rbtree<T, Compare>::max_child(rbtree_node<T> *p) {
  while (p->right != nil) {
    p = p->right;
  }
  return p;
}

template<class T, class Compare>
void rbtree<T, Compare>::rotate_left(rbtree_node<T> *p) {
  rbtree_node<T> *y = p->right;
  p->right = y->left;
  if (y->left != nil) {
    y->left->parent = p;
  }
  y->parent = p->parent;
  if (p->parent == nil) {
    _root = y;
  } else if (p == p->parent->left) {
    p->parent->left = y;
  } else {
    p->parent->right = y;
  }
  y->left = p;
  p->parent = y;
}

template<class T, class Compare>
void rbtree<T, Compare>::rotate_right(rbtree_node<T> *p) {
  rbtree_node<T> *y = p->left;
  p->left = y->right;
  if (y->right != nil) {
    y->right->parent = p;
  }
  y->parent = p->parent;
  if (p->parent == nil) {
    _root = y;
  } else if (p == p->parent->right) {
    p->parent->right = y;
  } else {
    p->parent->left = y;
  }
  y->right = p;
  p->parent = y;
}

/**
 * Member functions
 */

template<class T, class Compare>
rbtree<T, Compare>::rbtree() : _root(), _size(0), comp(Compare()) {
  nil = new rbtree_node<T>();
  nil->parent = nullptr;
  nil->left = nullptr;
  nil->right = nullptr;
  nil->color = RB_BLACK;
  _root = nil;
}

template<class T, class Compare>
rbtree<T, Compare>::rbtree(const Compare &compare)
    : _root(), _size(0), comp(compare) {}

template<class T, class Compare>
rbtree<T, Compare>::rbtree(const rbtree::this_type &x)
    : _root(x._root), _size(0), comp(x.comp) {}

template<class T, class Compare>
rbtree<T, Compare>::rbtree(rbtree::this_type &&x) : _root(), _size(0), comp() {
  swap(x);
}

template<class T, class Compare>
rbtree<T, Compare>::~rbtree() {
}

/**
 * Modifiers
 */

template<class T, class Compare>
void rbtree<T, Compare>::clear() noexcept {
  while (_size > 0) {
    erase(_root);
  }
}

template<class T, class Compare>
void rbtree<T, Compare>::insert_fixup(rbtree_node<T> *p) {
  while (p->parent->color == RB_RED) {
    rbtree_node<T> *y;
    if (p->parent == p->parent->parent->left) {
      y = p->parent->parent->right;
      if (y->color == RB_RED) {
        p->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        p = p->parent->parent;
      } else if (p == p->parent->right) {
        p = p->parent;
        rotate_left(p);
      } else {
        p->parent->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        rotate_right(p->parent->parent);
      }
    } else if (p->parent == p->parent->parent->right) {
      y = p->parent->parent->left;
      if (y->color == RB_RED) {
        p->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        p = p->parent->parent;
      } else if (p == p->parent->left) {
        p = p->parent;
        rotate_right(p);
      } else {
        p->parent->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        rotate_left(p->parent->parent);
      }
    }
  }
  _root->color = RB_BLACK;
}

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::insert(rbtree_node<T> *p) {
  node_type *y = nil;
  node_type *x = _root;
  while (x != nil) {
    y = x;
    if (comp(p->value, x->value)) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  p->parent = y;
  if (y == nil) {
    _root = p;
  } else if (comp(p->value, y->value)) {
    y->left = p;
  } else {
    y->right = p;
  }
  _size++;
  p->left = nil;
  p->right = nil;
  p->color = RB_RED;
  insert_fixup(p);
  return p;
}

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::insert(const value_type &value) {
  node_type *p = new rbtree_node<T>(value);
  return insert(p);
}

/**
 * in rbtree @t, using subtree @v to replace subtree @u
 */
template<class T, class Compare>
void rbtree<T, Compare>::transplant(rbtree_node<T> *u, rbtree_node<T> *v) {
  if (u->parent == nil) {
    _root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template<class T, class Compare>
void rbtree<T, Compare>::erase_fixup(rbtree_node<T> *x) {
//  rbtree_node<T> *w;
  while (x != _root && x->color == RB_BLACK) {
    if (x == x->parent->left) {
      rbtree_node<T> *w = x->parent->right;
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        rotate_left(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else if (w->right->color == RB_BLACK) {
        w->left->color = RB_BLACK;
        w->color = RB_RED;
        rotate_right(w);
        w = x->parent->right;
      } else {
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->right->color = RB_BLACK;
        rotate_left(x->parent);
        x = _root;
      }
    } else {
      rbtree_node<T> *w = x->parent->left;
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        rotate_right(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else if (w->left->color == RB_BLACK) {
        w->right->color = RB_BLACK;
        w->color = RB_RED;
        rotate_left(w);
        w = x->parent->left;
      } else {
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->left->color = RB_BLACK;
        rotate_right(x->parent);
        x = _root;
      }
    }
  }
  x->color = RB_BLACK;
}

template<class T, class Compare>
void rbtree<T, Compare>::erase(rbtree::node_type *p) {
  rbtree_node<T> *y = p;
  rbtree_node<T> *x;
  char y_color = y->color;
  if (p->left == nil) {
    x = p->right;
    transplant(p, p->right);
  } else if (p->right == nil) {
    x = p->left;
    transplant(p, p->left);
  } else {
    y = min_child(p->right);
    y_color = y->color;
    x = y->right;
    if (y->parent == p) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    transplant(p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  _size--;
  if (y_color == RB_BLACK) {
    erase_fixup(x);
  }
}

template<class T, class Compare>
void rbtree<T, Compare>::erase(const value_type &value) {
  rbtree_node<T> *p = find(value);
  if (p == nullptr) {
    return ;
  }
  erase(p);
}

/**
 * Lookup
 */

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::find(rbtree::node_type *p,
                                                        const value_type &value) {
  while (p != nullptr && value != p->value) {
    if (comp(value, p->value)) {
      p = p->left;
    } else {
      p = p->right;
    }
  }
  return p;
}

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::find(const value_type &value) {
  return find(_root, value);
}

/**
 * Traverse
 */

template<class T, class Compare>
void rbtree<T, Compare>::pre_order() {
  rbtree_node<T> *p = _root;
  stl::vector<T> v;
  stack<rbtree_node<T> *> s;
  while (true) {
    while (p != nil && p != nullptr) {
      T val = p->value;
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
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::in_order() {
  rbtree_node<T> *p = _root;
  stl::vector<T> v;
  stack<rbtree_node<T> *> s;
  while (true) {
    while (p != nil && p != nullptr) {
      s.push(p);
      p = p->left;
    }
    if (s.empty()) {
      break;
    }
    p = s.top();
    s.pop();
    T val = p->value;
    v.push_back(val);
    p = p->right;
  }
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::_post_order(rbtree_node<T> *p, stl::vector<T> &v) {
  if (p == nil || p == nullptr) {
    return;
  }
  _post_order(p->left, v);
  _post_order(p->right, v);
  v.push_back(p->value);
}

template<class T, class Compare>
void rbtree<T, Compare>::post_order() {
  stl::vector<T> v;
  _post_order(_root, v);
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::level_order() {
  rbtree_node<T> *p = _root;
  stl::vector<T> v;
  if (p == nullptr || p == nil) {
    return;
  }
  stl::queue<rbtree_node<T> *> q;
  q.push(p);
  while (!q.empty()) {
    p = q.front();
    q.pop();
    T val = p->value;
    v.push_back(val);
    if (p->left != nil) {
      q.push(p->left);
    }
    if (p->right != nil) {
      q.push(p->right);
    }
  }
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::print(rbtree_node<T> *p, int prefix) {
  char prefix_str[prefix];
  for (int i = 0; i < prefix; i++) {
    prefix_str[i] = ' ';
  }
  prefix_str[prefix] = '\0';
  if (p == nil) {
    return;
  }
  std::cout << prefix_str;
  if (p == _root) {
    std::cout << "--";
  } else if (p == p->parent->left) {
    std::cout << "->";
  } else if (p == p->parent->right) {
    std::cout << "=>";
  }
  if (p->color == RB_RED) {
    std::cout << "\033[31m" << p->value << "\033[0m\n";
  } else {
    std::cout << "\033[0m" << p->value << "\033[0m\n";
  }
  print(p->left, prefix + 2);
  print(p->right, prefix + 2);
}

template<class T, class Compare>
void rbtree<T, Compare>::print() {
  print(_root, 0);
}

}// namespace stl

#endif//CPP_STL_TREE_H
