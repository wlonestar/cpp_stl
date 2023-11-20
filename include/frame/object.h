#ifndef CPP_STL_OBJECT_H
#define CPP_STL_OBJECT_H

#pragma once

#include <string>
#include <typeinfo>

namespace stl {

class Object {
public:
  virtual std::string type_name() const { return typeid(*this).name(); }
};

}// namespace stl

#endif
