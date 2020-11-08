#ifndef CAMERA_CONTROL_PLATFORM_SPECIAL_FUNCTION_REGISTER_HPP
#define CAMERA_CONTROL_PLATFORM_SPECIAL_FUNCTION_REGISTER_HPP

#include "platform/bits.hpp"
#include "platform/ints.hpp"

#include <stdint.h>

namespace platform
{

  template<uintptr_t Address, unsigned Width, uint_t<Width> ValidMask, uint_t<Width> ReadMask = ValidMask, uint_t<Width> WriteMask = ValidMask>
  struct special_function_register
  {
    using backing_type = uint_t<Width>;
    using pointer_type = backing_type volatile *;

    template<unsigned... Bits>
    bool constexpr static Writable = (WriteMask & ((0 | ... | (uint_t<Width>{1} << Bits)))) == (0 | ... | (uint_t<Width>{1} << Bits));

    template<unsigned... Bits>
    bool constexpr static Readable = (ReadMask & ((0 | ... | (uint_t<Width>{1} << Bits)))) == (0 | ... | (uint_t<Width>{1} << Bits));

    template<backing_type Value>
    bool constexpr static ValueMaskCompatible = ((Value & WriteMask) == Value);

    auto static read() noexcept -> backing_type
    {
      return *pointer();
    }

    template<backing_type Value>
    auto static write() noexcept -> void requires ValueMaskCompatible<Value>
    {
      write_impl(Value);
    }

    auto static write_unchecked(backing_type value) noexcept -> void
    {
      write_impl(value);
    }

    template<unsigned... Bits>
    auto static set(bits<Bits...>) noexcept -> void requires Readable<Bits...> && Writable<Bits...>
    {
      auto constexpr bits_to_set = (uint_t<Width>{0} | ... | (uint_t<Width>{1} << Bits));
      write_impl(read() | bits_to_set);
    }

    template<unsigned... Bits>
    auto static clear(bits<Bits...>) noexcept -> void requires Readable<Bits...> && Writable<Bits...>
    {
      auto constexpr bits_to_clear = (uint_t<Width>{0} | ... | (uint_t<Width>{1} << Bits));
      write_impl(read() & ~(bits_to_clear));
    }

    template<unsigned Bit>
    auto static toggle_bit() noexcept -> void requires Readable<Bit> && Writable<Bit>
    {
      write_impl(read() ^ (1u << Bit));
    }

  private:
    auto static constexpr base_offset = Address <= 0x3F ? 0x20 : 0;

    auto static pointer() noexcept -> pointer_type
    {
      return reinterpret_cast<pointer_type>(Address + base_offset);
    }

    auto static write_impl(backing_type value) noexcept -> void
    {
      *pointer() = value;
    }
  };

}  // namespace platform

#endif