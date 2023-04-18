//
// Created by wjl on 2023/4/13.
//

#include "vector.h"
#include <iomanip>
#include <numeric>
#include <vector>

template<class T>
void test_vector_init() {
  Log("==> test vector constructor");
  stl::vector<T> v1;
  assert(v1.empty() == true);
  stl::vector<T> v2(5, 1);
  assert(v2.size() == 5 && v2[0] == 1);
  stl::vector<T> v3(5);
  assert(v3.size() == 5 && v3[0] == 0);
  stl::vector<T> v4(v2);
  assert(v4.size() == 5 && v4[0] == 1);
  stl::vector<T> v5(v3);
  assert(v5.size() == 5 && v5[0] == 0);
  std::initializer_list<T> ilist{1, 2, 3, 4, 5, 6, 7};
  stl::vector<T> v6(ilist);
  assert(v6.size() == 7);
  Log("==> pass!");
}

template<class T>
void test_vector_operator_equal() {
  Log("==> test vector operator =");
  stl::vector<T> v1(5, 1);
  stl::vector<T> v2 = v1;
  assert(v2.size() == 5 && v2[0] == 1);
  stl::vector<T> v3 = {4, 5, 6, 7};
  assert(v3.size() == 4 && v3[0] == 4);
  Log("==> pass!");
}

template<class T>
void test_vector_assign() {
  Log("==> test vector assign()");
  stl::vector<T> v1(5, 1);
  assert(v1.size() == 5 && v1[0] == 1);
  v1.assign(6, 2);
  assert(v1.size() == 6 && v1[0] == 2);
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8});
  assert(v1.size() == 8 && v1[7] == 8);
  Log("==> pass!");
}

template<class T>
void test_vector_at() {
  Log("==> test vector at()");
  stl::vector<T> v1{1, 2, 3, 4, 5};
  v1.at(0) = 3;
  int const &a = v1.at(0);
  assert(v1.at(0) == a);
  assert(v1.at(3) == 4);
  assert(v1.at(4) == 5);
  Log("==> pass!");
}

template<class T>
void test_vector_operator_pos() {
  Log("==> test vector operator []");
  stl::vector<T> numbers{2, 4, 6, 8};
  assert(numbers[1] == 4);
  numbers[0] = 5;
  assert(numbers[0] == 5);
  Log("==> pass!");
}

template<class T>
void test_vector_front() {
  Log("==> test vector front()");
  stl::vector<T> v{1, 2, 3, 4, 5};
  assert(v.front() == 1);
  Log("==> pass!");
}

template<class T>
void test_vector_back() {
  Log("==> test vector back()");
  stl::vector<T> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  assert(v.back() == 11);
  Log("==> pass!");
}

template<class T>
void test_vector_data() {
  Log("==> test vector data()");
  stl::vector<T> container{1, 2, 3, 4};
  for (std::size_t i = 0; i < 4; i++) {
    assert(container.data()[i] == i + 1);
  }
  Log("==> pass!");
}

template<class T>
void test_vector_iterator() {
  Log("==> test vector iterator");
  stl::vector<T> nums{1, 2, 3, 4, 5, 6};
  assert(*nums.begin() == 1);
  int i = 1;
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    assert(*it == i++);
  }
  i = 1;
  for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
    assert(*it == i++);
  }
  i = 6;
  for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
    assert(*it == i--);
  }
  i = 6;
  for (auto it = nums.crbegin(); it != nums.crend(); ++it) {
    assert(*it == i--);
  }
  i = 1;
  for (auto &it: nums) {
    assert(it == i++);
  }
  Log("==> pass!");
}

template<class T>
void test_vector_empty() {
  Log("==> test vector empty()");
  stl::vector<T> v;
  assert(v.empty() == true);
  v = {1, 2, 3, 4};
  assert(v.empty() == false);
  assert(v.size() == 4);
  Log("==> pass!");
}

template<class T>
void test_vector_reserve() {
  Log("==> test vector reserve()");
  stl::vector<T> v{1, 2, 3, 4};
  v.reserve(4);
  assert(v.capacity() == 4);
  v.reserve(5);
  assert(v.capacity() == 5);
  Log("==> pass!");
}

template<class T>
void test_vector_capacity() {
  Log("==> test vector capacity()");
  stl::vector<T> v{1, 2, 3};
  assert(v.capacity() == 5);
  v = {1, 2, 3, 4, 5, 6};
  assert(v.capacity() == 12);
  Log("==> pass!");
}

template<class T>
void test_vector_shrink_to_fit() {
  Log("==> test vector shrink_to_fit()");
  stl::vector<T> v{1, 2, 3, 4, 5, 6, 7};
  v.reserve(100);
  assert(v.capacity() == 100);
  v.shrink_to_fit();
  assert(v.capacity() == 50);
  Log("==> pass!");
}

template<class T>
void test_vector_clear() {
  Log("==> test vector clear()");
  stl::vector<T> v{1, 2, 3};
  assert(v.size() == 3 && v.capacity() == 5);
  v.clear();
  assert(v.empty() == true && v.capacity() == 5);
  Log("==> pass!");
}

template<class T>
void test_vector_insert() {
  Log("==> test vector insert()");
  stl::vector<T> v1{1, 2, 3, 4};
  T a = 5;
  auto it = v1.end();
  v1.insert(it, std::move(a));
  assert(v1.size() == 5 && v1[4] == 5);
  v1.reserve(20);
  v1.insert(v1.begin(), 12, 7);
  assert(v1.size() == 17 && v1[0] == 7 && v1[11] == 7 && v1[12] == 1);
  stl::vector<T> v2{1, 2, 3, 4, 5};
  v2.reserve(10);
  std::initializer_list<T> ilist{1, 2, 3};
  v2.insert(v2.begin() += 2, ilist);
  assert(v2.size() == 8 && v2[2] == 1 && v2[3] == 2 && v2[4] == 3);
  Log("==> pass!");
}

template<class T>
void test_vector_emplace() {
  Log("==> test vector emplace()");
  stl::vector<T> v{1, 2, 3};
  v.emplace(v.end(), 5);
  assert(v.back() == 5);
  v.emplace(v.end(), 4);
  assert(v.back() == 4);
  T a = 1;
  v.emplace(v.begin(), a);
  assert(v.front() == a);
  v.emplace(v.begin(), std::move(a));
  assert(v.front() == 1);
  assert(v.size() == 7);
  Log("==> pass!");
}

template<class T>
void test_vector_erase() {
  Log("==> test vector erase()");
  stl::vector<T> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  assert(c.size() == 10);
  c.erase(c.begin());
  assert(c.size() == 9 && c.front() == 1);
  c.erase(c.begin() + 2, c.begin() + 5);
  assert(c.size() == 6);
  for (stl::vector<int>::iterator it = c.begin(); it != c.end();) {
    if (*it % 2 == 0) {
      it = c.erase(it);
    } else {
      ++it;
    }
  }
  assert(c.size() == 3 && c[0] == 1 && c[1] == 7 && c[2] == 9);
  Log("==> pass!");
}

void test_vector_push_back() {
  Log("==> test vector push_back()");
  stl::vector<std::string> letters;
  std::string a = "abc";
  letters.push_back(a);
  assert(letters.size() == 1 && letters.front() == "abc");
  std::string s{"def"};
  letters.push_back(std::move(s));
  assert(letters.size() == 2 && letters.back() == "def");
  Log("==> pass!");
}

void test_vector_emplace_back() {
  Log("==> test vector emplace_back()");
  struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    Point(Point &&other)  noexcept : x(other.x), y(other.y) {}
    Point &operator=(const Point &other) = default;
  };
  stl::vector<Point> v;
  for (size_t i = 0; i < 5; i++) {
    v.emplace_back(i, i);
  }
  assert(v.size() == 5);
  int i = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    assert(it->x == i && it->y == i);
    i++;
  }
  Log("==> pass!");
}

template<class T>
void test_vector_pop_back() {
  Log("==> test vector pop_back()");
  stl::vector<T> v{3, 2, 1};
  assert(v.size() == 3 && v.back() == 1);
  v.pop_back();
  assert(v.size() == 2 && v.back() == 2);
  v.pop_back();
  assert(v.size() == 1 && v.back() == 3);
  v.pop_back();
  Log("==> pass!");
}

template<class T>
void test_vector_resize() {
  Log("==> test vector resize()");
  stl::vector<T> v = {1, 2, 3};
  v.resize(5);
  assert(v.size() == 5 && v.back() == 0);
  v.resize(2);
  assert(v.size() == 2 && v.back() == 2);
  v.resize(6, 4);
  assert(v.size() == 6 && v[2] == 4);
  Log("==> pass!");
}

template<class T>
void test_vector_swap() {
  Log("==> test vector swap()");
  stl::vector<T> a1{1, 2, 3}, a2{4, 5};
  auto it1 = a1.begin() + 1;
  auto it2 = a2.begin() + 1;
  T &ref1 = a1.front();
  T &ref2 = a2.front();
  assert(*it1 == 2 && *it2 == 5 && ref1 == 1 && ref2 == 4);
  a1.swap(a2);
  assert(*it1 == 2 && *it2 == 5 && ref1 == 1 && ref2 == 4);
  stl::swap(a1, a2);
  assert(*it1 == 2 && *it2 == 5 && ref1 == 1 && ref2 == 4);
  Log("==> pass!");
}

template<class T>
void test_operator_equal_equal() {
  Log("==> test operator ==");
  std::vector<T> alice{1, 2, 3};
  std::vector<T> bob{7, 8, 9, 10};
  std::vector<T> eve{1, 2, 3};
  assert(!(alice == bob));
  assert(alice == eve);
  Log("==> pass!");
}

void test_erase_if() {
  Log("==> test erase_if()");
  stl::vector<char> cnt;
  for (char i = '0'; i <= '9'; i++) {
    cnt.push_back(i);
  }
  assert(cnt.size() == 10 && cnt.back() == '9');
  stl::erase(cnt, '3');
  assert(cnt.size() == 9 && cnt[3] == '4');
  auto erased = stl::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
  assert(erased == 5);
  Log("==> pass!");
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
  test_vector_iterator<T>();
  test_vector_empty<T>();
  test_vector_reserve<T>();
  test_vector_capacity<T>();
  test_vector_shrink_to_fit<T>();
  test_vector_clear<T>();
  test_vector_insert<T>();
  test_vector_emplace<T>();
  test_vector_erase<T>();
  test_vector_push_back();
  test_vector_emplace_back();
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
