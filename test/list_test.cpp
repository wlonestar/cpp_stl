//
// Created by wjl on 2023/4/17.
//

#include "list.h"
#include <list>
#include <vector>
#include <iostream>

void test_std_list() {
  std::list<int> l;
  l.push_back(1);
  auto it1 = l.begin();
  auto it2 = l.end();
  auto it3 = it1;
  auto it4 = it2;
  it3--;
  it4++;
  printf("%p\n%p\n%p\n%p\n", &it1, &it2, &it3, &it4);
}

int main() {
  test_std_list();
  return 0;
}
