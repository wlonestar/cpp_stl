#ifndef CPP_STL_DATASTRUCTURE_H
#define CPP_STL_DATASTRUCTURE_H

#pragma once

#include "object.h"

namespace stl {

template<typename T>
class DataStructure : public Object {
public:
  virtual size_t size() const = 0;
  virtual bool empty() const { return size() == 0; }
};

}// namespace stl

#endif
