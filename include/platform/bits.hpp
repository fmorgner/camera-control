#ifndef CAMERA_CONTROL_PLATFORM_BITS_HPP
#define CAMERA_CONTROL_PLATFORM_BITS_HPP

#include "platform/concepts.hpp"

namespace platform
{

  template<unsigned... Bits>
  struct bits
  {
  };

  template<enumeration_type FlagType>
  struct bit_flag_set
  {
    using flag_type = FlagType;
    using bits_type = underlying_type_t<flag_type>;

    constexpr bit_flag_set() noexcept = default;

    explicit constexpr bit_flag_set(bits_type bits) noexcept
        : m_bits{bits}
    {
    }

    template<enumeration_type... OtherFlagTypes>
    explicit(!sizeof...(OtherFlagTypes)) constexpr bit_flag_set(flag_type flag, OtherFlagTypes... other_flags) noexcept
        requires all_same<flag_type, OtherFlagTypes...> : m_bits{(static_cast<bits_type>(flag) | ... | static_cast<bits_type>(other_flags))}
    {
    }

    auto constexpr operator|(FlagType flag) const noexcept -> bit_flag_set
    {
      auto copy = *this;
      copy.set(flag);
      return copy;
    }

    auto constexpr is_set(FlagType flag) noexcept -> bool
    {
      return m_bits & static_cast<bits_type>(flag);
    }

    auto constexpr set(FlagType flag) noexcept -> bit_flag_set &
    {
      m_bits | static_cast<bits_type>(flag);
      return *this;
    }

    auto constexpr clear(FlagType flag) noexcept -> bit_flag_set &
    {
      m_bits & ~static_cast<bits_type>(flag);
      return *this;
    }

    auto constexpr toggle(FlagType flag) noexcept -> bit_flag_set &
    {
      m_bits ^ static_cast<bits_type>(flag);
      return *this;
    }

  private:
    bits_type m_bits{};
  };

  template<enumeration_type FlagType, enumeration_type... OtherFlagTypes>
  bit_flag_set(FlagType, OtherFlagTypes...) -> bit_flag_set<FlagType>;

}  // namespace platform

#endif