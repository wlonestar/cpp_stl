//
// Created by wjl on 2023/4/24.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include "util.h"

#include <iostream>

namespace stl {

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

  void preorder(tree_node<T> *p) {
    if (!p) {
      return ;
    }
    std::cout << p->data << " ";
    preorder(p->left);
    preorder(p->right);
  }

  void preorder() {
    std::cout << "tree(pre order): [ ";
    preorder(this);
    std::cout << "]\n";
  }

  void inorder(tree_node<T> *p) {
    if (!p) {
      return ;
    }
    inorder(p->left);
    std::cout << p->data << " ";
    inorder(p->right);
  }

  void inorder() {
    std::cout << "tree(in order): [ ";
    inorder(this);
    std::cout << "]\n";
  }

  void postorder(tree_node<T> *p) {
    if (!p) {
      return ;
    }
    postorder(p->left);
    postorder(p->right);
    std::cout << p->data << " ";
  }

  void postorder() {
    std::cout << "tree(post order): [ ";
    postorder(this);
    std::cout << "]\n";
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
    p->height= 1 + MAX(p->left->height, p->right->height);
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

  void preorder() {
    if (_root) {
      _root->preorder();
    }
  }

  void inorder() {
    if (_root) {
      _root->inorder();
    }
  }

  void postorder() {
    if (_root) {
      _root->postorder();
    }
  }

};


}// namespace stl

#endif//CPP_STL_TREE_H
