//
// Created by wjl on 2023/4/24.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include "queue.h"
#include "stack.h"
#include "util.h"

#include <iostream>

namespace stl {

typedef enum {
  RB_RED,
  RB_BLACK
} rb_color_t;

template<class T>
struct tree_node {
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type *const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef tree_node<T> node;

  T data;
  node *parent;
  node *left;
  node *right;
  size_type height;
  rb_color_t color;

  tree_node()
      : parent(nullptr), left(nullptr), right(nullptr),
        height(0), color(RB_RED) {}
  tree_node(const T &value,
            node *p = nullptr, node *l = nullptr, node *r = nullptr,
            size_type h = 0, rb_color_t c = RB_RED)
      : data(value), parent(p), left(l), right(r), height(h), color(c) {}

  size_type size();

  tree_node<T> *succ();

  tree_node<T> *insert_left(const T &value);
  tree_node<T> *insert_right(const T &value);

  /**
   * Traverse
   */

  template<class Lambda>
  void pre_order(tree_node<T> *p, Lambda &&lambda);
  template<class Lambda>
  void pre_order(Lambda &&lambda);

  template<class Lambda>
  void in_order(tree_node<T> *p, Lambda &&lambda);
  template<class Lambda>
  void in_order(Lambda &&lambda);

  template<class Lambda>
  void post_order(tree_node<T> *p, Lambda &&lambda);
  template<class Lambda>
  void post_order(Lambda &&lambda);

  template<class Lambda>
  void level_order(tree_node<T> *p, Lambda &&lambda);
  template<class Lambda>
  void level_order(Lambda &&lambda);
  void level_order();
};

template<class T>
class tree {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type *const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef tree_node<T> node;

private:
  size_type _size;
  node *_root;

  void update_height(tree_node<T> *p);
  void update_height_above(tree_node<T> *p);

public:
  tree() : _size(0), _root(nullptr) {}
  ~tree();

  size_type size() const;
  bool empty() const;
  tree_node<T> *root() const;

  tree_node<T> *insert_root(const T &value);
  tree_node<T> *insert_left(tree_node<T> *p, const T &value);
  tree_node<T> *insert_right(tree_node<T> *p, const T &value);
  tree_node<T> *attach_left(tree_node<T> *p, tree<T> *&t);
  tree_node<T> *attach_right(tree_node<T> *p, tree<T> *&t);

  int remove(tree_node<T> *p);
  tree<T> *secede(tree_node<T> *p);

  /**
   * Traverse
   */

  template<class Lambda>
  void pre_order(Lambda &&lambda);

  template<class Lambda>
  void in_order(Lambda &&lambda);

  template<class Lambda>
  void post_order(Lambda &&lambda);

  template<class Lambda>
  void level_order(Lambda &&lambda);

  void level_order();
};

/**
 * node operator
 */

template<class T>
static bool is_root(tree_node<T> *p) {
  return !p->parent;
}

template<class T>
static bool is_left(tree_node<T> *p) {
  return !is_root(p) && p == p->parent->left;
}

template<class T>
static bool is_right(tree_node<T> *p) {
  return !is_root(p) && p == p->parent->right;
}

template<class T>
static bool has_parent(tree_node<T> *p) {
  return !is_root(p);
}

template<class T>
static bool has_left(tree_node<T> *p) {
  return p->left != nullptr;
}

template<class T>
static bool has_right(tree_node<T> *p) {
  return p->right != nullptr;
}

template<class T>
static bool has_child(tree_node<T> *p) {
  return has_left(p) || has_right(p);
}

template<class T>
static bool has_both_child(tree_node<T> *p) {
  return has_left(p) && has_right(p);
}

template<class T>
static bool is_leaf(tree_node<T> *p) {
  return !has_child(p);
}

template<class T>
static tree_node<T> *sibling(tree_node<T> *p) {
  return is_left(p) ? p->parent->right : p->parent->left;
}

template<class T>
static tree_node<T> *uncle(tree_node<T> *p) {
  return is_left(p->parent) ? p->parent->parent->right : p->parent->parent->left;
}

template<class T>
static void left_most(tree_node<T> *p, stack<tree_node<T> *> &s) {
  while (p) {
    s.push(p);
    p = p->left;
  }
}

template<class T>
static void highest_leaf(stack<tree_node<T> *> &s) {
  while (auto p = s.top()) {
    if (has_left(p)) {
      if (has_right(p)) {
        s.push(p->right);
      }
      s.push(p->left);
    } else {
      s.push(p->right);
    }
  }
  s.pop();
}


/**
 * tree-node implementation
 */

template<class T>
tree_node<T>::size_type tree_node<T>::size() {
  TODO();
}

template<class T>
tree_node<T> *tree_node<T>::insert_left(const T &value) {
  tree_node<T> *newp = new tree_node(value, this);
  this->left = newp;
  return newp;
}

template<class T>
tree_node<T> *tree_node<T>::insert_right(const T &value) {
  tree_node<T> *newp = new tree_node(value, this);
  this->right = newp;
  return newp;
}

template<class T>
tree_node<T> *tree_node<T>::succ() {
  TODO();
}

template<class T>
template<class Lambda>
void tree_node<T>::pre_order(tree_node<T> *p, Lambda &&lambda) {
  if (!p) {
    return;
  }
  stack<tree_node<T> *> s;
  s.push(p);
  while (!s.empty()) {
    tree_node<T> *pp = s.top();
    lambda(pp->data);
    s.pop();
    if (has_right(pp)) {
      s.push(pp->right);
    }
    if (has_left(pp)) {
      s.push(pp->left);
    }
  }
}

template<class T>
template<class Lambda>
void tree_node<T>::pre_order(Lambda &&lambda) {
  pre_order(this, lambda);
}

template<class T>
template<class Lambda>
void tree_node<T>::in_order(tree_node<T> *p, Lambda &&lambda) {
  if (!p) {
    return;
  }
  stack<tree_node<T> *> s;
  left_most(p, s);
  while (!s.empty()) {
    tree_node<T> *pp = s.top();
    lambda(pp->data);
    s.pop();
    if (has_right(pp)) {
      // pp only has right child
      left_most(pp->right, s);
    }
  }
}

template<class T>
template<class Lambda>
void tree_node<T>::in_order(Lambda &&lambda) {
  in_order(this, lambda);
}

template<class T>
template<class Lambda>
void tree_node<T>::post_order(tree_node<T> *p, Lambda &&lambda) {
  if (!p) {
    return;
  }
  stack<tree_node<T> *> s;
  s.push(p);
  while (!s.empty()) {
    if (s.top() != p->parent) {
      highest_leaf(s);
    }
    p = s.top();
    s.pop();
    lambda(p->data);
  }
}

template<class T>
template<class Lambda>
void tree_node<T>::post_order(Lambda &&lambda) {
  post_order(this, lambda);
}

template<class T>
template<class Lambda>
void tree_node<T>::level_order(tree_node<T> *p, Lambda &&lambda) {
  if (!p) {
    return;
  }
  queue<tree_node<T> *> q;
  q.push(p);
  while (!q.empty()) {
    tree_node<T> *pp = q.front();
    lambda(pp->data);
    q.pop();
    if (has_left(pp)) {
      q.push(pp->left);
    }
    if (has_right(pp)) {
      q.push(pp->right);
    }
  }
}

template<class T>
template<class Lambda>
void tree_node<T>::level_order(Lambda &&lambda) {
  level_order(this, lambda);
}

template<class T>
void tree_node<T>::level_order() {
  std::cout << "tree(level order): [ ";
  auto lambda = [](const value_type &value) {
    std::cout << value << " ";
  };
  level_order(this, lambda);
  std::cout << "]\n";
}
/**
 * tree implementation
 */

template<class T>
void tree<T>::update_height(tree_node<T> *p) {
  p->height = 1 + MAX(p->left->height, p->right->height);
}

template<class T>
void tree<T>::update_height_above(tree_node<T> *p) {
  while (p) {
    update_height(p);
    p = p->parent;
  }
}

template<class T>
tree<T>::~tree() {
  if (_size > 0) {
    delete _root;
  }
}

template<class T>
tree<T>::size_type tree<T>::size() const {
  return _size;
}

template<class T>
bool tree<T>::empty() const {
  return !_root;
}

template<class T>
tree_node<T> *tree<T>::root() const {
  return _root;
}

template<class T>
tree_node<T> *tree<T>::insert_root(const T &value) {
  tree_node<T> *newp = new tree_node(value);
  this->_root = newp;
  _size = 1;
  return this->_root;
}

template<class T>
tree_node<T> *tree<T>::insert_left(tree_node<T> *p, const T &value) {
  p->insert_left(value);
  this->_size++;
  update_height_above(p);
  return p->left;
}

template<class T>
tree_node<T> *tree<T>::insert_right(tree_node<T> *p, const T &value) {
  p->insert_right(value);
  this->_size++;
  update_height_above(p);
  return p->right;
}

template<class T>
tree_node<T> *tree<T>::attach_left(tree_node<T> *p, tree<T> *&t) {
  p->left = t->_root;
  if (p->left) {
    p->left->parent = p;
  }
  _size += t->_size;
  update_height_above(p);
  t->_root = nullptr;
  t->_size = 0;
  t = nullptr;
  return p;
}

template<class T>
tree_node<T> *tree<T>::attach_right(tree_node<T> *p, tree<T> *&t) {
  p->right = t->_root;
  if (p->right) {
    p->right->parent = p;
  }
  _size += t->_size;
  update_height_above(p);
  t->_root = nullptr;
  t->_size = 0;
  t = nullptr;
  return p;
}

template<class T>
static int remove_at(tree_node<T> *p) {
  if (p == nullptr) {
    return 0;
  }
  int n = 1 + remove_at(p->left) + remove_at(p->right);
  return n;
}

template<class T>
int tree<T>::remove(tree_node<T> *p) {
  is_root(p) ? _root : (is_left(p) ? p->parent->left : p->parent->right) = nullptr;
  update_height_above(p->parent);
  int n = remove_at(p);
  _size -= n;
  return n;
}

template<class T>
tree<T> *tree<T>::secede(tree_node<T> *p) {
  is_root(p) ? _root : (is_left(p) ? p->parent->left : p->parent->right) = nullptr;
  update_height_above(p->parent);
  tree<T> *t = new tree<T>;
  t->_root = p;
  p->parent = nullptr;
  t->_size = p->size();
  _size -= t->_size;
  return t;
}

template<class T>
template<class Lambda>
void tree<T>::pre_order(Lambda &&lambda) {
  _root->pre_order(lambda);
}

template<class T>
template<class Lambda>
void tree<T>::in_order(Lambda &&lambda) {
  _root->in_order(lambda);
}

template<class T>
template<class Lambda>
void tree<T>::post_order(Lambda &&lambda) {
  _root->post_order(lambda);
}

template<class T>
template<class Lambda>
void tree<T>::level_order(Lambda &&lambda) {
  _root->level_order(lambda);
}

template<class T>
void tree<T>::level_order() {
  _root->level_order();
}

}// namespace stl

#endif//CPP_STL_TREE_H
