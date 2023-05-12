//
// Created by wjl on 2023/5/12.
//

#ifndef CPP_STL_AVL_H
#define CPP_STL_AVL_H

#pragma once

#include <initializer_list>
#include <iostream>

namespace stl {

template<class T>
struct avl_node {
public:
  typedef avl_node<T> this_type;
  typedef std::size_t size_type;

public:
  this_type *parent;
  this_type *left;
  this_type *right;
  size_type height;
  T value;

public:
  avl_node() : parent(nullptr), left(nullptr), right(nullptr), height(0) {}

  avl_node(const T &val, avl_node<T> *parent = nullptr,
           avl_node<T> *left = nullptr, avl_node<T> *right = nullptr,
           size_type h = 0)
      : value(val), parent(parent), left(left), right(right), height(h) {}
};

template<class T, class Compare = std::less<T>>
class avl {
public:
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef avl_node<value_type> node_type;
  typedef avl<T, Compare> this_type;

private:
  node_type *_root;
  size_type _size;
  Compare comp;

private:
  node_type *min_child(node_type *p);
  node_type *max_child(node_type *p);
  void rotate_left(node_type *p);
  void rotate_right(node_type *p);

public:
  avl();
  ~avl();

  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }

  void insert(const value_type &value);
  void erase(const value_type &value);

  node_type *find(node_type *p, const value_type &value);
  node_type *find(const value_type &value);

};

}// namespace stl

#endif//CPP_STL_AVL_H
