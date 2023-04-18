//
// Created by wjl on 2023/4/18.
//

#ifndef CPP_STL_ITERATOR_H
#define CPP_STL_ITERATOR_H

#pragma once

#include <iterator>

namespace stl {

template<class Iterator, typename Container>
class _iterator {
protected:
  Iterator current;

  typedef std::iterator_traits<Iterator> traits_type;

public:
  typedef Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::reference reference;
  typedef typename traits_type::pointer pointer;

  _iterator() : current(Iterator()) {}
  explicit _iterator(const Iterator &i) : current(i) {}

  reference operator*() const { return *current; }
  pointer operator->() const { return current; }
  _iterator &operator++() {
    ++current;
    return *this;
  }
  _iterator operator++(int) { return _iterator(current++); }
  _iterator &operator--() {
    --current;
    return *this;
  }
  _iterator operator--(int) { return _iterator(current--); }

  reference operator[](difference_type n) const { return current[n]; }
  _iterator &operator+=(difference_type n) {
    current += n;
    return *this;
  }
  _iterator operator+(difference_type n) const { return _iterator(current + n); }
  _iterator &operator-=(difference_type n) {
    current -= n;
    return *this;
  }
  _iterator operator-(difference_type n) const { return _iterator(current - n); }

  const Iterator &base() const { return current; }
};

template<typename IteratorL, typename IteratorR, typename Container>
constexpr bool operator==(const _iterator<IteratorL, Container> &lhs,
                          const _iterator<IteratorR, Container> &rhs) {
  return lhs.base() == rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline auto operator-(const _iterator<IteratorL, Container> &lhs,
                      const _iterator<IteratorR, Container> &rhs) noexcept {
  return lhs.base() - rhs.base();
}

template<typename Iterator, typename Container>
inline typename _iterator<Iterator, Container>::difference_type
operator-(const _iterator<Iterator, Container> &lhs,
          const _iterator<Iterator, Container> &rhs) {
  return lhs.base() - rhs.base();
}

template<typename Iterator, typename Container>
inline _iterator<Iterator, Container> operator+(typename _iterator<Iterator, Container>::difference_type n,
                                                const _iterator<Iterator, Container> &i) {
  return _iterator<Iterator, Container>(i.base() + n);
}

}// namespace stl

#endif//CPP_STL_ITERATOR_H
