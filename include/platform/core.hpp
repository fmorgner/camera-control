#ifndef CAMERA_CONTROL_PLATFORM_CORE_HPP
#define CAMERA_CONTROL_PLATFORM_CORE_HPP

#include "platform/algorithm.hpp"
#include "platform/array.hpp"
#include "platform/bits.hpp"
#include "platform/ints.hpp"
#include "platform/math.hpp"
#include "platform/special_function_register.hpp"
#include "platform/type_traits.hpp"

namespace platform
{

  enum struct status_flag : uint_t<8>{
      carry = 0b0000'0001,
      zero = 0b0000'0010,
      negative = 0b0000'0100,
      twos_complement_overflow = 0b0000'1000,
      sign = 0b0001'0000,
      half_carry = 0b0010'0000,
      bit_copy_storage = 0b0100'0000,
      interrupt_enable = 0b1000'0000,
  };

  namespace detail
  {
    auto constexpr is_valid_flag(status_flag flag) -> bool
    {
      auto constexpr enumerators = array{
          status_flag::carry,
          status_flag::zero,
          status_flag::negative,
          status_flag::twos_complement_overflow,
          status_flag::sign,
          status_flag::half_carry,
          status_flag::bit_copy_storage,
          status_flag::interrupt_enable,
      };
      return platform::find(enumerators.cbegin(), enumerators.cend(), flag) != enumerators.cend();
    }
  }  // namespace detail

  template<status_flag Flag>
  concept known_status_flag = requires
  {
    detail::is_valid_flag(Flag);
  };

  struct status_register_t
  {
    using flags_type = bit_flag_set<status_flag>;

    template<status_flag Flag>
    auto is_set() const noexcept -> bool requires known_status_flag<Flag>
    {
      return read().is_set(Flag);
    }

    template<status_flag Flag>
    auto set() noexcept -> void requires known_status_flag<Flag>
    {
      switch (Flag)
      {
      case status_flag::carry:
        asm("sec");
        break;
      case status_flag::zero:
        asm("sez");
        break;
      case status_flag::negative:
        asm("sen");
        break;
      case status_flag::twos_complement_overflow:
        asm("sev");
        break;
      case status_flag::sign:
        asm("ses");
        break;
      case status_flag::half_carry:
        asm("seh");
        break;
      case status_flag::bit_copy_storage:
        asm("set");
        break;
      case status_flag::interrupt_enable:
        asm("sei");
        break;
      }
    }

    template<status_flag Flag>
    auto clear() noexcept -> void requires known_status_flag<Flag>
    {
      switch (Flag)
      {
      case status_flag::carry:
        asm("clc");
        break;
      case status_flag::zero:
        asm("clz");
        break;
      case status_flag::negative:
        asm("cln");
        break;
      case status_flag::twos_complement_overflow:
        asm("clv");
        break;
      case status_flag::sign:
        asm("cls");
        break;
      case status_flag::half_carry:
        asm("clh");
        break;
      case status_flag::bit_copy_storage:
        asm("clt");
        break;
      case status_flag::interrupt_enable:
        asm("cli");
        break;
      }
    }

  private:
    auto static read() noexcept -> flags_type
    {
      return flags_type{sreg.read()};
    }

    auto constexpr static sreg = special_function_register<0x3f, 8, 0b1111'1111>{};
  } constinit status_register{};

  auto constexpr operator|(status_flag lhs, status_flag rhs) -> status_register_t::flags_type
  {
    return status_register_t::flags_type{lhs, rhs};
  }

}  // namespace platform

#endif