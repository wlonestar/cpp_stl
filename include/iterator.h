//
// Created by wjl on 2023/4/18.
//

#ifndef CPP_STL_ITERATOR_H
#define CPP_STL_ITERATOR_H

#pragma once

#include <iterator>

namespace stl {

template<class Iterator, typename Container>
class base_iterator {
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

  base_iterator() : current(Iterator()) {}
  explicit base_iterator(const Iterator &i) : current(i) {}

  reference operator*() const {
    return *current;
  }

  pointer operator->() const {
    return current;
  }

  base_iterator &operator++() {
    ++current;
    return *this;
  }

  base_iterator operator++(int) {
    return base_iterator(current++);
  }

  base_iterator &operator--() {
    --current;
    return *this;
  }

  base_iterator operator--(int) {
    return base_iterator(current--);
  }

  reference operator[](difference_type n) const {
    return current[n];
  }

  base_iterator &operator+=(difference_type n) {
    current += n;
    return *this;
  }

  base_iterator operator+(difference_type n) const {
    return base_iterator(current + n);
  }

  base_iterator &operator-=(difference_type n) {
    current -= n;
    return *this;
  }

  base_iterator operator-(difference_type n) const {
    return base_iterator(current - n);
  }

  const Iterator &base() const {
    return current;
  }
};

template<typename IteratorL, typename IteratorR, typename Container>
constexpr bool operator==(const base_iterator<IteratorL, Container> &lhs,
                          const base_iterator<IteratorR, Container> &rhs) {
  return lhs.base() == rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline auto operator-(const base_iterator<IteratorL, Container> &lhs,
                      const base_iterator<IteratorR, Container> &rhs) noexcept {
  return lhs.base() - rhs.base();
}

template<typename Iterator, typename Container>
inline typename base_iterator<Iterator, Container>::difference_type
operator-(const base_iterator<Iterator, Container> &lhs,
          const base_iterator<Iterator, Container> &rhs) {
  return lhs.base() - rhs.base();
}

template<typename Iterator, typename Container>
inline base_iterator<Iterator, Container> operator+(
  typename base_iterator<Iterator, Container>::difference_type n,
  const base_iterator<Iterator, Container> &i) {
  return base_iterator<Iterator, Container>(i.base() + n);
}

}// namespace stl

#endif//CPP_STL_ITERATOR_H
