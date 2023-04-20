//
// Created by wjl on 2023/4/14.
//

#ifndef CPP_STL_UTIL_H
#define CPP_STL_UTIL_H

namespace stl {

#define TODO() \
  printf("Not implemented!"); \
  exit(-1)

#define Log(format, ...) printf(format "\n", ##__VA_ARGS__)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

}

#endif//CPP_STL_UTIL_H
