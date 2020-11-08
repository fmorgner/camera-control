#ifndef CAMERA_CONTROL_PLATFORM_CONCEPTS_HPP
#define CAMERA_CONTROL_PLATFORM_CONCEPTS_HPP

#include "platform/type_traits.hpp"

namespace platform
{

  template<typename LType, typename RType>
  concept same_as = is_same_v<LType, RType> && is_same_v<RType, LType>;

  template<typename... Types>
  concept all_same = are_same_v<Types...>;

  template<typename Type>
  concept enumeration_type = is_enum_v<Type>;

  template<typename Type>
  concept integral = is_integral_v<Type>;

}  // namespace platform

#endif