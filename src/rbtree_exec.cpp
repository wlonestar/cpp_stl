#include <cassert>
#include <iostream>
#include <rbtree.h>

// ./rbtree_exec <n> <a[0]> <a[1]> ... <a[n-1]>
int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(EXIT_FAILURE);
  }
  int n = strtol(argv[1], nullptr, 10);
  if (argc != n + 2) {
    exit(EXIT_FAILURE);
  }
  int a[n];
  for (int i = 0; i < n; i++) {
    a[i] = strtol(argv[i + 2], nullptr, 10);
  }
  stl::rbtree<int> t;
  for (int i = 0; i < n; i++) {
    t.insert(a[i]);
    t.print();
  }
  t.print();
  return 0;
}
