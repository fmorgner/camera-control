#ifndef CAMERA_CONTROL_PLATFORM_ALGORITHM_HPP
#define CAMERA_CONTROL_PLATFORM_ALGORITHM_HPP

namespace platform
{

  template<typename InputIterator, typename ValueType>
  auto constexpr find(InputIterator first, InputIterator last, ValueType const & value) -> InputIterator
  {
    for (; first != last; ++first)
    {
      if (*first == value)
      {
        return first;
      }
    }
    return last;
  }

}  // namespace platform

#endif