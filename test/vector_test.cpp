//
// Created by wjl on 2023/4/13.
//

#include "vector.h"

template<class T>
void test_vector_init() {
  stl::vector<T> v1;
  v1.print();
  stl::vector<T> v2(5, 1);
  v2.print();
  stl::vector<T> v3(5);
  v3.print();
  stl::vector<T> v4(v1);
  v4.print();
  stl::vector<T> v5(std::move(v2));
  v5.print();
  std::initializer_list<T> ilist{1, 2, 3, 4, 5, 6, 7};
  stl::vector<T> v6(ilist);
  v6.print();
}

template<class T>
void test_vector_operator_equal() {
  stl::vector<T> v1(5, 1);
  v1.print();
  stl::vector<T> v2 = v1;
  v2.print();
  stl::vector<T> v3 = {4, 5, 6, 7};
  v3.print();
}

template<class T>
void test_vector_assign() {
  stl::vector<T> v1(5, 1);
  v1.print();
  v1.assign(6, 2);
  v1.print();
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8});
  v1.print();
}

template<class T>
void test_vector_at() {
  stl::vector<T> v1{1, 2, 3, 4, 5};
  v1.at(0) = 3;
  int const &a = v1.at(0);
  assert(v1.at(0) == a);
  assert(v1.at(3) == 4);
  assert(v1.at(4) == 5);
//  try {
//    v1.at(5);
//  } catch (std::out_of_range const &exc) {
//    std::cout << exc.what() << "\n";
//  }
}

template<class T>
void test_vector_operator_pos() {
  stl::vector<T> numbers {2, 4, 6, 8};
  assert(numbers[1] == 4);
  numbers[0] = 5;
  assert(numbers[0] == 5);
}

template<class T>
void test_vector_front() {
  stl::vector<T> v{1, 2, 3, 4, 5};
  assert(v.front() == 1);
}

template<class T>
void test_vector_back() {
  stl::vector<T> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  assert(v.back() == 11);
}

template<class T>
void test_vector_data() {
  stl::vector<T> container{1, 2, 3, 4};
  for (std::size_t i = 0; i < 4; i++) {
    assert(container.data()[i] == i + 1);
  }
}

template<class T>
void test_vector_begin_end() {
  stl::vector<T> nums{1, 2, 3, 4, 5, 6};
  assert(*nums.begin() == 1);
  int i = 1;
  for (auto it = nums.begin(), end = nums.end(); it >= end; ++it) {
    assert(*it == i++);
  }
  i = 6;
  for (auto it = nums.end(), end = nums.begin(); it >= end; --it) {
    assert(*it == i--);
  }
}

template<class T>
void test_vector_empty() {
  stl::vector<T> v;
  assert(v.empty() == true);
  assert(v.size() == 0);
  v = {1, 2, 3, 4};
  assert(v.empty() == false);
  assert(v.size() == 4);
}

template<class T>
void test_vector_reserve() {
  stl::vector<T> v{1, 2, 3, 4};
  v.reserve(4);
  v.reserve(5);
}

template<class T>
void test_vector_capacity() {
  stl::vector<T> v{1, 2, 3};
  assert(v.capacity() == 5);
  v = {1, 2, 3, 4, 5, 6};
  assert(v.capacity() == 12);
}

template<class T>
void test_vector_shrink_to_fit() {
  stl::vector<T> v{1, 2, 3, 4, 5, 6, 7};
  std::cout << v.capacity() << "\n";
  v.shrink_to_fit();
  std::cout << v.capacity() << "\n";
}

template<class T>
void test_vector_clear() {
  stl::vector<T> v{1, 2, 3};
  assert(v.size() == 3 && v.capacity() == 5);
  v.clear();
  assert(v.size() == 0 && v.capacity() == 5);
}

template<class T>
void test_vector_insert() {
  stl::vector<T> v1{1, 2, 3, 4};
  v1.print();
  v1.insert(2, 5);
  v1.print();
  v1.insert(2, 12, 7);
  v1.print();
  stl::vector<T> v2{1, 2, 3, 4, 5};
  v2.print();
  std::initializer_list<T> ilist{1, 2, 3};
  v2.insert(3, ilist);
  v2.print();
}

template<class T>
void test_vector() {
  test_vector_init<T>();
  test_vector_operator_equal<T>();
  test_vector_assign<T>();
  test_vector_at<T>();
  test_vector_operator_pos<T>();
  test_vector_front<T>();
  test_vector_back<T>();
  test_vector_data<T>();
  test_vector_begin_end<T>();
  test_vector_empty<T>();
  test_vector_reserve<T>();
  test_vector_capacity<T>();
  test_vector_shrink_to_fit<T>();
  test_vector_clear<T>();
  test_vector_insert<T>();
}

int main() {
  test_vector<int>();
  return 0;
}
