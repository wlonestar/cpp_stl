//
// Created by wjl on 2023/4/17.
//

#ifndef CPP_STL_LIST_H
#define CPP_STL_LIST_H

#pragma once

#include <cstddef>

namespace stl {

template<class T>
class list_node {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;

private:
  list_node* prev;
  list_node* next;

public:


};

template<class T>
class list {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;

  typedef list_node<T> Node;


private:
  Node *node;
  size_type _size;

public:

};

}

#endif//CPP_STL_LIST_H
