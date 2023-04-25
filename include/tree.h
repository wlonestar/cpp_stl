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

template<class T>
struct tree_node;

template<class T>
class tree;

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
    if (p->has_left()) {
      if (p->has_right()) {
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
struct tree_node {
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type &reference;
  typedef const value_type *const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  T data;
  tree_node<T> *parent;
  tree_node<T> *left;
  tree_node<T> *right;
  size_type height;

  tree_node() : parent(nullptr), left(nullptr), right(nullptr), height(0) {}
  tree_node(const T &value, tree_node<T> *p = nullptr,
            tree_node<T> *l = nullptr, tree_node<T> *r = nullptr, size_type h = 0)
      : data(value), parent(p), left(l), right(r), height(h) {}

  bool has_left() {
    return this->left != nullptr;
  }

  bool has_right() {
    return this->right != nullptr;
  }

  tree_node<T> *insert_left(const T &value) {
    tree_node<T> *newp = new tree_node(value, this);
    this->left = newp;
    return newp;
  }

  tree_node<T> *insert_right(const T &value) {
    tree_node<T> *newp = new tree_node(value, this);
    this->right = newp;
    return newp;
  }

  void pre_order(tree_node<T> *p) {
    if (!p) {
      return;
    }
    stack<tree_node<T> *> s;
    s.push(p);
    while (!s.empty()) {
      tree_node<T> *pp = s.top();
      std::cout << pp->data << " ";
      s.pop();
      if (pp->has_right()) {
        s.push(pp->right);
      }
      if (pp->has_left()) {
        s.push(pp->left);
      }
    }
  }

  template<class Lambda>
  void pre_order(tree_node<T> *p, Lambda &&lambda) {
    if (!p) {
      return;
    }
    stack<tree_node<T> *> s;
    s.push(p);
    while (!s.empty()) {
      tree_node<T> *pp = s.top();
      lambda(pp->data);
      s.pop();
      if (pp->has_right()) {
        s.push(pp->right);
      }
      if (pp->has_left()) {
        s.push(pp->left);
      }
    }
  }

  void pre_order() {
    std::cout << "tree(pre order): [ ";
    pre_order(this);
    std::cout << "]\n";
  }

  template<class Lambda>
  void pre_order(Lambda &&lambda) {
    pre_order(this, lambda);
  }

  void in_order(tree_node<T> *p) {
    if (!p) {
      return;
    }
    stack<tree_node<T> *> s;
    left_most(p, s);
    while (!s.empty()) {
      tree_node<T> *pp = s.top();
      std::cout << pp->data << " ";
      s.pop();
      if (pp->has_right()) {
        // pp only has right child
        left_most(pp->right, s);
      }
    }
  }

  template<class Lambda>
  void in_order(tree_node<T> *p, Lambda &&lambda) {
    if (!p) {
      return;
    }
    stack<tree_node<T> *> s;
    left_most(p, s);
    while (!s.empty()) {
      tree_node<T> *pp = s.top();
      lambda(pp->data);
      s.pop();
      if (pp->has_right()) {
        // pp only has right child
        left_most(pp->right, s);
      }
    }
  }

  void in_order() {
    std::cout << "tree(in order): [ ";
    in_order(this);
    std::cout << "]\n";
  }

  template<class Lambda>
  void in_order(Lambda &&lambda) {
    in_order(this, lambda);
  }

  void post_order(tree_node<T> *p) {
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
      std::cout << p->data << " ";
    }
  }

  template<class Lambda>
  void post_order(tree_node<T> *p, Lambda &&lambda) {
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

  void post_order() {
    std::cout << "tree(post order): [ ";
    post_order(this);
    std::cout << "]\n";
  }

  template<class Lambda>
  void post_order(Lambda &&lambda) {
    post_order(this, lambda);
  }
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

  void update_height(tree_node<T> *p) {
    p->height = 1 + MAX(p->left->height, p->right->height);
  }

  void update_height_above(tree_node<T> *p) {
    while (p) {
      update_height(p);
      p = p->parent;
    }
  }

public:
  tree() : _size(0), _root(nullptr) {}

  ~tree() {
    if (_size > 0) {
      delete _root;
    }
  }

  size_type size() const {
    return _size;
  }

  bool empty() const {
    return !_root;
  }

  tree_node<T> *root() const {
    return _root;
  }

  tree_node<T> *insert_root(const T &value) {
    tree_node<T> *newp = new tree_node(value);
    this->_root = newp;
    _size = 1;
    return this->_root;
  }

  tree_node<T> *insert_left(tree_node<T> *p, const T &value) {
    p->insert_left(value);
    this->_size++;
    update_height_above(p);
    return p->left;
  }

  tree_node<T> *insert_right(tree_node<T> *p, const T &value) {
    p->insert_right(value);
    this->_size++;
    update_height_above(p);
    return p->left;
  }

  void pre_order() {
    _root->pre_order();
  }

  template<class Lambda>
  void pre_order(Lambda &&lambda) {
    _root->pre_order(lambda);
  }

  void in_order() {
    _root->in_order();
  }

  template<class Lambda>
  void in_order(Lambda &&lambda) {
    _root->in_order(lambda);
  }

  void post_order() {
    _root->post_order();
  }

  template<class Lambda>
  void post_order(Lambda &&lambda) {
    _root->post_order(lambda);
  }
};

}// namespace stl

#endif//CPP_STL_TREE_H
