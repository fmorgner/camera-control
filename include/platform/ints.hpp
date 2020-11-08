#ifndef CAMERA_CONTROL_PLATFORM_INTS_HPP
#define CAMERA_CONTROL_PLATFORM_INTS_HPP

#include <stdint.h>

namespace platform
{

  namespace detail
  {

    template<unsigned Size>
    struct signed_int;

    template<>
    struct signed_int<8>
    {
      using type = int8_t;
    };

    template<>
    struct signed_int<16>
    {
      using type = int16_t;
    };

    template<>
    struct signed_int<32>
    {
      using type = int32_t;
    };

    template<>
    struct signed_int<64>
    {
      using type = int64_t;
    };

    template<unsigned Size>
    struct unsigned_int;

    template<>
    struct unsigned_int<8>
    {
      using type = uint8_t;
    };

    template<>
    struct unsigned_int<16>
    {
      using type = uint16_t;
    };

    template<>
    struct unsigned_int<32>
    {
      using type = uint32_t;
    };

    template<>
    struct unsigned_int<64>
    {
      using type = uint64_t;
    };

    auto constexpr round_to_suitable_size(unsigned size) -> int
    {
      return (size <= 8) ? 8 : (size <= 16) ? 16 : (size <= 32) ? 32 : (size <= 64) ? 64 : size;
    };

  }  // namespace detail

  template<int Size>
  using int_t = typename detail::signed_int<detail::round_to_suitable_size(Size)>::type;

  template<int Size>
  using uint_t = typename detail::unsigned_int<detail::round_to_suitable_size(Size)>::type;

}  // namespace platform

#endif