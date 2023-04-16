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
#include <utility>

namespace stl {

template<class T>
class vector {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type&  reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type * const_pointer;

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

  typedef iterator iterator;
  typedef reverse_iterator reverse_iterator;

  static const size_type default_capacity = 5;

private:
  size_type _capacity;
  size_type _size;
  T *_elem;

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
  constexpr iterator emplace(iterator pos, Args &&...args);

  /**
   * Erases the specified elements from the container.
   * Removes the element at @pos.
   *
   * @pos - iterator to the element to remove
   * @return - if @pos refers to the last element, then the end() iterator
   *    is returned.
   */
  constexpr iterator erase(iterator pos);
  /**
   * Erases the specified elements from the container.
   * Removes the elements in the range [@first, @last).
   *
   * @first, @last - range of elements to remove
   * @return - if @last == end() prior to removal, then the updated end()
   *    iterator is returned.
   *    if [@first, @last) is an empty range, then @last is returned.
   */
  constexpr iterator erase(iterator first, iterator last);

  /**
   * Appends the given element value to the end of the container.
   *
   * If the new size() is greater than capacity() then all iterators and
   * references (including the end() iterator) are invalidated.
   * Otherwise only the end() iterator is invalidated.
   *
   * @value - the value of the element to append
   */
  constexpr void push_back(const T &value);
  constexpr void push_back(T &&value);

  /**
   * Appends a new element to the end of the container.
   *
   * If the new size() is greater than capacity() then all iterators and
   * references (including the end() iterator) are invalidated.
   * Otherwise only the end() iterator is invalidated.
   *
   * @args - arguments to forward to the constructor of the element
   */
  template<class... Args>
  constexpr reference emplace_back(Args &&...args);

  /**
   * Removes the last element of the container.
   *
   * Calling pop_back on an empty container results in undefined behavior.
   * Iterators and references to the last element, as well as the end()
   * iterator, are invalidated.
   */
  constexpr void pop_back();

  /**
   * Resizes the container to contain @count element, does nothing
   * if @count == size().
   *
   * If the current size is greater than @count, the container is reduced to
   * its first @count elements.
   * If the current size is less than @count, additional default-inserted
   * elements are appended.
   *
   * @count - new size of the container
   */
  constexpr void resize(size_type count);
  /**
   * Resizes the container to contain @count element, does nothing
   * if @count == size().
   *
   * If the current size is greater than @count, the container is reduced to
   * its first @count elements.
   * If the current size is less than @count, additional copies of @value are
   * appended.
   *
   * @count - new size of the container
   * @value - the value to initialize the new elements with
   */
  constexpr void resize(size_type count, const value_type &value);

  /**
   * Exchanges the contents and capacity of the container with those of @other.
   * Does not invoke any move, copy, or swap operations on individual elements.
   *
   * All iterators and references remain valid.
   * The end() iterator is invalidated.
   *
   * @other - container to exchange the contents with
   */
  constexpr void swap(vector &other) noexcept;

  void print() {
    std::cout << "vector(" << _capacity << ", " << _size << "): [ ";
    for (size_type i = 0; i < _size; i++) {
      std::cout << _elem[i] << " ";
    }
    std::cout << "]\n";
  }
};

/**
 * Compares the contents of two vectors.
 *
 * @lhs, @rhs - vectors whose contents to compare
 * @return - true if the contents of the vectors are equal, false otherwise
 */
template<class T>
constexpr bool operator==(const stl::vector<T> &lhs, const stl::vector<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (auto liter = lhs.begin(), riter = rhs.begin(); liter < lhs.end(); liter++, riter++) {
    if (std::cmp_not_equal(*liter, *riter)) {
      return false;
    }
  }
  return true;
}

/**
 * Specializes the std::swap algorithm for stl::vector.
 * Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
 *
 * @lhs, @rhs - containers whose contents to swap
 */
template<class T>
constexpr void swap(stl::vector<T> &lhs, stl::vector<T> &rhs) noexcept {
  lhs.swap(rhs);
}

/**
 * Erases all elements that compare equal to value from the container.
 *
 * @c - container from which to erase
 * @value - value to be removed
 * @return - the number of erased elements
 */
template<class T, class U>
constexpr typename stl::vector<T>::size_type erase(stl::vector<T> &c, const U &value) {
  typename stl::vector<T>::size_type size = 0;
  for (typename vector<T>::iterator it = c.begin(); it < c.end(); it++) {
    if (*it == value) {
      size++;
      c.erase(it);
      it--;
    }
  }
  return size;
}

/**
 * Erases all elements that satisfy the predicate pred from the container.
 *
 * @c - container from which to erase
 * @pred - unary predicate which returns true if the element should be erased
 * @return - the number of erased elements
 */
template<class T, class Pred>
constexpr typename stl::vector<T>::size_type erase_if(stl::vector<T> &c, Pred pred) {
  typename stl::vector<T>::size_type size = 0;
  for (typename vector<T>::iterator it = c.begin(); it < c.end(); it++) {
    if (pred(*it)) {
      size++;
      c.erase(it);
      it--;
    }
  }
  return size;
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
  *pos = std::move(value);
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
constexpr vector<T>::iterator vector<T>::emplace(vector::iterator pos, Args &&...args) {
  auto value = new T(std::forward<Args>(args)...);
  return insert(pos, *value);
}

template<class T>
constexpr vector<T>::iterator vector<T>::erase(vector::iterator pos) {
  for (iterator i = pos; i < end(); i++) {
    value_type t = *(i + 1);
    *i = t;
  }
  _size--;
  return pos == (end() - 1) ? end() : pos;
}

template<class T>
constexpr vector<T>::iterator vector<T>::erase(vector::iterator first, vector::iterator last) {
  size_type removed = last - first;
  for (iterator i = first; i < end(); i++) {
    value_type t = *(i + removed);
    *i = t;
  }
  _size -= removed;
  if (last == end()) {
    return end();
  }
  if (first == last) {
    return last;
  }
  return last;
}

template<class T>
constexpr void vector<T>::push_back(const T &value) {
  if (_size + 1 > _capacity) {
    reserve(_size * 2);
  }
  _elem[_size] = value;
  _size++;
}

template<class T>
constexpr void vector<T>::push_back(T &&value) {
  if (_size + 1 > _capacity) {
    reserve(_size * 2);
  }
  _elem[_size] = std::move(value);
  _size++;
}

template<class T>
template<class... Args>
constexpr vector<T>::reference vector<T>::emplace_back(Args &&...args) {
  auto value = new T(std::forward<Args>(args)...);
  push_back(*value);
  return *value;
}

template<class T>
constexpr void vector<T>::pop_back() {
  _size--;
}

template<class T>
constexpr void vector<T>::resize(vector::size_type count) {
  if (_size >= count) {
    _size = count;
  } else {
    reserve(count);
    size_type oldSize = _size;
    for (size_type i = 0; i < count - oldSize; i++) {
      push_back(0);
    }
  }
}

template<class T>
constexpr void vector<T>::resize(vector::size_type count, const value_type &value) {
  if (_size >= count) {
    _size = count;
  } else {
    reserve(count);
    size_type oldSize = _size;
    for (size_type i = 0; i < count - oldSize; i++) {
      push_back(value);
    }
  }
}

template<class T>
constexpr void vector<T>::swap(vector &other) noexcept {
  std::swap(_elem, other._elem);
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
}

}// namespace stl

#endif//CPP_STL_VECTOR_H
