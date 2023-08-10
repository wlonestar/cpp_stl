//
// Created by wjl on 2023/5/21.
//

#ifndef CPP_STL_BTREE_H
#define CPP_STL_BTREE_H

#pragma once

#include <vector.h>

namespace stl {

template<class T>
struct btree_node {
  vector<T> keys;
  vector<btree_node<T> *> children;
  bool leaf;

  btree_node(bool l = false) : leaf(l) {}
};

template<class T>
class btree {
public:
  typedef std::size_t size_type;
  typedef T value_type;
  typedef btree_node<T> node_type;

private:
  node_type *_root;
  size_type _t;

public:
  btree(size_type t = 3) : _t(t) {
    _root = new btree_node<T>(true);
  }

  std::pair<node_type *, size_type> search(const value_type &value, node_type *node) {
    size_type i = 0;
    while (i < node->keys.size() && value > node->keys[i]) {
      i += 1;
    }
    if (i < node->keys.size() && value == node->keys[i]) {
      return std::make_pair(node, i);
    } else if (node->leaf) {
      return std::make_pair(nullptr, -1);
    } else {
      return search(value, node->children[i]);
    }
  }

  std::tuple<node_type *, size_type> search(const value_type &value) {
    return search(value, _root);
  }

  void split_child(node_type *x, size_type i) {
    size_type t = _t;
    // y is a full child of x
    node_type *y = x->children[i];
    // create a new node and add it
    node_type *z = new btree_node<T>(y->leaf);
    x->children.insert(x->children.begin() + i + 1, z);
    // insert the median of the full child y into x
    x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
    // split apart y's keys into y & z
    vector<T> y1 = y->keys;
    y1.erase(y1.begin(), y1.begin() + t);
    z->keys = y1;

    vector<T> y2 = y->keys;
    y2.erase(y2.begin() + t - 1, y2.end());
    y->keys = y2;
    // if y is not a leaf, we reassign y's children to y & z
    if (!y->leaf) {
      vector<btree_node<T> *> y11 = y->children;
      y11.erase(y11.begin(), y11.begin() + t);
      z->children = y11;

      vector<btree_node<T> *> y22 = y->children;
      y22.erase(y22.begin() + t - 1, y22.end());
      y->children = y22;
    }
  }

  void insert_non_full(node_type *x, const value_type &value) {
    size_type t = _t;
    size_type i = x->keys.size() - 1;
    // find the correct spot in the leaf to insert the key
    if (x->leaf) {
      x->keys.push_back(INT_MIN);
      while (i >= 0 && value < x->keys[i]) {
        x->keys[i + 1] = x->keys[i];
        i -= 1;
      }
      x->keys[i + 1] = value;
    } else {
      // if not a leaf, find the correct subtree to insert the key
      while (i >= 0 && value < x->keys[i]) {
        i -= 1;
      }
      i += 1;
      // if child node is full, split it
      if (x->children[i]->keys.size() == 2 * t - 1) {
        split_child(x, i);
        if (value > x->keys[i]) {
          i += 1;
        }
      }
      insert_non_full(x->children[i], value);
    }
  }

  void insert(const value_type &value) {
    size_type t = _t;
    node_type *root = _root;
    // if root is full, create a new node - tree's height grows by 1
    if (root->keys.size() == 2 * t - 1) {
      node_type *new_root = new btree_node<T>();
      _root = new_root;
      new_root->children.insert(new_root->children.begin(), root);
      split_child(new_root, 0);
      insert_non_full(new_root, value);
    } else {
      insert_non_full(root, value);
    }
  }

  void erase_sibling(node_type *x, size_type i, size_type j) {
    node_type *cnode = x->children[i];
    if (i < j) {
      node_type *rsnode = x->children[j];
      cnode->keys.push_back(x->keys[i]);
      x->keys[i] = rsnode->keys[0];
      if (rsnode->children.size() > 0) {
        cnode->children.push_back(rsnode->children[0]);
        rsnode->children.erase(rsnode->children.begin());
      }
      rsnode->keys.erase(rsnode->keys.begin());
    } else {
      node_type *lsnode = x->children[j];
      cnode->keys.insert(cnode->keys.begin(), x->keys[i - 1]);
      x->keys[i - 1] = lsnode->keys.back();
      lsnode->keys.pop_back();
      if (lsnode->children.size() > 0) {
        cnode->children.insert(cnode->children.begin(), lsnode->children.back());
        lsnode->children.pop_back();
      }
    }
  }

  void erase_merge(node_type *x, size_type i, size_type j) {
    node_type *cnode = x->children[i];
    node_type *new_node;
    if (j > i) {
      node_type *rsnode = x->children[j];
      cnode->keys.push_back(x->keys[i]);
      for (int k = 0; k < rsnode->keys.size(); k++) {
        cnode->keys.push_back(rsnode->keys[k]);
        if (rsnode->children.size() > 0) {
          cnode->children.push_back(rsnode->children[k]);
        }
      }
      if (rsnode->children.size() > 0) {
        cnode->children.push_back(rsnode->children.back());
        rsnode->children.pop_back();
      }
      new_node = cnode;
      x->keys.erase(x->keys.begin() + i);
      x->children.erase(x->children.begin() + j);
    } else {
      node_type *lsnode = x->children[j];
      lsnode->keys.push_back(x->keys[j]);
      for (int k = 0; k < cnode->keys.size(); k++) {
        lsnode->keys.push_back(cnode->keys[k]);
        if (lsnode->children.size() > 0) {
          lsnode->children.push_back(cnode->children[k]);
        }
      }
      if (lsnode->children.size() > 0) {
        lsnode->children.push_back(cnode->children.back());
        cnode->children.pop_back();
      }
      new_node = lsnode;
      x->keys.erase(x->keys.begin() + j);
      x->children.erase(x->children.begin() + i);
    }
    if (x == _root && x->keys.size() == 0) {
      _root = new_node;
    }
  }

  value_type &erase_predecessor(node_type *x) {
    if (x->leaf) {
      value_type val = x->keys.back();
      x->keys.pop_back();
      return val;
    }
    size_type n = x->keys.size() - 1;
    if (x->children[n]->keys.size() >= _t) {
      erase_sibling(x, n + 1, n);
    } else {
      erase_merge(x, n, n + 1);
    }
    erase_predecessor(x->children[n]);
  }

  value_type &erase_successor(node_type *x) {
    if (x->leaf) {
      auto val = x->keys.front();
      x->keys.erase(x->keys.begin());
      return val;
    }
    if (x->children[1]->keys.size() >= _t) {
      erase_sibling(x, 0, 1);
    } else {
      erase_successor(x->children[0]);
    }
    erase_successor(x->children[0]);
  }

  void erase_internal_node(node_type *x, const value_type &k, size_type i) {
    size_type t = _t;
    if (x->leaf) {
      if (x->keys[i] == k) {
        x->keys.erase(x->keys.begin() + i);
      }
      return;
    }
    if (x->children[i]->keys.size() >= t) {
      x->keys[i] = erase_predecessor(x->children[i]);
      return;
    } else if (x->children[i + 1]->keys.size() >= t) {
      x->keys[i] = erase_successor(x->children[i + 1]);
      return;
    } else {
      erase_merge(x, i, i + 1);
      erase_internal_node(x->children[i], k, _t - 1);
    }
  }

  void erase(node_type *x, const value_type &k) {
    size_type t = _t;
    size_type i = 0;
    while (i < x->keys.size() && k > x->keys[i]) {
      i += 1;
    }
    if (x->leaf) {
      if (i < x->keys.size() && x->keys[i] == k) {
        x->keys.erase(x->keys.begin() + i);
      }
      return;
    }
    if (i < x->keys.size() && x->keys[i] == k) {
      return erase_internal_node(x, k, i);
    } else if (x->children[i]->keys.size() >= t) {
      erase(x->children[i], k);
    } else {
      if (i != 0 && i + 2 < x->children.size()) {
        if (x->children[i - 1]->keys.size() >= t) {
          erase_sibling(x, i, i - 1);
        } else if (x->children[i + 1]->keys.size() >= t) {
          erase_sibling(x, i, i + 1);
        } else {
          erase_merge(x, i, i + 1);
        }
      } else if (i == 0) {
        if (x->children[i + 1]->keys.size() >= t) {
          erase_sibling(x, i, i + 1);
        } else {
          erase_merge(x, i, i + 1);
        }
      } else if (i + 1 == x->children.size()) {
        if (x->children[i - 1]->keys.size() >= t) {
          erase_sibling(x, i, i - 1);
        } else {
          erase_merge(x, i, i - 1);
        }
      }
      erase(x->children[i], k);
    }
  }

  void erase(const value_type &k) {
    erase(_root, k);
  }

  void print(node_type *x, size_type level = 0) {
    std::cout << "level " << level << ": ";
    for (const auto &item: x->keys) {
      std::cout << item << " ";
    }
    std::cout << "\n";
    level += 1;
    if (x->children.size() > 0) {
      for (const auto &item: x->children) {
        print(item, level);
      }
    }
  }

  void print() {
    print(_root);
  }
};

}// namespace stl

#endif//CPP_STL_BTREE_H
