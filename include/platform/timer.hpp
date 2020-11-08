#ifndef CAMERA_CONTROL_PLATFORM_TIMER_HPP
#define CAMERA_CONTROL_PLATFORM_TIMER_HPP

#include "platform/ints.hpp"
#include "platform/special_function_register.hpp"
#include "platform/type_traits.hpp"

#include <stdint.h>

namespace platform
{

  /**
   * Base template for all timers
   *
   * @tparam CounterBase The base address of the counter register
   * @tparam CounterWidth The bit-width of the counter register
   * @tparam InterruptMaskBase The base address of the counter interrupt mask
   * @tparam InterruptMaskWidth The bit-width of the counter interrupt mask
   * @tparam InterruptMaskMask The valid bits in the counter interrupt mask
   */
  template<uintptr_t CounterBase,
           uint_t<8> CounterWidth,
           uintptr_t InterruptMaskBase,
           uint_t<8> InterruptMaskWidth,
           uint_t<InterruptMaskWidth> InterruptMaskMask>
  struct timer
  {
    auto constexpr static interrupt_mask = special_function_register<InterruptMaskBase, InterruptMaskWidth, InterruptMaskMask>{};
    auto constexpr static counter_register =
        special_function_register<CounterBase, CounterWidth, (uint_t<CounterWidth * 2>{1} << CounterWidth) - 1>{};

    template<char ID, uintptr_t Base, uint_t<8> ValidMask>
    using control_register_type = special_function_register<Base, 8, ValidMask>;

    template<char ID>
    auto constexpr static control_register{typename enable_if<ID == ' '>::type{}};
  };

  enum struct timer_clock
  {
    none,
    no_prescaling = 0b001,
    divide_clock_by_8 = 0b010,
    divide_clock_by_64 = 0b011,
    divide_clock_by_256 = 0b100,
    divide_clock_by_1024 = 0b101,
    external_clock_falling_edge = 0b110,
    external_clock_rising_edge = 0b111,
  };

  template<uint32_t Frequency, timer_clock ClockConfig>
  auto constexpr s_to_timer_ticks(double s) -> uint16_t
  {
    auto constexpr config = static_cast<uint8_t>(ClockConfig);
    static_assert(config >= 1 && config <= 5);

    auto constexpr prescaler = [] {
      switch (ClockConfig)
      {
      case timer_clock::no_prescaling:
        return 1;
      case timer_clock::divide_clock_by_8:
        return 8;
      case timer_clock::divide_clock_by_64:
        return 64;
      case timer_clock::divide_clock_by_256:
        return 256;
      case timer_clock::divide_clock_by_1024:
        return 1024;
      }
    }();

    auto constexpr timer_frequency = Frequency / prescaler;
    auto constexpr seconds_per_tick = 1.0 / timer_frequency;
    return static_cast<uint16_t>(s / seconds_per_tick);
  }
}  // namespace platform

#endif