//
// Created by wjl on 2023/4/13.
//

#ifndef CPP_STL_VECTOR_H
#define CPP_STL_VECTOR_H

#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

namespace stl {

template<class T>
class vector {
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  static const size_type default_capacity = 5;

private:
  size_type _capacity;
  size_type _size;
  T *_elem;

  void expand();
  void shrink();
  bool range_check(size_type n);

public:
  constexpr vector();
  constexpr vector(size_type count, const T &value);
  constexpr explicit vector(size_type count);
  constexpr vector(const vector &other);
  constexpr vector(const vector &&other) noexcept;
  constexpr vector(std::initializer_list<T> init);
  constexpr ~vector();

  constexpr vector &operator=(const vector &other);
  constexpr vector &operator=(vector &&other) noexcept;
  constexpr vector &operator=(std::initializer_list<T> ilist);

  /**
   * Replace the contents with @count copies of value @value
   *
   * @count - the new size of the container
   * @value - the value to initialize elements of the container with
   */
  constexpr void assign(size_type count, const T &value);
  /**
   * Replace the contents with the elements from the initializer list @ilist
   *
   * @ilist - initializer list to copy the values from
   */
  constexpr void assign(std::initializer_list<T> ilist);

  /**
   * Returns a reference to the element at specified location @pos, with bounds checking
   *
   * @pos - position of the element to return
   * @return reference to the requested element
   * @exception - std::out_of_range
   */
  constexpr reference at(size_type pos) {
    range_check(pos);
    return _elem[pos];
  }
  constexpr const_reference at(size_type pos) const {
    range_check(pos);
    return _elem[pos];
  }


  void print() {
    std::cout << "vector(" << _capacity << ", " << _size << "): [ ";
    for (size_type i = 0; i < _size; i++) {
      std::cout << _elem[i] << " ";
    }
    std::cout << "]\n";
  }
};

template<class T>
void vector<T>::expand() {
  if (_size < _capacity) {
    return;
  }
  if (_capacity < default_capacity) {
    _capacity = default_capacity;
  }
  _capacity *= 2;
  T *old = _elem;
  _elem = new T[_capacity];
  for (size_type i = 0; i < _size; i++) {
    _elem[i] = old[i];
  }
  delete[] old;
}

template<class T>
void vector<T>::shrink() {
  if (_capacity < default_capacity * 2) {
    return;
  }
  if (_size * 4 > _capacity) {
    return;
  }
  _capacity /= 2;
  T *old = _elem;
  _elem = new T[_capacity];
  for (size_type i = 0; i < _size; i++) {
    _elem[i] = old[i];
  }
  delete[] old;
}

template<class T>
bool vector<T>::range_check(vector::size_type n) {
  if (n < _size) {
    return true;
  } else {
    throw std::out_of_range(
      "vector::range_check: n (which is " +
      std::to_string(n) +
      ") >= this->size()");
  }
}

template<class T>
constexpr vector<T>::vector() {
  _capacity = default_capacity;
  _size = 0;
  _elem = new T[_capacity];
}

template<class T>
constexpr vector<T>::vector(vector::size_type count, const T &value) {
  _capacity = default_capacity < count ? (count * 2) : default_capacity;
  _size = count;
  _elem = new T[_capacity];
  for (size_type i = 0; i < count; i++) {
    _elem[i] = value;
  }
}

template<class T>
constexpr vector<T>::vector(vector::size_type count) {
  _capacity = default_capacity < count ? (count * 2) : default_capacity;
  _size = count;
  _elem = new T[_capacity];
}

template<class T>
constexpr vector<T>::vector(const vector &other) {
  _capacity = other._capacity;
  _size = other._size;
  _elem = new T[_capacity];
  for (size_type i = 0; i < _size; i++) {
    _elem[i] = other._elem[i];
  }
}

template<class T>
constexpr vector<T>::vector(const vector &&other) noexcept {
  _capacity = other._capacity;
  _size = other._size;
  _elem = new T[_capacity];
  for (size_type i = 0; i < _size; i++) {
    _elem[i] = other._elem[i];
  }
}

template<class T>
constexpr vector<T>::vector(std::initializer_list<T> init) {
  _capacity = default_capacity < init.size() ? (2 * init.size()) : default_capacity;
  _size = init.size();
  _elem = new T[_capacity];
  size_type i = 0;
  for (auto a: init) {
    _elem[i++] = a;
  }
}

template<class T>
constexpr vector<T>::~vector() {
  delete[] _elem;
}

template<class T>
constexpr vector<T> &vector<T>::operator=(const vector &other) {
  _capacity = other._capacity;
  _size = other._size;
  _elem = new T[_capacity];
  for (size_type i = 0; i < other._size; i++) {
    _elem[i] = other._elem[i];
  }
  *this = other;
  return *this;
}

template<class T>
constexpr vector<T> &vector<T>::operator=(vector &&other) noexcept {
  _capacity = other._capacity;
  _size = other._size;
  _elem = new T[_capacity];
  for (size_type i = 0; i < other._size; i++) {
    _elem[i] = other._elem[i];
  }
  return *this;
}

template<class T>
constexpr vector<T> &vector<T>::operator=(std::initializer_list<T> ilist) {
  _capacity = default_capacity < ilist.size() ? (2 * ilist.size()) : default_capacity;
  _size = ilist.size();
  _elem = new T[_capacity];
  size_type i = 0;
  for (auto a: ilist) {
    _elem[i++] = a;
  }
  return *this;
}

template<class T>
constexpr void vector<T>::assign(vector::size_type count, const T &value) {
  _capacity = _capacity < count ? (2 * count) : _capacity;
  _size = count;
  _elem = new T[_capacity];
  for (size_t i = 0; i < _size; i++) {
    _elem[i] = value;
  }
}

template<class T>
constexpr void vector<T>::assign(std::initializer_list<T> ilist) {
  _capacity = _capacity < ilist.size() ? (2 * ilist.size()) : _capacity;
  _size = ilist.size();
  _elem = new T[_capacity];
  size_type i = 0;
  for (auto a: ilist) {
    _elem[i++] = a;
  }
}

}// namespace stl

#endif//CPP_STL_VECTOR_H
