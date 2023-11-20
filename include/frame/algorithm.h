#ifndef CPP_STL_ALGORITHM_H
#define CPP_STL_ALGORITHM_H

#pragma once

#include "object.h"

namespace stl {

template<typename OutputType, typename... InputTypes>
class Algorithm;

template<typename OutputType, typename... InputTypes>
class Algorithm<OutputType(InputTypes...)> : public Object {
public:
  using Output = OutputType;
  virtual OutputType operator()(InputTypes... inputs) = 0;
};

}// namespace stl

#endif
