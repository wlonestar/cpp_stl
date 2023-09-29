//
// Created by wjl on 2023/4/13.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector_test
#include <boost/test/included/unit_test.hpp>

#include <vector.h>

BOOST_AUTO_TEST_CASE(vector_init) {
  Log("==> test vector constructor");
  stl::vector<int> v1;
  BOOST_CHECK(v1.empty() == true);

  stl::vector<int> v2(5, 1);
  BOOST_CHECK(v2.size() == 5);
  BOOST_CHECK(v2[0] == 1);
  
  stl::vector<int> v3(5);
  BOOST_CHECK(v3.size() == 5);
  BOOST_CHECK(v3[0] == 0);
  
  stl::vector<int> v4(v2);
  BOOST_CHECK(v4.size() == 5);
  BOOST_CHECK(v4[0] == 1);

  stl::vector<int> v5(v3);
  BOOST_CHECK(v5.size() == 5);
  BOOST_CHECK(v5[0] == 0);
  
  std::initializer_list<int> ilist{1, 2, 3, 4, 5, 6, 7};
  stl::vector<int> v6(ilist);
  BOOST_CHECK(v6.size() == 7);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_operator_equal) {
  Log("==> test vector operator =");
  stl::vector<int> v1(5, 1);
  stl::vector<int> v2 = v1;
  BOOST_CHECK(v2.size() == 5);
  BOOST_CHECK(v2[0] == 1);
  stl::vector<int> v3 = {4, 5, 6, 7};
  BOOST_CHECK(v3.size() == 4);
  BOOST_CHECK(v3[0] == 4);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_assign) {
  Log("==> test vector assign()");
  stl::vector<int> v1(5, 1);
  BOOST_CHECK(v1.size() == 5);
  BOOST_CHECK(v1[0] == 1);
  v1.assign(6, 2);
  BOOST_CHECK(v1.size() == 6);
  BOOST_CHECK(v1[0] == 2);
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8});
  BOOST_CHECK(v1.size() == 8);
  BOOST_CHECK(v1[7] == 8);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_at) {
  Log("==> test vector at()");
  stl::vector<int> v1{1, 2, 3, 4, 5};
  v1.at(0) = 3;
  int const &a = v1.at(0);
  BOOST_CHECK(v1.at(0) == a);
  BOOST_CHECK(v1.at(3) == 4);
  BOOST_CHECK(v1.at(4) == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_operator_pos) {
  Log("==> test vector operator []");
  stl::vector<int> numbers{2, 4, 6, 8};
  BOOST_CHECK(numbers[1] == 4);
  numbers[0] = 5;
  BOOST_CHECK(numbers[0] == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_front) {
  Log("==> test vector front()");
  stl::vector<int> v{1, 2, 3, 4, 5};
  BOOST_CHECK(v.front() == 1);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_back) {
  Log("==> test vector back()");
  stl::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  BOOST_CHECK(v.back() == 11);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_data) {
  Log("==> test vector data()");
  stl::vector<int> container{1, 2, 3, 4};
  for (std::size_t i = 0; i < 4; i++) {
    BOOST_CHECK(container.data()[i] == i + 1);
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_iterator) {
  Log("==> test vector iterator");
  stl::vector<int> nums{1, 2, 3, 4, 5, 6};
  BOOST_CHECK(*nums.begin() == 1);
  int i = 1;
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    BOOST_CHECK(*it == i++);
  }
  i = 1;
  for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
    BOOST_CHECK(*it == i++);
  }
  i = 6;
  for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
    BOOST_CHECK(*it == i--);
  }
  i = 6;
  for (auto it = nums.crbegin(); it != nums.crend(); ++it) {
    BOOST_CHECK(*it == i--);
  }
  i = 1;
  for (auto &it: nums) {
    BOOST_CHECK(it == i++);
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_empty) {
  Log("==> test vector empty()");
  stl::vector<int> v;
  BOOST_CHECK(v.empty() == true);
  v = {1, 2, 3, 4};
  BOOST_CHECK(v.empty() == false);
  BOOST_CHECK(v.size() == 4);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_reserve) {
  Log("==> test vector reserve()");
  stl::vector<int> v{1, 2, 3, 4};
  v.reserve(4);
  BOOST_CHECK(v.capacity() == 4);
  v.reserve(5);
  BOOST_CHECK(v.capacity() == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_capacity) {
  Log("==> test vector capacity()");
  stl::vector<int> v{1, 2, 3};
  BOOST_CHECK(v.capacity() == 5);
  v = {1, 2, 3, 4, 5, 6};
  BOOST_CHECK(v.capacity() == 12);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_shrink_to_fit) {
  Log("==> test vector shrink_to_fit()");
  stl::vector<int> v{1, 2, 3, 4, 5, 6, 7};
  v.reserve(100);
  BOOST_CHECK(v.capacity() == 100);
  v.shrink_to_fit();
  BOOST_CHECK(v.capacity() == 50);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_clear) {
  Log("==> test vector clear()");
  stl::vector<int> v{1, 2, 3};
  BOOST_CHECK(v.size() == 3);
  BOOST_CHECK(v.capacity() == 5);
  v.clear();
  BOOST_CHECK(v.empty() == true);
  BOOST_CHECK(v.capacity() == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_insert) {
  Log("==> test vector insert()");
  stl::vector<int> v1{1, 2, 3, 4};
  int a = 5;
  auto it = v1.end();
  v1.insert(it, std::move(a));
  BOOST_CHECK(v1.size() == 5);
  BOOST_CHECK(v1[4] == 5);
  v1.reserve(20);
  v1.insert(v1.begin(), 12, 7);
  BOOST_CHECK(v1.size() == 17);
  BOOST_CHECK(v1[0] == 7);
  BOOST_CHECK(v1[11] == 7);
  BOOST_CHECK(v1[12] == 1);
  stl::vector<int> v2{1, 2, 3, 4, 5};
  v2.reserve(10);
  std::initializer_list<int> ilist{1, 2, 3};
  v2.insert(v2.begin() += 2, ilist);
  BOOST_CHECK(v2.size() == 8);
  BOOST_CHECK(v2[2] == 1);
  BOOST_CHECK(v2[3] == 2);
  BOOST_CHECK(v2[4] == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_emplace) {
  Log("==> test vector emplace()");
  stl::vector<int> v{1, 2, 3};
  v.emplace(v.end(), 5);
  BOOST_CHECK(v.back() == 5);
  v.emplace(v.end(), 4);
  BOOST_CHECK(v.back() == 4);
  int a = 1;
  v.emplace(v.begin(), a);
  BOOST_CHECK(v.front() == a);
  v.emplace(v.begin(), std::move(a));
  BOOST_CHECK(v.front() == 1);
  BOOST_CHECK(v.size() == 7);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_erase) {
  Log("==> test vector erase()");
  stl::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BOOST_CHECK(c.size() == 10);
  c.erase(c.begin());
  BOOST_CHECK(c.size() == 9);
  BOOST_CHECK(c.front() == 1);
  c.erase(c.begin() + 2, c.begin() + 5);
  BOOST_CHECK(c.size() == 6);
  for (stl::vector<int>::iterator it = c.begin(); it != c.end();) {
    if (*it % 2 == 0) {
      it = c.erase(it);
    } else {
      ++it;
    }
  }
  BOOST_CHECK(c.size() == 3);
  BOOST_CHECK(c[0] == 1);
  BOOST_CHECK(c[1] == 7);
  BOOST_CHECK(c[2] == 9);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_push_back) {
  Log("==> test vector push_back()");
  stl::vector<std::string> letters;
  std::string a = "abc";
  letters.push_back(a);
  BOOST_CHECK(letters.size() == 1);
  BOOST_CHECK(letters.front() == "abc");
  std::string s{"def"};
  letters.push_back(std::move(s));
  BOOST_CHECK(letters.size() == 2);
  BOOST_CHECK(letters.back() == "def");
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_emplace_back) {
  Log("==> test vector emplace_back()");
  struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    Point(Point &&other) noexcept : x(other.x), y(other.y) {}
    Point &operator=(const Point &other) = default;
  };
  stl::vector<Point> v;
  for (size_t i = 0; i < 5; i++) {
    v.emplace_back(i, i);
  }
  BOOST_CHECK(v.size() == 5);
  int i = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    BOOST_CHECK(it->x == i);
    BOOST_CHECK(it->y == i);
    i++;
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_pop_back) {
  Log("==> test vector pop_back()");
  stl::vector<int> v{3, 2, 1};
  BOOST_CHECK(v.size() == 3);
  BOOST_CHECK(v.back() == 1);
  v.pop_back();
  BOOST_CHECK(v.size() == 2);
  BOOST_CHECK(v.back() == 2);
  v.pop_back();
  BOOST_CHECK(v.size() == 1);
  BOOST_CHECK(v.back() == 3);
  v.pop_back();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_resize) {
  Log("==> test vector resize()");
  stl::vector<int> v = {1, 2, 3};
  v.resize(5);
  BOOST_CHECK(v.size() == 5);
  BOOST_CHECK(v.back() == 0);
  v.resize(2);
  BOOST_CHECK(v.size() == 2);
  BOOST_CHECK(v.back() == 2);
  v.resize(6, 4);
  BOOST_CHECK(v.size() == 6);
  BOOST_CHECK(v[2] == 4);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_swap) {
  Log("==> test vector swap()");
  stl::vector<int> a1{1, 2, 3}, a2{4, 5};
  auto it1 = a1.begin() + 1;
  auto it2 = a2.begin() + 1;
  int &ref1 = a1.front();
  int &ref2 = a2.front();
  BOOST_CHECK(*it1 == 2);
  BOOST_CHECK(*it2 == 5);
  BOOST_CHECK(ref1 == 1);
  BOOST_CHECK(ref2 == 4);
  a1.swap(a2);
  BOOST_CHECK(*it1 == 2);
  BOOST_CHECK(*it2 == 5);
  BOOST_CHECK(ref1 == 1);
  BOOST_CHECK(ref2 == 4);
  stl::swap(a1, a2);
  BOOST_CHECK(*it1 == 2);
  BOOST_CHECK(*it2 == 5);
  BOOST_CHECK(ref1 == 1);
  BOOST_CHECK(ref2 == 4);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_operator_equal_equal) {
  Log("==> test operator ==");
  stl::vector<int> alice{1, 2, 3};
  stl::vector<int> bob{7, 8, 9, 10};
  stl::vector<int> eve{1, 2, 3};
  BOOST_CHECK(!(alice == bob));
  BOOST_CHECK(alice == eve);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_erase_if) {
  Log("==> test erase_if()");
  stl::vector<char> cnt;
  for (char i = '0'; i <= '9'; i++) {
    cnt.push_back(i);
  }
  BOOST_CHECK(cnt.size() == 10);
  BOOST_CHECK(cnt.back() == '9');
  stl::erase(cnt, '3');
  BOOST_CHECK(cnt.size() == 9);
  BOOST_CHECK(cnt[3] == '4');
  auto erased = stl::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
  BOOST_CHECK(erased == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(vector_print) {
  class Point3d {
  public:
    double x;
    double y;
    double z;
    Point3d() = default;
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3d(Point3d &&other) noexcept : x(other.x), y(other.y), z(other.z) {}
    Point3d &operator=(const Point3d &other) = default;
  };
  stl::vector<Point3d> v;
  for (int i = 0; i < 5; i++) {
    double rand = 0.05 * i;
    v.emplace_back(i * rand, (i + 1) * rand, (i + 2) * rand);
  }
  auto lambda = [](const Point3d &p) {
    printf("(%g, %g, %g)\n", p.x, p.y, p.z);
  };
  v.for_each(v.begin(), v.end(), lambda);
  v.for_each(v.cbegin(), v.cend(), lambda);
  v.for_each(v.rbegin(), v.rend(), lambda);
  v.for_each(v.crbegin(), v.crend(), lambda);
  v.print([](const Point3d &p) {
    printf("(%.4g, %.4g, %.4g)", p.x, p.y, p.z);
  });
  Log("==> pass!");
}
