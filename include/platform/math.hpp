#ifndef CAMERA_CONTROL_PLATFORM_MATH_HPP
#define CAMERA_CONTROL_PLATFORM_MATH_HPP

#include "platform/concepts.hpp"

namespace platform
{

  template<integral ValueType>
  auto constexpr log2(ValueType value) noexcept -> ValueType
  {
    return (value < 2) ? 1 : 1 + log2(value / 2);
  }

}  // namespace platform

#endif