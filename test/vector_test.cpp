//
// Created by wjl on 2023/4/13.
//

#include "vector.h"
#include <iomanip>
#include <numeric>
#include <vector>

template<class T>
void print_std_vector(std::vector<T> &v) {
  std::cout << "std_vector(" << v.capacity() << ", " << v.size() << "): [ ";
  for (auto it = v.begin(); it < v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "]\n";
}

template<class T>
void test_vector_init() {
  Log("test vector init");
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
  stl::vector<T> numbers{2, 4, 6, 8};
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
  Log("test vector begin");
  stl::vector<T> nums{1, 2, 3, 4, 5, 6};
  assert(*nums.begin() == 1);
  int i = 1;
  for (auto it = nums.begin(); it < nums.end(); ++it) {
    assert(*it == i++);
  }
  i = 6;
  for (auto it = nums.rbegin(); it < nums.rend(); ++it) {
    assert(*it == i--);
  }
  i = 1;
  for (auto &it: nums) {
    assert(it == i++);
  }
}

template<class T>
void test_vector_empty() {
  stl::vector<T> v;
  assert(v.empty() == true);
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
  assert(v.empty() == true && v.capacity() == 5);
}

template<class T>
void test_std_vector_insert() {
  Log("==> test std vector insert");
  std::vector<T> v1{1, 2, 3, 4};
  print_std_vector(v1);
  T a = 5;
  v1.insert(v1.end() + 3, std::move(a));
  print_std_vector(v1);
  v1.reserve(20);
  v1.insert(v1.begin(), 12, 7);
  print_std_vector(v1);
  std::vector<T> v2{1, 2, 3, 4, 5};
  print_std_vector(v2);
  v2.reserve(10);
  std::initializer_list<T> ilist{1, 2, 3};
  v2.insert(v2.begin() += 2, ilist);
  print_std_vector(v2);
}

template<class T>
void test_vector_insert() {
  Log("==> test vector insert");
  stl::vector<T> v1{1, 2, 3, 4};
  v1.print();
  T a = 5;
  v1.insert(v1.end() + 3, std::move(a));
  v1.print();
  v1.reserve(20);
  v1.insert(v1.begin(), 12, 7);
  v1.print();
  stl::vector<T> v2{1, 2, 3, 4, 5};
  v2.print();
  v2.reserve(10);
  std::initializer_list<T> ilist{1, 2, 3};
  v2.insert(v2.begin() += 2, ilist);
  v2.print();
}

template<class T>
void test_std_vector_emplace() {
  Log("==> test std vector emplace");
  std::vector<T> v{1, 2, 3};
  print_std_vector(v);
  v.emplace(v.end(), 5);
  v.emplace(v.end(), 4);
  T a = 1;
  v.emplace(v.begin(), a);
  v.emplace(v.begin(), std::move(a));
  print_std_vector(v);
}

template<class T>
void test_vector_emplace() {
  Log("==> test vector emplace");
  stl::vector<T> v{1, 2, 3};
  v.print();
  v.emplace(v.end(), 5);
  v.emplace(v.end(), 4);
  T a = 1;
  v.emplace(v.begin(), a);
  v.emplace(v.begin(), std::move(a));
  v.print();
}

template<class T>
void test_vector_erase() {
  Log("==> test vector erase");
  stl::vector<T> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.print();
  c.erase(c.begin());
  c.print();
  c.erase(c.begin() + 2, c.begin() + 5);
  c.print();
  // Erase all even numbers
  for (stl::vector<int>::iterator it = c.begin(); it != c.end();) {
    if (*it % 2 == 0) {
      it = c.erase(it);
    } else {
      ++it;
    }
  }
  c.print();
}

void test_vector_push_back() {
  Log("==> test vector push_back");
  stl::vector<std::string> letters;
  std::string a = "abc";
  letters.push_back(a);
  std::string s{"def"};
  letters.push_back(std::move(s));
  std::cout << "std::vector `letters` holds: ";
  for (auto &&e: letters) {
    std::cout << std::quoted(e) << ' ';
  }
  std::cout << "\nMoved-from string `s` holds: " << std::quoted(s) << '\n';
}

template<class T>
void test_vector_emplace_back() {
  Log("==> test vector emplace_back");
  stl::vector<T> v;
  for (size_t i = 0; i < 5; i++) {
    v.emplace_back((T) i);
  }
  v.print();
}

template<class T>
void test_vector_pop_back() {
  Log("--> test vector pop_back");
  stl::vector<T> v;
  v.print();
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.print();
  v.pop_back();
  v.print();
}

template<class T>
void test_vector_resize() {
  Log("==> test vector resize");
  stl::vector<T> v = {1, 2, 3};
  v.print();
  v.resize(5);
  v.print();
  v.resize(2);
  v.print();
  v.resize(6, 4);
  v.print();
}

template<class T>
void test_vector_swap() {
  stl::vector<T> a1{1, 2, 3}, a2{4, 5};
  a1.print();
  a2.print();
  auto it1 = a1.begin() + 1;
  auto it2 = a2.begin() + 1;
  T &ref1 = a1.front();
  T &ref2 = a2.front();
  std::cout << *it1 << " " << *it2 << " " << ref1 << " " << ref2 << "\n";
  a1.swap(a2);
  std::cout << *it1 << " " << *it2 << " " << ref1 << " " << ref2 << "\n";
  a1.print();
  a2.print();
  stl::swap(a1, a2);
  a1.print();
  a2.print();
}

template<class T>
void test_operator_equal_equal() {
  std::vector<T> alice{1, 2, 3};
  std::vector<T> bob{7, 8, 9, 10};
  std::vector<T> eve{1, 2, 3};
  assert(!(alice == bob));
  assert(alice == eve);
}

void test_erase_if() {
  stl::vector<char> cnt(10);
  std::iota(cnt.begin(), cnt.end(), '0');
  cnt.print();

  stl::erase(cnt, '3');
  cnt.print();

  auto erased = stl::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
  cnt.print();
  std::cout << "Erased even numbers: " << erased << '\n';
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
  test_std_vector_insert<T>();
  test_vector_insert<T>();
  test_std_vector_emplace<T>();
  test_vector_emplace<T>();
  test_vector_erase<T>();
  test_vector_push_back();
  test_vector_emplace_back<T>();
  test_vector_pop_back<T>();
  test_vector_resize<T>();
  test_vector_swap<T>();
  test_operator_equal_equal<T>();
  test_erase_if();
}

int main() {
  test_vector<int>();
  return 0;
}
