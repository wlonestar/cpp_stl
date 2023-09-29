//
// Created by wjl on 2023/5/8.
//

#ifndef CPP_STL_RBTREE_H
#define CPP_STL_RBTREE_H

#pragma once

#include <initializer_list>
#include <iostream>
#include <string>
#include <tuple>

#include <nlohmann/json.hpp>

#include <queue.h>
#include <stack.h>
#include <util.h>
#include <vector.h>

namespace stl {

/**
 * rbtree status type
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
  T data;

public:
  rbtree_node()
      : parent(nullptr), left(nullptr), right(nullptr), color(RB_RED) {}

  rbtree_node(const T &val, rbtree_node<T> *parent = nullptr,
              rbtree_node<T> *left = nullptr, rbtree_node<T> *right = nullptr,
              rb_color color = RB_RED)
      : data(val), parent(parent), left(left), right(right), color(color) {}

  friend void to_json(nlohmann::json &j, const rbtree_node<T> &n) {
    j["value"] = n.data;
    j["key"] = n.data;
    j["color"] = n.color == RB_BLACK ? "black" : "red";
    if (n.parent != nullptr) {
      j["parent"] = n.parent->data;
    } else {
      j["parent"] = "null";
    }
    if (n.left != nullptr) {
      j["left"] = n.left->data;
    } else {
      j["left"] = "null";
    }
    if (n.right != nullptr) {
      j["right"] = n.right->data;
    } else {
      j["right"] = "null";
    }
  }
};

template<class U>
struct link {
  U from;
  U to;

  link() = default;
  link(U f, U t) : from(f), to(t) {}

  friend void to_json(nlohmann::json &j, const link &t) {
    j["from"] = t.from;
    j["to"] = t.to;
  }
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
  node_type *_root;
  size_type _size;
  Compare comp;

private:
  /**
   * Node operation
   */

  rbtree_node<T> *min_child(rbtree_node<T> *p) {
    while (p->left != nil) {
      p = p->left;
    }
    return p;
  }

  rbtree_node<T> *max_child(rbtree_node<T> *p) {
    while (p->right != nil) {
      p = p->right;
    }
    return p;
  }

  void rotate_left(rbtree_node<T> *p) {
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

  void rotate_right(rbtree_node<T> *p) {
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

public:
  /**
   * Member functions
   */

  rbtree() : _root(), _size(0), comp(Compare()) {
    nil = new rbtree_node<T>();
    nil->parent = nullptr;
    nil->left = nullptr;
    nil->right = nullptr;
    nil->color = RB_BLACK;
    _root = nil;
  }

  rbtree(const Compare &compare)
      : _root(), _size(0), comp(compare) {}

  rbtree(const this_type &x)
      : _root(x._root), _size(0), comp(x.comp) {}

  rbtree(this_type &&x)
      : _root(), _size(0), comp() {
    swap(x);
  }

  ~rbtree() {
    clear();
    delete nil;
  }

  /**
   * Capacity
   */

  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }

  /**
   * Modifiers
   */

  void clear() noexcept {
    while (_size > 0) {
      erase(_root);
    }
  }

  void insert_fixup(rbtree_node<T> *p) {
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

  node_type *insert(rbtree_node<T> *p) {
    node_type *y = nil;
    node_type *x = _root;
    while (x != nil) {
      y = x;
      if (comp(p->data, x->data)) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    p->parent = y;
    if (y == nil) {
      _root = p;
    } else if (comp(p->data, y->data)) {
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

  node_type *insert(const value_type &value) {
    node_type *p = new rbtree_node<T>(value);
    return insert(p);
  }

  /**
   * in rbtree @t, using subtree @v to replace subtree @u
   */
  void transplant(rbtree_node<T> *u, rbtree_node<T> *v) {
    if (u->parent == nil) {
      _root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void erase_fixup(rbtree_node<T> *x) {
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

  void erase(node_type *p) {
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

  void erase(const value_type &value) {
    rbtree_node<T> *p = find(value);
    if (p == nullptr) {
      return;
    }
    erase(p);
  }

  /**
   * Lookup
   */

  node_type *find(node_type *p, const value_type &value) {
    while (p != nullptr && value != p->data) {
      if (comp(value, p->data)) {
        p = p->left;
      } else {
        p = p->right;
      }
    }
    return p;
  }

  node_type *find(const value_type &value) {
    return find(_root, value);
  }

  /**
   * Traverse
   */

  void pre_order(stl::vector<T> &v) {
    rbtree_node<T> *p = _root;
    stack<rbtree_node<T> *> s;
    while (true) {
      while (p != nil && p != nullptr) {
        T val = p->data;
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

  void in_order(stl::vector<T> &v) {
    rbtree_node<T> *p = _root;
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
      T val = p->data;
      v.push_back(val);
      p = p->right;
    }
  }

  void _post_order(rbtree_node<T> *p, stl::vector<T> &v) {
    if (p == nil || p == nullptr) {
      return;
    }
    _post_order(p->left, v);
    _post_order(p->right, v);
    v.push_back(p->data);
  }

  void post_order(stl::vector<T> &v) {
    _post_order(_root, v);
  }

  void level_order(stl::vector<T> &v) {
    rbtree_node<T> *p = _root;
    if (p == nullptr || p == nil) {
      return;
    }
    stl::queue<rbtree_node<T> *> q;
    q.push(p);
    while (!q.empty()) {
      p = q.front();
      q.pop();
      T val = p->data;
      v.push_back(val);
      if (p->left != nil) {
        q.push(p->left);
      }
      if (p->right != nil) {
        q.push(p->right);
      }
    }
  }

  void print(rbtree_node<T> *p, int prefix) {
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
      std::cout << "\033[31m" << p->data << "\033[0m\n";
    } else {
      std::cout << "\033[0m" << p->data << "\033[0m\n";
    }
    print(p->left, prefix + 2);
    print(p->right, prefix + 2);
  }

  void print() {
    print(_root, 0);
  }

  friend void to_json(nlohmann::json &j, const rbtree<T> &t) {
    // same as in order traverse, but need to get all nodes
    stl::vector<rbtree_node<T>> nodes;
    rbtree_node<T> *p = t._root;
    stl::stack<rbtree_node<T> *> s;
    while (true) {
      while (p != t.nil && p != nullptr) {
        s.push(p);
        p = p->left;
      }
      if (s.empty()) {
        break;
      }
      p = s.top();
      s.pop();
      nodes.push_back(*p);
      p = p->right;
    }

    // loop all nodes, find all links between nodes
    // if it has parent, add a link from parent to itself,
    // if it has child, add a link from itself to its child
    stl::vector<link<T>> links;
    for (rbtree_node<T> &node: nodes) {
      if (node.parent != nullptr) {
        link<T> *l = new link(node.parent->data, node.data);
        links.push_back(*l);
      }
      if (node.left != nullptr) {
        link<T> *l = new link(node.data, node.left->data);
        links.push_back(*l);
      }
      if (node.parent != nullptr) {
        link<T> *l = new link(node.data, node.right->data);
        links.push_back(*l);
      }
    }
    j["n"] = t._size;
    j["nodes"] = nodes;
    j["links"] = links;
  }
};

}// namespace stl

#endif//CPP_STL_RBTREE_H
