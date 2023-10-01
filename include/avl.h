//
// Created by wjl on 2023/9/28.
//

#ifndef CPP_STL_AVL_H
#define CPP_STL_AVL_H

#pragma once

#include <algorithm>
#include <iostream>

#include <queue.h>
#include <stack.h>
#include <util.h>
#include <vector.h>

namespace stl {

/**
 * avl node type
 */
template<class T>
struct avl_node {
private:
  typedef avl_node<T> this_type;

public:
  this_type *left;
  this_type *right;
  size_t height;
  T data;

public:
  avl_node(const T &val)
      : left(nullptr), right(nullptr), height(1), data(val) {}
};

/**
 * avl tree
 */
template<typename T>
class avl {
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
  typedef avl_node<value_type> node_type;
  typedef avl<T> this_type;

private:
  node_type *_root;
  size_type _size;

private:
  /**
   * Node operation
   */

  size_type height(node_type *head) {
    if (head == nullptr) {
      return 0;
    }
    return head->height;
  }

  node_type *right_rotate(node_type *p) {
    node_type *t = p->left;
    p->left = t->right;
    t->right = p;
    p->height = 1 + std::max(height(p->left), height(p->right));
    t->height = 1 + std::max(height(t->left), height(t->right));
    return t;
  }

  node_type *left_rotate(node_type *p) {
    node_type *t = p->right;
    p->right = t->left;
    t->left = p;
    p->height = 1 + std::max(height(p->left), height(p->right));
    t->height = 1 + std::max(height(t->left), height(t->right));
    return t;
  }

  node_type *_insert(node_type *p, T e) {
    if (p == nullptr) {
      _size += 1;
      node_type *temp = new node_type(e);
      return temp;
    }
    if (e < p->data) {
      p->left = _insert(p->left, e);
    } else if (e > p->data) {
      p->right = _insert(p->right, e);
    }
    p->height = 1 + std::max(height(p->left), height(p->right));
    int bal = height(p->left) - height(p->right);
    if (bal > 1) {
      if (e < p->left->data) {
        return right_rotate(p);
      } else {
        p->left = left_rotate(p->left);
        return right_rotate(p);
      }
    } else if (bal < -1) {
      if (e > p->right->data) {
        return left_rotate(p);
      } else {
        p->right = right_rotate(p->right);
        return left_rotate(p);
      }
    }
    return p;
  }

  node_type *_erase(node_type *p, T e) {
    if (p == nullptr) {
      return nullptr;
    }
    if (e < p->data) {
      p->left = _erase(p->left, e);
    } else if (e > p->data) {
      p->right = _erase(p->right, e);
    } else {
      node_type *r = p->right;
      if (p->right == nullptr) {
        node_type *l = p->left;
        delete (p);
        p = l;
      } else if (p->left == nullptr) {
        delete (p);
        p = r;
      } else {
        while (r->left != nullptr) {
          r = r->left;
        }
        p->data = r->data;
        p->right = _erase(p->right, r->data);
      }
    }
    if (p == NULL) {
      return p;
    }
    p->height = 1 + std::max(height(p->left), height(p->right));
    int bal = height(p->left) - height(p->right);
    if (bal > 1) {
      if (height(p->left) >= height(p->right)) {
        return right_rotate(p);
      } else {
        p->left = left_rotate(p->left);
        return right_rotate(p);
      }
    } else if (bal < -1) {
      if (height(p->right) >= height(p->left)) {
        return left_rotate(p);
      } else {
        p->right = right_rotate(p->right);
        return left_rotate(p);
      }
    }
    return p;
  }

  node_type *_search(node_type *p, T e) {
    if (p == nullptr) {
      return nullptr;
    }
    T val = p->data;
    if (val == e) {
      return p;
    }
    if (val > e) {
      return _search(p->left, e);
    }
    if (val < e) {
      return _search(p->right, e);
    }
  }

public:
  /**
   * Member functions
   */

  avl() : _root(nullptr), _size(0) {}

  ~avl() {
    clear();
  }

  /**
   * Capacity
   */

  bool empty() const { return _size == 0; }
  size_t size() const { return _size; }

  /**
   * Modifiers
   */

  void clear() noexcept {
    // TODO
  }

  void insert(T e) {
    _root = _insert(_root, e);
  }

  void erase(T e) {
    _root = _erase(_root, e);
  }

  /**
   * Look up
   */

  node_type *find(T e) {
    return _search(_root, e);
  }

  void print(node_type *p, int prefix) {
    char prefix_str[prefix + 1];
    for (int i = 0; i < prefix; i++) {
      prefix_str[i] = ' ';
    }
    prefix_str[prefix] = '\0';
    if (p == nullptr) {
      return;
    }
    std::cout << prefix_str;
    std::cout << "--";
    std::cout << p->data << "\n";
    print(p->left, prefix + 2);
    print(p->right, prefix + 2);
  }

  void print() { print(_root, 0); }
};

}// namespace stl

#endif//CPP_STL_AVL_H
