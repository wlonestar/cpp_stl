//
// Created by wjl on 2023/4/13.
//

#ifndef CPP_STL_VECTOR_H
#define CPP_STL_VECTOR_H

#pragma once

#include "util.h"

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

namespace stl {

template<class T>
class vector {
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;

public:
  class iterator {
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

  private:
    pointer ptr;

  public:
    explicit iterator(pointer ptr) : ptr(ptr) {}

    reference operator*() { return *ptr; }
    const_reference operator*() const { return *ptr; }
    pointer operator->() { return ptr; }
    const_pointer operator->() const { return ptr; }

    iterator &operator++() {
      ptr++;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      ptr--;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    iterator operator+=(int n) {
      ptr += n;
      return *this;
    }
    iterator operator-=(int n) {
      ptr -= n;
      return *this;
    }

    iterator operator+(int n) {
      iterator tmp = *this;
      tmp.ptr += n;
      return tmp;
    }
    iterator operator-(int n) {
      iterator tmp = *this;
      tmp.ptr -= n;
      return tmp;
    }

    difference_type operator-(iterator const &r) const { return ptr - r.ptr; }

    bool operator<(iterator const &r) const { return ptr < r.ptr; }
    bool operator<=(iterator const &r) const { return ptr <= r.ptr; }
    bool operator>(iterator const &r) const { return ptr > r.ptr; }
    bool operator>=(iterator const &r) const { return ptr >= r.ptr; }
    bool operator==(const iterator &r) const { return ptr == r.ptr; }
    bool operator!=(const iterator &r) const { return ptr != r.ptr; }
  };

  class reverse_iterator {
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

  private:
    pointer ptr;

  public:
    explicit reverse_iterator(pointer ptr) : ptr(ptr) {}

    reference operator*() { return *ptr; }
    const_reference operator*() const { return *ptr; }
    pointer operator->() { return ptr; }
    const_pointer operator->() const { return ptr; }

    reverse_iterator &operator++() {
      ptr--;
      return *this;
    }
    reverse_iterator operator++(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }
    reverse_iterator &operator--() {
      ptr++;
      return *this;
    }
    reverse_iterator operator--(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    reverse_iterator operator+=(int n) {
      (*this) -= n;
      return *this;
    }
    reverse_iterator operator-=(int n) {
      (*this) += n;
      return *this;
    }

    reverse_iterator operator+(int n) {
      reverse_iterator tmp(*this);
      return tmp - n;
    }
    reverse_iterator operator-(int n) {
      reverse_iterator tmp(*this);
      return tmp + n;
    }

    difference_type operator-(reverse_iterator const &r) const { return ptr - r.ptr; }

    bool operator<(reverse_iterator const &r) const { return ptr < r.ptr; }
    bool operator<=(reverse_iterator const &r) const { return ptr <= r.ptr; }
    bool operator>(reverse_iterator const &r) const { return ptr > r.ptr; }
    bool operator>=(reverse_iterator const &r) const { return ptr >= r.ptr; }
    bool operator==(const reverse_iterator &r) const { return ptr == r.ptr; }
    bool operator!=(const reverse_iterator &r) const { return ptr != r.ptr; }
  };

  using iterator = iterator;
  using reverse_iterator = reverse_iterator;

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
   * Returns a reference to the element at specified location @pos, with bounds checking.
   *
   * @pos - position of the element to return
   * @return - reference to the requested element
   * @exception - std::out_of_range
   */
  constexpr reference at(size_type pos);
  constexpr const_reference at(size_type pos) const;

  /**
   * Returns a reference to the element at specified location @pos. No bounds checking is performed.
   *
   * @pos - position of the element to return
   * @return - reference to the requested element
   */
  constexpr reference operator[](size_type pos);
  constexpr const_reference operator[](size_type pos) const;

  constexpr reference front();
  constexpr const_reference front() const;
  constexpr reference back();
  constexpr const_reference back() const;

  /**
   * Returns pointer to the underlying array serving as element storage.
   * The pointer is such that range [data(), data() + size()) is always
   * a valid range, even if the container is empty(data() is not
   * dereferenceable in that case).
   *
   * @return - Pointer to the underlying element storage, For non-empty
   * containers, the returned pointer compares equal to the address of
   * the first element
   *
   * Note: if size() is 0, data() may or may not return a null pointer.
   */
  constexpr T *data() noexcept;
  constexpr const T *data() const noexcept;

  constexpr iterator begin() noexcept;
  constexpr iterator end() noexcept;
  constexpr reverse_iterator rbegin() noexcept;
  constexpr reverse_iterator rend() noexcept;

  [[nodiscard]] constexpr bool empty() const noexcept;
  [[nodiscard]] constexpr size_type size() const noexcept;

  /**
   * Increase the capacity of the vector (the total number of elements that the
   * vector can hold without requiring reallocation) to a value that's greater
   * or equal to @new_cap. If new_cap is greater than the current capacity(),
   * new storage is allocated, otherwise the function does nothing.
   *
   * reserve() does not change the size of the vector.
   *
   * if @new_cap is greater than capacity(), all iterators, including the end()
   * iterator, and all references to the elements are invalidated. Otherwise,
   * no iterators or references are invalidated.
   *
   * After a call to reserve(), insertions will not trigger reallocation unless
   * the insertion would make the size of the vector greater than the value of
   * capacity().
   *
   * @new_cap - new capacity of the vector, in number of elements
   */
  constexpr void reserve(size_type new_cap);
  [[nodiscard]] constexpr size_type capacity() const noexcept;
  constexpr void shrink_to_fit();

  /**
   * Erases all elements from the container. After this call, size() returns
   * zero.
   * Invalidates any references, pointers, or iterators referring to contained
   * elements. Any past-the-end iterators are also invalidated.
   * Leaves the capacity() of the vector unchanged
   */
  constexpr void clear() noexcept;

  /**
   * Inserts elements at the specified location in the container.
   *
   * @pos - index before which the content will be inserted
   * @value - element value to insert
   * @return - pointer to the inserted @value
   */
  constexpr iterator insert(iterator pos, const T &value);
  /**
   * Inserts elements at the specified location in the container.
   *
   * @pos - index before which the content will be inserted
   * @value - element value to insert
   * @return - pointer to the inserted @value
   */
  constexpr iterator insert(iterator pos, T &&value);
  /**
   * Inserts elements at the specified location in the container.
   *
   * @pos - index before which the content will be inserted
   * @count - number of elements to insert
   * @value - element value to insert
   * @return - pointer to the inserted @value
   */
  constexpr iterator insert(iterator pos, size_type count, const T &value);
  /**
   * Inserts elements at the specified location in the container.
   *
   * @pos - index before which the content will be inserted
   * @ilist - initializer list to insert the values from
   * @return - pointer to the inserted @value
   */
  constexpr iterator insert(iterator pos, std::initializer_list<T> ilist);

  /**
   * Inserts a new element into the container directly before pos.
   *
   * @pos - index before which the new element will be constructed
   * @args - arguments to forward to the constructor of the element
   * @return - pointer to the emplaced element
   */
  template<class... Args>
  constexpr pointer emplace(size_type pos, Args &&...args);


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
  delete[] _elem;
  _capacity = other._capacity;
  _size = other._size;
  _elem = new T[_capacity];
  for (size_type i = 0; i < other._size; i++) {
    _elem[i] = other._elem[i];
  }
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

template<class T>
constexpr vector<T>::reference vector<T>::at(vector::size_type pos) {
  range_check(pos);
  return _elem[pos];
}

template<class T>
constexpr vector<T>::const_reference vector<T>::at(vector::size_type pos) const {
  range_check(pos);
  return _elem[pos];
}

template<class T>
constexpr vector<T>::reference vector<T>::operator[](vector::size_type pos) {
  return _elem[pos];
}

template<class T>
constexpr vector<T>::const_reference vector<T>::operator[](vector::size_type pos) const {
  return _elem[pos];
}

template<class T>
constexpr vector<T>::reference vector<T>::front() {
  return _elem[0];
}

template<class T>
constexpr vector<T>::const_reference vector<T>::front() const {
  return _elem[0];
}

template<class T>
constexpr vector<T>::reference vector<T>::back() {
  return _elem[_size - 1];
}

template<class T>
constexpr vector<T>::const_reference vector<T>::back() const {
  return _elem[_size - 1];
}

template<class T>
constexpr vector<T>::pointer vector<T>::data() noexcept {
  return _elem;
}

template<class T>
constexpr vector<T>::const_pointer vector<T>::data() const noexcept {
  return _elem;
}

template<class T>
constexpr vector<T>::iterator vector<T>::begin() noexcept {
  return iterator(&_elem[0]);
}

template<class T>
constexpr vector<T>::iterator vector<T>::end() noexcept {
  return iterator(&_elem[_size]);
}

template<class T>
constexpr vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
  return reverse_iterator(&_elem[_size - 1]);
}

template<class T>
constexpr vector<T>::reverse_iterator vector<T>::rend() noexcept {
  return reverse_iterator(&_elem[-1]);
}

template<class T>
constexpr bool vector<T>::empty() const noexcept {
  return _size == 0;
}

template<class T>
constexpr vector<T>::size_type vector<T>::size() const noexcept {
  return _size;
}

template<class T>
constexpr void vector<T>::reserve(vector::size_type new_cap) {
  assert(new_cap >= _size);
  if (new_cap <= _capacity) {
    _capacity = new_cap;
    return;
  } else {
    _capacity = new_cap;
    T *old = _elem;
    _elem = new T[_capacity];
    for (size_type i = 0; i < _size; i++) {
      _elem[i] = old[i];
    }
    delete[] old;
  }
}

template<class T>
constexpr vector<T>::size_type vector<T>::capacity() const noexcept {
  return _capacity;
}

template<class T>
constexpr void vector<T>::shrink_to_fit() {
  shrink();
}

template<class T>
constexpr void vector<T>::clear() noexcept {
  delete[] _elem;
  _elem = new T[_capacity];
  _size = 0;
}

template<class T>
constexpr vector<T>::iterator vector<T>::insert(vector::iterator pos, const T &value) {
  for (iterator i = ++end(); i > pos; i--) {
    value_type t = *(i - 1);
//    Log("pointer = %p, value = %d", i, t);
    *i = t;
  }
  *pos = value;
  _size++;
  return pos;
}

template<class T>
constexpr vector<T>::iterator vector<T>::insert(vector::iterator pos, T &&value) {
  for (iterator i = ++end(); i > pos; i--) {
    value_type t = *(i - 1);
//    Log("pointer = %p, value = %d", i, t);
    *i = t;
  }
  *pos = value;
  _size++;
  return pos;
}

template<class T>
constexpr vector<T>::iterator vector<T>::insert(vector::iterator pos, vector::size_type count, const T &value) {
  for (size_type i = 0; i < count; i++) {
    insert(pos, value);
  }
  return pos;
}

template<class T>
constexpr vector<T>::iterator vector<T>::insert(vector::iterator pos, std::initializer_list<T> ilist) {
  for (auto it = ilist.end() - 1; it >= ilist.begin(); it--) {
    insert(pos, *it);
  }
  return pos;
}

template<class T>
template<class... Args>
constexpr vector<T>::pointer vector<T>::emplace(vector::size_type pos, Args &&...args) {
  return nullptr;
}


}// namespace stl

#endif//CPP_STL_VECTOR_H
