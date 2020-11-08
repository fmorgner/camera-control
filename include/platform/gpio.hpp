#ifndef CAMERA_CONTROL_PLATFORM_GPIO_HPP
#define CAMERA_CONTROL_PLATFORM_GPIO_HPP

#include "platform/ints.hpp"
#include "platform/special_function_register.hpp"

#include <stdint.h>

namespace platform
{

  template<uintptr_t Base, uint_t<8> BitMask>
  struct gpio_port
  {
    auto constexpr static port = special_function_register<Base - 0, 8, BitMask>{};
    auto constexpr static ddr = special_function_register<Base - 1, 8, BitMask>{};
    auto constexpr static pin = special_function_register<Base - 2, 8, BitMask>{};

    template<unsigned... Pins>
    auto static toggle() noexcept -> void
    {
      pin.template write<(0 | ... | (1 << Pins))>();
    }

  private:
  };

}  // namespace platform

#endif