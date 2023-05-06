//
// Created by wjl on 2023/4/24.
//

#ifndef CPP_STL_TREE_H
#define CPP_STL_TREE_H

#pragma once

#include "queue.h"
#include "stack.h"
#include "util.h"

#include <tuple>
#include <compare>
#include <iostream>
#include <type_traits>
#include <utility>

namespace stl {

template<class Pair>
struct use_first {
  typedef Pair argument_type;
  typedef typename Pair::first_type result_type;

  const result_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template<class Pair>
struct use_second {
  typedef Pair argument_type;
  typedef typename Pair::second_type result_type;

  const result_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template<bool Condition, class ConditionIsTrueType, class ConditionIsFalseType>
struct type_select {
  typedef ConditionIsTrueType type;
};

///////////////////////////////////////////////////////////////////////////////

/**
 * rbtree
 */

enum RB_COLOR {
  RB_RED,
  RB_BLACK,
};

enum RB_SIDE {
  RB_LEFT,
  RB_RIGHT,
};

/**
 * Define a tree_node_base separately from tree_node (below),
 * because it allows to have non-templated operations.
 */
struct rbtree_node_base {
  typedef rbtree_node_base this_type;

public:
  // declared first because it is used most often
  this_type *right;
  this_type *left;
  this_type *parent;
  // only need one bit here
  char color;
};

/**
 * rbtree_node
 */
template<class Value>
struct rbtree_node : public rbtree_node_base {
  /**
   * For set and multiset, this is the user's value,
   * for map and multimap, this is a pair of key/value.
   */
  Value value;
};

/**
 * rbtree_node_base functions
 */

inline rbtree_node_base *rbtree_min_child(const rbtree_node_base *p) {
  while (p->left) {
    p = p->left;
  }
  return const_cast<rbtree_node_base *>(p);
}

inline rbtree_node_base *rbtree_max_child(const rbtree_node_base *p) {
  while (p->right) {
    p = p->right;
  }
  return const_cast<rbtree_node_base *>(p);
}

/**
 * rbtree increment
 *
 * @return - the next item in a sorted red-black tree.
 */
rbtree_node_base *rbtree_increment(const rbtree_node_base *p) {
  if (p->right) {
    p = p->right;
    while (p->right) {
      p = p->left;
    }
  } else {
    rbtree_node_base *tmp = p->parent;
    while (p == tmp->right) {
      p = tmp;
      tmp = tmp->parent;
    }
    if (p->right != tmp) {
      p = tmp;
    }
  }
  return const_cast<rbtree_node_base *>(p);
}

/**
 * rbtree decrement
 *
 * @return - the previous item in a sorted red-black tree.
 */
rbtree_node_base *rbtree_decrement(const rbtree_node_base *p) {
  if ((p->parent->parent == p) && (p->color == RB_RED)) {
    return p->right;
  } else if (p->left) {
    rbtree_node_base *tmp = p->left;
    while (tmp->right) {
      tmp = tmp->right;
    }
    return tmp;
  }
  rbtree_node_base *tmp = p->parent;
  while (p == tmp->left) {
    p = tmp;
    tmp = tmp->parent;
  }
  return const_cast<rbtree_node_base *>(tmp);
}

/**
 * rbtree black count
 *
 * Counts the number of black nodes in an red-black tree, from @top down to the
 * given @bottom node.
 * We don't count red nodes because red-black trees don't really care about red
 * node counts; it is black node counts that are significant in the maintenance
 * of a balanced tree.
 */
std::size_t rbtree_get_black_count(const rbtree_node_base *top, const rbtree_node_base *bottom) {
  std::size_t count = 0;
  for (; bottom; bottom = bottom->parent) {
    if (bottom->color == RB_BLACK) {
      ++count;
    }
    if (bottom == top) {
      break;
    }
  }
  return count;
}

/**
 * rbtree rotate left
 */
rbtree_node_base *rbtree_rotate_left(rbtree_node_base *p, rbtree_node_base *root) {
  TODO();
}


rbtree_node_base *rbtree_rotate_right(rbtree_node_base *p, rbtree_node_base *root) {
  TODO();
}

rbtree_node_base *rbtree_insert(rbtree_node_base *p, rbtree_node_base *parent, rbtree_node_base *anchor, RB_SIDE insertion_side) {
  TODO();
}

rbtree_node_base *rbtree_erase(rbtree_node_base *p, rbtree_node_base *anchor) {
  TODO();
}

/**
 * rbtree_iterator
 */
template<class T, class Pointer, class Reference>
struct rbtree_iterator {
  typedef rbtree_iterator<T, Pointer, Reference> this_type;
  typedef rbtree_iterator<T, T *, T &> iterator;
  typedef rbtree_iterator<T, const T *, const T &> const_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef rbtree_node_base base_node_type;
  typedef rbtree_node<T> node_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef std::bidirectional_iterator_tag iterator_category;

public:
  node_type *node;

public:
  rbtree_iterator() : node(NULL) {}

  explicit rbtree_iterator(const node_type *p)
      : node(static_cast<node_type *>(const_cast<node_type *>(p))) {}

  rbtree_iterator(const iterator &x) : node(x.node) {}

  rbtree_iterator &operator=(const iterator &x) {
    node = x.node;
    return *this;
  }

  reference operator*() const {
    return node->value;
  }

  pointer operator->() const {
    return &node->value;
  }

  rbtree_iterator &operator++() {
    node = static_cast<node_type *>(rbtree_increment(node));
    return *this;
  }

  rbtree_iterator operator++(int) {
    this_type tmp(*this);
    node = static_cast<node_type *>(rbtree_increment(node));
    return tmp;
  }

  rbtree_iterator &operator--() {
    node = static_cast<node_type *>(rbtree_decrement(node));
    return *this;
  }

  rbtree_iterator operator--(int) {
    this_type tmp(*this);
    node = static_cast<node_type *>(rbtree_decrement(node));
    return tmp;
  }
};

template<class T, class PointerA, class ReferenceA, class PointerB, class ReferenceB>
inline bool operator==(const rbtree_iterator<T, PointerA, ReferenceA> &a,
                       const rbtree_iterator<T, PointerB, ReferenceB> &b) {
  return a.node == b.node;
}

template<class T, class PointerA, class ReferenceA, class PointerB, class ReferenceB>
inline bool operator!=(const rbtree_iterator<T, PointerA, ReferenceA> &a,
                       const rbtree_iterator<T, PointerB, ReferenceB> &b) {
  return a.node != b.node;
}

template<class T, class Pointer, class Reference>
inline bool operator!=(const rbtree_iterator<T, Pointer, Reference> &a,
                       const rbtree_iterator<T, Pointer, Reference> &b) {
  return a.node != b.node;
}

/**
 * rb_base_compare_ebo
 *
 * utilizes the "empty base-class optimization" to reduce the size of the rbtree
 * when its compare template argument is an empty class.
 */
template<class Compare, bool = std::is_empty<Compare>::value>
struct rb_base_compare_ebo {
private:
  Compare comp;

protected:
  rb_base_compare_ebo() : comp() {}
  rb_base_compare_ebo(const Compare &compare) : comp(compare) {}

  Compare &get_compare() {
    return comp;
  }

  const Compare &get_compare() const {
    return comp;
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) {
    return comp(lhs, rhs);
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) const {
    return comp(lhs, rhs);
  }
};

template<class Compare>
struct rb_base_compare_ebo<Compare, true> : private Compare {
protected:
  rb_base_compare_ebo() {}
  rb_base_compare_ebo(const Compare &compare) : Compare(compare) {}

  Compare &get_compare() {
    return *this;
  }

  const Compare &get_compare() const {
    return *this;
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) {
    return Compare::operator()(lhs, rhs);
  }

  template<class T>
  bool compare(const T &lhs, const T &rhs) const {
    return Compare::operator()(lhs, rhs);
  }
};

/**
 * rb_base
 *
 * This class allows us to use a generic rbtree as the basis of map, multimap,
 * set and multiset transparently. This vital template parameters for this are
 * the ExtractKey and the UniqueKeys parameters.
 *
 * If the rbtree has a value type of the form pair<T1, T2> and a key extraction
 * policy that returns the first part of the pair, the rbtree gets a mapped_type
 * typedef.
 * If it satisfies those criteria and also has unique keys, then it also gets an
 * operator[].
 */

/**
 * This specialization is used for 'set'
 */
template<class Key, class Value, class Compare, class ExtractKey, bool UniqueKeys, class RBTree>
struct rb_base : public rb_base_compare_ebo<Compare> {
  typedef ExtractKey extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'multiset'
 */
template<class Key, class Value, class Compare, class ExtractKey, class RBTree>
struct rb_base<Key, Value, Compare, ExtractKey, false, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef ExtractKey extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'map'
 */
template<class Key, class Pair, class Compare, class RBTree>
struct rb_base<Key, Pair, Compare, use_first<Pair>, true, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef use_first<Pair> extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * This specialization is used for 'multimap'
 */
template<class Key, class Pair, class Compare, class RBTree>
struct rb_base<Key, Pair, Compare, use_first<Pair>, false, RBTree> : public rb_base_compare_ebo<Compare> {
  typedef use_first<Pair> extract_key;

protected:
  using rb_base_compare_ebo<Compare>::compare;
  using rb_base_compare_ebo<Compare>::get_compare;

public:
  rb_base() {}
  rb_base(const Compare &compare) : rb_base_compare_ebo<Compare>(compare) {}
};

/**
 * rbtree
 */

/**
 * rbtree
 *
 * rbtree is the red-black tree basis for the map, multimap, set, multiset
 * containers. Just about all the work of those containers is done here, and they
 * are merely a shell which sets template polices that govern the code generation
 * for this rbtree.
 *
 * This rbtree implementation is pretty much the same as all other modern rbtree
 * implementations, as the topic is well known and researched. Choose to
 * implement a "relaxed balancing" option at some point in the future if it is
 * deemed worthwhile. Most rbtree implementations don't do this.
 *
 * The primary rbtree member variable is @_anchor, which is a node_type and acts
 * as the end_node. However, like any other node, it has left, right and parent
 * members. We do the conventional trick of assigning begin() (left-most rbtree
 * node)  to left, assigning 'end() - 1' to right, and assigning the tree root
 * node to parent.
 *
 * @Compare(functor): This is a comparison class which defaults to 'less'.
 * It is a common STL thing which takes arguments and returns true if the first
 * is less than the second.
 *
 * @ExtractKey(functor): This is a class which gets the key from a stored node.
 * With map and set, the node is a pair, whereas with set and multiset the node
 * is just the value. ExtractKey will be either @use_first (map and multimap) or
 * @use_self(set and multiset).
 *
 * @MutableIterators(bool): true if rbtree::iterator is a mutable iterator, false
 * if iterator and const_iterator are both const iterators. It will be true for
 * map and multimap and false for set and multiset.
 *
 * @UniqueKeys(bool): true if the keys are to be unique, and false if there can be
 * multiple instances of a given key. It will be true for set and map and false
 * for multiset and multimap.
 *
 * To consider: Add an option for relaxed tree balancing. This could result in
 * performance improvements but would require a more complicated implementation,
 *
 * @find_as:
 * In order to support the ability to have a tree of strings but be able to do
 * efficiently lookups via char pointers, we provide the @find_as function.
 * This function allows you to do a find with a key of a type other than the
 * tree's key type. See the @find_as function for more documentation on this.
 */
template<class Key, class Value, class Compare, class ExtractKey, bool MutableIterators, bool UniqueKeys>
class rbtree : public rb_base<Key, Value, Compare, ExtractKey, UniqueKeys, rbtree<Key, Value, Compare, ExtractKey, MutableIterators, UniqueKeys>> {
public:
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;
  typedef Key key_type;
  typedef Value value_type;
  typedef rbtree_node<value_type> node_type;
  typedef const value_type &reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  typedef typename type_select<MutableIterators,
                               rbtree_iterator<value_type, value_type *, value_type &>,
                               rbtree_iterator<value_type, const value_type *, const value_type &>>::type iterator;
  typedef rbtree_iterator<value_type, const value_type *, const value_type &> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef Compare key_compare;
  // map/set::insert return a pair, multimap/multiset::iterator return an iterator
  typedef typename type_select<UniqueKeys, std::pair<iterator, bool>, iterator>::type insert_return_type;
  typedef rbtree<Key, Value, Compare, ExtractKey, MutableIterators, UniqueKeys> this_type;
  typedef rb_base<Key, Value, Compare, ExtractKey, UniqueKeys, this_type> base_type;
  typedef std::integral_constant<bool, UniqueKeys> has_unique_keys_type;
  typedef typename base_type::extract_key extract_key;

protected:
  using base_type::compare;
  using base_type::get_compare;

public:
  /**
   * This node acts as end() and its left points to begin(),
   * and right points to rbegin() (the last node on the right)
   */
  rbtree_node_base _anchor;
  /**
   * Stores the count of nodes in the tree (not counting the anchor node)
   */
  size_type _size;

public:
  rbtree() : _anchor(), _size(0) {
    reset_lose_memory();
  }

  rbtree(const Compare &compare) : base_type(compare), _anchor(), _size(0) {
    reset_lose_memory();
  }

  rbtree(const this_type &x) : base_type(x.get_compare), _anchor(), _size(0) {
    reset_lose_memory();
    if (x._anchor.parent) {
      _anchor.parent = copy_subtree((const node_type *) x._anchor.parent, (node_type *) &_anchor);
      _anchor.right = rbtree_max_child(_anchor.parent);
      _anchor.left = rbtree_min_child(_anchor.parent);
      _size = x._size;
    }
  }

  rbtree(this_type &&x) : base_type(x.get_compare), _anchor(), _size(0) {
    reset_lose_memory();
    swap(x);
  }

  ~rbtree() {
    nuke_subtree((node_type *)_anchor.parent);
  }

public:
  key_compare &key_comp() {
    return get_compare();
  }

  const key_compare &key_comp() const {
    return get_compare();
  }

  this_type &operator=(const this_type &x) {
    if (this != &x) {
      clear();
      get_compare() = x.get_compare();
      if (x._anchor.parent) {
        _anchor.parent = copy_subtree((const node_type *) x._anchor.parent, (node_type *) &_anchor);
        _anchor.right = rbtree_max_child(_anchor.parent);
        _anchor.left = rbtree_min_child(_anchor.parent);
        _size = x._size;
      }
    }
    return *this;
  }

  this_type &operator=(this_type &&x) {
    if (this != &x) {
      clear();
      swap(x);
    }
    return *this;
  }

  this_type &operator=(std::initializer_list<value_type> ilist) {
    clear();
    for (typename std::initializer_list<value_type>::iterator it = ilist.begin(), itEnd = ilist.end(); it != itEnd; ++it) {
      insert_value(has_unique_keys_type(), std::move(*it));
    }
    return *this;
  }

  void swap(this_type &x) {
    std::swap(_size, x._size);
    std::swap(get_compare(), x.get_compare());

    if (_anchor.parent && x._anchor.parent) {
      std::swap(_anchor.right, x._anchor.right);
      std::swap(_anchor.left, x._anchor.left);
      std::swap(_anchor.parent, x._anchor.parent);
      _anchor.parent->parent = &_anchor;
      x._anchor.parent->parent = &x._anchor;
    } else if (_anchor.parent) {
      x._anchor.right = _anchor.right;
      x._anchor.left = _anchor.left;
      x._anchor.parent = _anchor.parent;
      x._anchor.parent->parent = &x._anchor;

      _anchor.right = &_anchor;
      _anchor.left = &_anchor;
      _anchor.parent = NULL;
    } else if (x._anchor.parent) {
      _anchor.right = x._anchor.right;
      _anchor.left = x._anchor.left;
      _anchor.parent = x._anchor.parent;
      _anchor.parent->parent = &_anchor;

      x._anchor.right = &x._anchor;
      x._anchor.left = &x._anchor;
      x._anchor.parent = NULL;
    }
  }

public:
  iterator begin() noexcept {
    return iterator(static_cast<node_type*>(_anchor.left));
  }

  const_iterator begin() const noexcept {
    return const_iterator(static_cast<node_type*>(const_cast<rbtree_node_base*>(_anchor.left)));
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(static_cast<node_type*>(const_cast<rbtree_node_base*>(_anchor.left)));
  }

  iterator end() noexcept {
    return iterator(static_cast<node_type*>(_anchor));
  }

  const_iterator end() const noexcept {
    return const_iterator(static_cast<node_type*>(const_cast<rbtree_node_base*>(&_anchor)));
  }

  const_iterator cend() const noexcept {
    return const_iterator(static_cast<node_type*>(const_cast<rbtree_node_base*>(&_anchor)));
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }

public:
  bool empty() const noexcept {
    return _size == 0;
  }

  size_type size() const noexcept {
    return _size;
  }

  template<class... Args>
  insert_return_type emplace(Args &&...args) {
    return insert_value(has_unique_keys_type(), std::forward<Args>(args)...);
  }

  template<class... Args>
  iterator emplace_hint(const_iterator position, Args &&...args) {
    return insert_value(has_unique_keys_type(), position, std::forward<Args>(args)...);
  }

  template<class P, class = typename std::enable_if<std::is_constructible<value_type, P &&>::value>::type>
  insert_return_type insert(P &&other) {
    return emplace(std::forward<P>(other));
  }

  iterator insert(const_iterator position, value_type &&value) {
    return insert_value_hint(has_unique_keys_type(), position, std::move(value));
  }

  insert_return_type insert(const value_type &value) {
    return insert_value(has_unique_keys_type(), value);
  }

  iterator insert(const_iterator position, const value_type &value) {
    return insert_value_hint(has_unique_keys_type(), position, value);
  }

  void insert(std::initializer_list<value_type> ilist) {
    for (typename std::initializer_list<value_type>::iterator it = ilist.begin(), it_end = ilist.end(); it != it_end; ++it) {
      insert_value(has_unique_keys_type(), std::move(*it));
    }
  }

  template<class M>
  std::pair<iterator, bool> insert_or_assign(const key_type &k, M &&obj) {
    auto iter = find(k);
    if (iter == end()) {
      // TODO
      return insert(value_type(std::forward_as_tuple(k), std::forward_as_tuple(std::forward<M>(obj))));
    } else {
      iter->second = std::forward<M>(obj);
      return { iter, false };
    }
  }

  template<class M>
  std::pair<iterator, bool> insert_or_assign(key_type &&k, M &&obj) {
    auto iter = find(k);
    if (iter == end()) {
      // TODO
      return insert(value_type(std::forward_as_tuple(std::move(k)), std::forward_as_tuple(std::forward<M>(obj))));
    } else {
      iter->second = std::forward<M>(obj);
      return { iter, false };
    }
  }

  template<class M>
  iterator insert_or_assign(const_iterator hint, const key_type &k, M &&obj) {
    auto iter = find(k);
    if (iter == end()) {
      // TODO
      return insert(hint, value_type(std::forward_as_tuple(k), std::forward_as_tuple(std::forward<M>(obj))));
    } else {
      iter->second = std::forward<M>(obj);
      return iter;
    }
  }

  template<class M>
  iterator insert_or_assign(const_iterator hint, key_type &&k, M &&obj) {
    auto iter = find(k);
    if (iter == end()) {
      // TODO
      return insert(hint, value_type(std::forward_as_tuple(std::move(k)), std::forward_as_tuple(std::forward<M>(obj))));
    } else {
      iter->second = std::forward<M>(obj);
      return iter;
    }
  }

  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);
  reverse_iterator erase(const_reverse_iterator position);
  reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);
  void erase(const key_type *first, const key_type *last);

  void clear();
  void reset_lose_memory();

  iterator find(const key_type &key);
  const_iterator find(const key_type &key) const;

  template<class U, class Compare2>
  iterator find_as(const U &u, Compare2 compare2);
  template<class U, class Compare2>
  const_iterator find_as(const U &u, Compare2 compare2) const;

  iterator lower_bound(const key_type &key);
  const_iterator lower_bound(const key_type &key) const;
  iterator upper_bound(const key_type &key);
  const_iterator upper_bound(const key_type &key) const;

  bool validate() const;
  int validata_iterator(const_iterator i) const;

protected:
  node_type *create_node_from_key(const key_type &key);

  template<class... Args>
  node_type *create_node(Args &&...args);
  node_type *create_node(const value_type &value);
  node_type *create_node(value_type &&value);
  node_type *create_node(const node_type *p, node_type *parent);

  node_type *copy_subtree(const node_type *src, node_type *dest);
  void nuke_subtree(node_type *p);

  template<class... Args>
  std::pair<iterator, bool> insert_value(std::true_type, Args &&...args);
  template<class... Args>
  iterator insert_value(std::false_type, Args &&...args);
  std::pair<iterator, bool> insert_value(std::true_type, value_type &&value);
  iterator insert_value(std::false_type, value_type &&value);

  template<class... Args>
  iterator insert_value_impl(node_type *parent, bool force_to_left, const key_type &key, Args &&...args);
  iterator insert_value_impl(node_type *parent, bool force_to_left, const key_type &key, node_type *p);

  std::pair<iterator, bool> insert_key(std::true_type, const key_type &key);
  iterator insert_key(std::false_type, const key_type &key);

  template<class... Args>
  iterator insert_value_hint(std::true_type, const_iterator position, Args &&...args);
  template<class... Args>
  iterator insert_value_hint(std::false_type, const_iterator position, Args &&...args);
  iterator insert_value_hint(std::true_type, const_iterator position, value_type &&value);
  iterator insert_value_hint(std::false_type, const_iterator position, value_type &&value);

  iterator insert_key(std::true_type, const_iterator position, const key_type &key);
  iterator insert_key(std::false_type, const_iterator position, const key_type &key);
  iterator insert_key_impl(node_type *parent, bool force_to_left, const key_type &key);

  node_type *get_key_insert_position_unique_keys(bool &can_insert, const key_type &key);
  node_type *get_key_insert_position_nonunique_keys(const key_type &key);
  node_type *get_key_insert_position_unique_keys_hint(const_iterator position, bool &force_to_left, const key_type &key);
  node_type *get_key_insert_position_nonunique_keys_hint(const_iterator position, bool &force_to_left, const key_type &key);
};

}// namespace stl

#endif//CPP_STL_TREE_H
