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

  rbtree_node<T> *insert(const T &val, rb_side side) {
    rbtree_node<T> *new_node = new rbtree_node(val, this);
    if (side == RB_LEFT) {
      left = new_node;
    } else if (side == RB_RIGHT) {
      right = new_node;
    }
    return this;
  }

  rbtree_node<T> *attach(rbtree_node<T> *p, rb_side side) {
    p->parent = this;
    if (side == RB_LEFT) {
      left = p;
    } else if (side == RB_RIGHT) {
      right = p;
    }
    return this;
  }

  /**
   * Debug
   */

  void print() {
    std::cout << "node(" << value << ", " << this << "): parent: "
              << parent << ", left: " << left << ", right: " << right << "\n";
  }
};

/**
 * rbtree node functions
 */

template<class T>
rbtree_node<T> *rb_min_child(rbtree_node<T> *p);
template<class T>
rbtree_node<T> *rb_max_child(rbtree_node<T> *p);
template<class T>
rbtree_node<T> *rb_increment(rbtree_node<T> *p);
template<class T>
rbtree_node<T> *rb_decrement(rbtree_node<T> *p);

/**
 * rbtree node traverses
 */

template<class T>
void rb_pre_order(rbtree_node<T> *p, stl::vector<T> &v);
template<class T>
void rb_in_order(rbtree_node<T> *p, stl::vector<T> &v);
template<class T>
void rb_post_order(rbtree_node<T> *p, stl::vector<T> &v);
template<class T>
void rb_level_order(rbtree_node<T> *p, stl::vector<T> &v);
template<class T>
void __rb_print(rbtree_node<T> *p, int prefix);
template<class T>
void rb_print(rbtree_node<T> *p);

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

template<class T, class Pointer, class Reference>
constexpr bool operator==(const rbtree_iterator<T, Pointer, Reference> &lhs,
                          const rbtree_iterator<T, Pointer, Reference> &rhs) {
  return lhs.node == rhs.node;
}

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

  typedef rbtree_iterator<value_type, value_type *, value_type &> iterator;
  typedef rbtree_iterator<value_type, const value_type *, const value_type &> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef rbtree_node<value_type> node_type;

  template<class Iter, class NodeType>
  struct _insert_return_type {
    Iter position;
    bool inserted;
    NodeType node;
  };
  typedef _insert_return_type<iterator, node_type> insert_return_type;

  typedef rbtree<T, Compare> this_type;

private:
  node_type *nil;

public:
  node_type *_root;
  size_type _size;
  Compare comp;

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
   * Iterators
   */

  iterator begin() noexcept {
    return iterator(static_cast<node_type *>(rb_min_child(_root)));
  }
  const_iterator begin() const noexcept {
    return const_iterator(static_cast<node_type *>(rb_min_child(_root)));
  }
  const_iterator cbegin() const noexcept {
    return constiterator(static_cast<node_type *>(rb_min_child(_root)));
  }

  iterator end() noexcept {
    return iterator(static_cast<node_type *>(rb_max_child(_root)->right));
  }
  const_iterator end() const noexcept {
    return const_iterator(static_cast<node_type *>(rb_max_child(_root)->right));
  }
  const_iterator cend() const noexcept {
    return const_iterator(static_cast<node_type *>(rb_max_child(_root)->right));
  }

  /**
   * Capacity
   */

  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }

  /**
   * Modifiers
   */

  void clear() noexcept;
  node_type *insert(const value_type &value);
  void erase(node_type *p);

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
  void post_order();
  void level_order();
  void print();
};

/**
 * Node operation
 */

template<class T>
void rb_rotate_left(rbtree_node<T> *p, rbtree<T> *t);
template<class T>
void rb_rotate_right(rbtree_node<T> *p, rbtree<T> *t);

/**
 * rbtree node functions
 */

template<class T>
rbtree_node<T> *rb_min_child(rbtree_node<T> *p) {
  while (p->left != nullptr) {
    p = p->left;
  }
  return p;
}

template<class T>
rbtree_node<T> *rb_max_child(rbtree_node<T> *p) {
  while (p->right != nullptr) {
    p = p->right;
  }
  return p;
}

template<class T>
rbtree_node<T> *rb_increment(rbtree_node<T> *p) {
  if (p->right != nullptr) {
    return rb_min_child<T>(p->right);
  }
  rbtree_node<T> *tmp = p->parent;
  while (tmp != nullptr && p == tmp->right) {
    p = tmp;
    tmp = tmp->parent;
  }
  return tmp;
}

template<class T>
rbtree_node<T> *rb_decrement(rbtree_node<T> *p) {
  if (p->left != nullptr) {
    return rb_max_child<T>(p->left);
  }
  rbtree_node<T> *tmp = p->parent;
  while (tmp != nullptr && p == tmp->left) {
    p = tmp;
    tmp = tmp->parent;
  }
  return tmp;
}

/**
 * rbtree node traverses
 */

template<class T>
void rb_pre_order(rbtree_node<T> *p, stl::vector<T> &v) {
  stack<rbtree_node<T> *> s;
  while (true) {
    while (p != nullptr) {
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
}

template<class T>
void rb_in_order(rbtree_node<T> *p, stl::vector<T> &v) {
  stack<rbtree_node<T> *> s;
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
    T val = p->value;
    v.push_back(val);
    p = p->right;
  }
}

template<class T>
static void goto_left(stack<rbtree_node<T> *> &s) {
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
void rb_post_order(rbtree_node<T> *p, stl::vector<T> &v) {
  if (p == nullptr) {
    return;
  }
  stack<rbtree_node<T> *> s;
  s.push(p);
  while (!s.empty()) {
    if (s.top() != p->parent) {
      goto_left(s);
    }
    p = s.top();
    s.pop();
    T val = p->value;
    v.push_back(val);
  }
}

template<class T>
void rb_level_order(rbtree_node<T> *p, stl::vector<T> &v) {
  if (p == nullptr) {
    return;
  }
  stl::queue<rbtree_node<T> *> q;
  q.push(p);
  while (!q.empty()) {
    p = q.front();
    q.pop();
    T val = p->value;
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
void __rb_print(rbtree_node<T> *p, int prefix) {
  char prefix_str[prefix];
  for (int i = 0; i < prefix; i++) {
    prefix_str[i] = ' ';
  }
  prefix_str[prefix] = '\0';
  if (p == nullptr) {
    return;
  }
  T value = p->value;
  std::cout << prefix_str << value << "\n";
  __rb_print<T>(p->left, prefix + 2);
  __rb_print<T>(p->right, prefix + 2);
}

template<class T>
void rb_print(rbtree_node<T> *p) {
  __rb_print<T>(p, 0);
}

/**
 * rbtree implementation
 */

/**
 * Member functions
 */

template<class T, class Compare>
rbtree<T, Compare>::rbtree() : _root(), _size(0), comp(Compare()) {
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
}

// TODO
template<class T>
static void insert_fixup(rbtree_node<T> *p, rbtree<T> *t) {
  if (p == t->_root) {
    p->color = RB_BLACK;
    return;
  }
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
        rb_rotate_left(p, t);
      }
      p->parent->color = RB_BLACK;
      p->parent->parent->color = RB_RED;
      rb_rotate_right(p->parent->parent, t);
    } else {
      y = p->parent->parent->left;
      if (y->color == RB_RED) {
        p->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        p = p->parent->parent;
      } else if (p == p->parent->left) {
        p = p->parent;
        rb_rotate_right(p, t);
      }
      p->parent->color = RB_BLACK;
      p->parent->parent->color = RB_RED;
      rb_rotate_left(p->parent->parent, t);
    }
  }
  t->_root->color = RB_BLACK;
}

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::insert(const value_type &value) {
  node_type *p = new rbtree_node<T>(value);
  node_type *y = nil;
  node_type *x = _root;
  while (x != nil) {
    y = x;
    if (comp(value, x->value)) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  p->parent = y;
  if (y == nil) {
    _root = p;
  } else if (comp(value, y->value)) {
    y->left = p;
  } else {
    y->right = p;
  }
  _size++;
  p->left = nil;
  p->right = nil;
  p->color = RB_RED;
  insert_fixup(p, this);
  return p;
}

/**
 * in rbtree @t, using subtree @v to replace subtree @u
 */
template<class T>
static void transplant(rbtree<T> *t, rbtree_node<T> *u, rbtree_node<T> *v) {
  if (u->parent == nullptr) {
    t->_root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

template<class T, class Compare>
void rbtree<T, Compare>::erase(rbtree::node_type *p) {
  if (p->left == nullptr) {
    transplant(this, p, p->right);
  } else if (p->right == nullptr) {
    transplant(this, p, p->left);
  } else {
    rbtree_node<T> *tmp = rb_min_child(p->right);
    if (tmp->parent != p) {
      transplant(this, tmp, tmp->right);
      tmp->right = p->right;
      tmp->right->parent = tmp;
    }
    transplant(this, p, tmp);
    tmp->left = p->left;
    tmp->left->parent = tmp;
  }
  _size--;
}

/**
 * Lookup
 */

template<class T, class Compare>
rbtree<T, Compare>::node_type *rbtree<T, Compare>::find(rbtree::node_type *p, const value_type &value) {
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
  stl::vector<T> v;
  rb_pre_order(_root, v);
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::in_order() {
  stl::vector<T> v;
  rb_in_order(_root, v);
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::post_order() {
  stl::vector<T> v;
  rb_post_order(_root, v);
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::level_order() {
  stl::vector<T> v;
  rb_level_order(_root, v);
  v.for_each(v.begin(), v.end(), [](const T &value) {
    std::cout << value << " ";
  });
  std::cout << "\n";
}

template<class T, class Compare>
void rbtree<T, Compare>::print() {
  rb_print<T>(_root);
}

/**
 * Node operation
 */

template<class T>
void rb_rotate_left(rbtree_node<T> *p, rbtree<T> *t) {
  rbtree_node<T> *const y = p->right;
  p->right = y->left;
  if (y->left != nullptr) {
    y->left->parent = p;
  }
  y->parent = p->parent;
  if (p == t->_root) {
    t->_root = y;
  } else if (p == p->parent->left) {
    p->parent->left = y;
  } else {
    p->parent->right = y;
  }
  y->left = p;
  p->parent = y;
}

template<class T>
void rb_rotate_right(rbtree_node<T> *p, rbtree<T> *t) {
  rbtree_node<T> *const y = p->left;
  p->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = p;
  }
  y->parent = p->parent;
  if (p == t->_root) {
    t->_root = y;
  } else if (p == p->parent->right) {
    p->parent->right = y;
  } else {
    p->parent->left = y;
  }
  y->right = p;
  p->parent = y;
}

/**
 * generate tree
 */

static stl::rbtree_node<int> *generate_full_tree() {
  stl::rbtree_node<int> *n = new stl::rbtree_node<int>(4);
  stl::rbtree_node<int> *n1 = new stl::rbtree_node<int>(2);
  n1->insert(1, stl::RB_LEFT);
  n1->insert(3, stl::RB_RIGHT);
  n->attach(n1, stl::RB_LEFT);
  stl::rbtree_node<int> *n2 = new stl::rbtree_node<int>(6);
  n2->insert(5, stl::RB_LEFT);
  n2->insert(7, stl::RB_RIGHT);
  n->attach(n2, stl::RB_RIGHT);
  /**
   * generated tree:
   *
   *       4
   *      / \
   *     2   6
   *   / \  / \
   *  1  3 5  7
   */
  return n;
}

}// namespace stl

#endif//CPP_STL_TREE_H
