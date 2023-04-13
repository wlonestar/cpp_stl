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
  stl::vector<T> v5(v2);
  v5.print();
  stl::vector<T> v6 {1, 2, 3, 4, 5, 6, 7, 8};
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
  assert(v1.at(0) == 1);
  assert(v1.at(3) == 4);
  assert(v1.at(4) == 5);
  try {
    v1.at(5);
  } catch (std::out_of_range const &exc) {
    std::cout << exc.what() << "\n";
  }
}

template<class T>
void test_vector() {
  test_vector_init<T>();
  test_vector_operator_equal<T>();
  test_vector_assign<T>();
  test_vector_at<T>();
}

int main() {
  test_vector<int>();
  return 0;
}
