//
// Created by wjl on 2023/4/13.
//

#include "vector.h"
#include <gtest/gtest.h>

TEST(test_vector, test_vector_init) {
  Log("==> test vector constructor");
  stl::vector<int> v1;
  EXPECT_EQ(v1.empty(), true);
  stl::vector<int> v2(5, 1);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2[0], 1);
  stl::vector<int> v3(5);
  EXPECT_EQ(v3.size(), 5);
  EXPECT_EQ(v3[0], 0);
  stl::vector<int> v4(v2);
  EXPECT_EQ(v4.size(), 5);
  EXPECT_EQ(v4[0], 1);
  stl::vector<int> v5(v3);
  EXPECT_EQ(v5.size(), 5);
  EXPECT_EQ(v5[0], 0);
  std::initializer_list<int> ilist{1, 2, 3, 4, 5, 6, 7};
  stl::vector<int> v6(ilist);
  EXPECT_EQ(v6.size(), 7);
  Log("==> pass!");
}

TEST(test_vector, test_vector_operator_equal) {
  Log("==> test vector operator =");
  stl::vector<int> v1(5, 1);
  stl::vector<int> v2 = v1;
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2[0], 1);
  stl::vector<int> v3 = {4, 5, 6, 7};
  EXPECT_EQ(v3.size(), 4);
  EXPECT_EQ(v3[0], 4);
  Log("==> pass!");
}

TEST(test_vector, test_vector_assign) {
  Log("==> test vector assign()");
  stl::vector<int> v1(5, 1);
  EXPECT_EQ(v1.size(), 5);
  EXPECT_EQ(v1[0], 1);
  v1.assign(6, 2);
  EXPECT_EQ(v1.size(), 6);
  EXPECT_EQ(v1[0], 2);
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8});
  EXPECT_EQ(v1.size(), 8);
  EXPECT_EQ(v1[7], 8);
  Log("==> pass!");
}

TEST(test_vector, test_vector_at) {
  Log("==> test vector at()");
  stl::vector<int> v1{1, 2, 3, 4, 5};
  v1.at(0) = 3;
  int const &a = v1.at(0);
  EXPECT_EQ(v1.at(0), a);
  EXPECT_EQ(v1.at(3), 4);
  EXPECT_EQ(v1.at(4), 5);
  Log("==> pass!");
}

TEST(test_vector, test_vector_operator_pos) {
  Log("==> test vector operator []");
  stl::vector<int> numbers{2, 4, 6, 8};
  EXPECT_EQ(numbers[1], 4);
  numbers[0] = 5;
  EXPECT_EQ(numbers[0], 5);
  Log("==> pass!");
}

TEST(test_vector, test_vector_front) {
  Log("==> test vector front()");
  stl::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
  Log("==> pass!");
}

TEST(test_vector, test_vector_back) {
  Log("==> test vector back()");
  stl::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  EXPECT_EQ(v.back(), 11);
  Log("==> pass!");
}

TEST(test_vector, test_vector_data) {
  Log("==> test vector data()");
  stl::vector<int> container{1, 2, 3, 4};
  for (std::size_t i = 0; i < 4; i++) {
    EXPECT_EQ(container.data()[i], i + 1);
  }
  Log("==> pass!");
}

TEST(test_vector, test_vector_iterator) {
  Log("==> test vector iterator");
  stl::vector<int> nums{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(*nums.begin(), 1);
  int i = 1;
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  i = 1;
  for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  i = 6;
  for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
    EXPECT_EQ(*it, i--);
  }
  i = 6;
  for (auto it = nums.crbegin(); it != nums.crend(); ++it) {
    EXPECT_EQ(*it, i--);
  }
  i = 1;
  for (auto &it: nums) {
    EXPECT_EQ(it, i++);
  }
  Log("==> pass!");
}

TEST(test_vector, test_vector_empty) {
  Log("==> test vector empty()");
  stl::vector<int> v;
  EXPECT_EQ(v.empty(), true);
  v = {1, 2, 3, 4};
  EXPECT_EQ(v.empty(), false);
  EXPECT_EQ(v.size(), 4);
  Log("==> pass!");
}

TEST(test_vector, test_vector_reserve) {
  Log("==> test vector reserve()");
  stl::vector<int> v{1, 2, 3, 4};
  v.reserve(4);
  EXPECT_EQ(v.capacity(), 4);
  v.reserve(5);
  EXPECT_EQ(v.capacity(), 5);
  Log("==> pass!");
}

TEST(test_vector, test_vector_capacity) {
  Log("==> test vector capacity()");
  stl::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.capacity(), 5);
  v = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(v.capacity(), 12);
  Log("==> pass!");
}

TEST(test_vector, test_vector_shrink_to_fit) {
  Log("==> test vector shrink_to_fit()");
  stl::vector<int> v{1, 2, 3, 4, 5, 6, 7};
  v.reserve(100);
  EXPECT_EQ(v.capacity(), 100);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 50);
  Log("==> pass!");
}

TEST(test_vector, test_vector_clear) {
  Log("==> test vector clear()");
  stl::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 5);
  v.clear();
  EXPECT_EQ(v.empty(), true);
  EXPECT_EQ(v.capacity(), 5);
  Log("==> pass!");
}

TEST(test_vector, test_vector_insert) {
  Log("==> test vector insert()");
  stl::vector<int> v1{1, 2, 3, 4};
  int a = 5;
  auto it = v1.end();
  v1.insert(it, std::move(a));
  EXPECT_EQ(v1.size(), 5);
  EXPECT_EQ(v1[4], 5);
  v1.reserve(20);
  v1.insert(v1.begin(), 12, 7);
  EXPECT_EQ(v1.size(), 17);
  EXPECT_EQ(v1[0], 7);
  EXPECT_EQ(v1[11], 7);
  EXPECT_EQ(v1[12], 1);
  stl::vector<int> v2{1, 2, 3, 4, 5};
  v2.reserve(10);
  std::initializer_list<int> ilist{1, 2, 3};
  v2.insert(v2.begin() += 2, ilist);
  EXPECT_EQ(v2.size(), 8);
  EXPECT_EQ(v2[2], 1);
  EXPECT_EQ(v2[3], 2);
  EXPECT_EQ(v2[4], 3);
  Log("==> pass!");
}

TEST(test_vector, test_vector_emplace) {
  Log("==> test vector emplace()");
  stl::vector<int> v{1, 2, 3};
  v.emplace(v.end(), 5);
  EXPECT_EQ(v.back(), 5);
  v.emplace(v.end(), 4);
  EXPECT_EQ(v.back(), 4);
  int a = 1;
  v.emplace(v.begin(), a);
  EXPECT_EQ(v.front(), a);
  v.emplace(v.begin(), std::move(a));
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.size(), 7);
  Log("==> pass!");
}

TEST(test_vector, test_vector_erase) {
  Log("==> test vector erase()");
  stl::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(c.size(), 10);
  c.erase(c.begin());
  EXPECT_EQ(c.size(), 9);
  EXPECT_EQ(c.front(), 1);
  c.erase(c.begin() + 2, c.begin() + 5);
  EXPECT_EQ(c.size(), 6);
  for (stl::vector<int>::iterator it = c.begin(); it != c.end();) {
    if (*it % 2 == 0) {
      it = c.erase(it);
    } else {
      ++it;
    }
  }
  EXPECT_EQ(c.size(), 3);
  EXPECT_EQ(c[0], 1);
  EXPECT_EQ(c[1], 7);
  EXPECT_EQ(c[2], 9);
  Log("==> pass!");
}

TEST(test_vector, test_vector_push_back) {
  Log("==> test vector push_back()");
  stl::vector<std::string> letters;
  std::string a = "abc";
  letters.push_back(a);
  EXPECT_EQ(letters.size(), 1);
  EXPECT_EQ(letters.front(), "abc");
  std::string s{"def"};
  letters.push_back(std::move(s));
  EXPECT_EQ(letters.size(), 2);
  EXPECT_EQ(letters.back(), "def");
  Log("==> pass!");
}

TEST(test_vector, test_vector_emplace_back) {
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
  EXPECT_EQ(v.size(), 5);
  int i = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(it->x, i);
    EXPECT_EQ(it->y, i);
    i++;
  }
  Log("==> pass!");
}

TEST(test_vector, test_vector_pop_back) {
  Log("==> test vector pop_back()");
  stl::vector<int> v{3, 2, 1};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.back(), 1);
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
  v.pop_back();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.back(), 3);
  v.pop_back();
  Log("==> pass!");
}

TEST(test_vector, test_vector_resize) {
  Log("==> test vector resize()");
  stl::vector<int> v = {1, 2, 3};
  v.resize(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.back(), 0);
  v.resize(2);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
  v.resize(6, 4);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[2], 4);
  Log("==> pass!");
}

TEST(test_vector, test_vector_swap) {
  Log("==> test vector swap()");
  stl::vector<int> a1{1, 2, 3}, a2{4, 5};
  auto it1 = a1.begin() + 1;
  auto it2 = a2.begin() + 1;
  int &ref1 = a1.front();
  int &ref2 = a2.front();
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(ref1, 1);
  EXPECT_EQ(ref2, 4);
  a1.swap(a2);
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(ref1, 1);
  EXPECT_EQ(ref2, 4);
  stl::swap(a1, a2);
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 5);
  EXPECT_EQ(ref1, 1);
  EXPECT_EQ(ref2, 4);
  Log("==> pass!");
}

TEST(test_vector, test_operator_equal_equal) {
  Log("==> test operator ==");
  stl::vector<int> alice{1, 2, 3};
  stl::vector<int> bob{7, 8, 9, 10};
  stl::vector<int> eve{1, 2, 3};
  EXPECT_NE(alice, bob);
  EXPECT_EQ(alice, eve);
  Log("==> pass!");
}

TEST(test_vector, test_erase_if) {
  Log("==> test erase_if()");
  stl::vector<char> cnt;
  for (char i = '0'; i <= '9'; i++) {
    cnt.push_back(i);
  }
  EXPECT_EQ(cnt.size(), 10);
  EXPECT_NE(cnt.back(), '9');
  stl::erase(cnt, '3');
  EXPECT_EQ(cnt.size(), 9);
  EXPECT_EQ(cnt[3], '4');
  auto erased = stl::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
  EXPECT_EQ(erased, 5);
  Log("==> pass!");
}

TEST(test_vector, test_vector_print) {
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
}
