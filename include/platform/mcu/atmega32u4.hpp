#ifndef CAMERA_CONTROL_PLATFORM_MCU_ATMEGA32U4_HPP
#define CAMERA_CONTROL_PLATFORM_MCU_ATMEGA32U4_HPP

#include "platform/gpio.hpp"
#include "platform/timer.hpp"

#if !defined(PLATFORM_MCU_INCLUDED) && !defined(PLATFORM_DISABLE_MCU_INCLUDE_ERROR)
#error "Don't include this file directly"
#endif

namespace platform
{
  /* Timers/Counters */

  /**
   * Timer/Counter 0 -- 8-bit
   */

  struct timer0_t : timer<0x26, 8, 0x6e, 8, 0b0000'0111>
  {
    using super = timer<0x26, 8, 0x6e, 8, 0b0000'0111>;
    using super::control_register;
  } constinit timer0{};

  template<>
  auto constexpr timer0_t::control_register<'A'> = timer0_t::control_register_type<'A', 0x24, 0b1111'0011>{};

  template<>
  auto constexpr timer0_t::control_register<'B'> = timer0_t::control_register_type<'B', 0x25, 0b1100'1111>{};

  /**
   * Timer/Counter 1 -- 16-bit
   */
  struct timer1_t : timer<0x84, 16, 0x6f, 8, 0b0010'1111>
  {
    using super = timer<0x84, 16, 0x6f, 8, 0b0010'1111>;
    using super::control_register;
  } constinit timer1{};

  template<>
  auto constexpr timer1_t::control_register<'A'> = timer1_t::control_register_type<'A', 0x80, 0b1111'1111>{};

  template<>
  auto constexpr timer1_t::control_register<'B'> = timer1_t::control_register_type<'B', 0x81, 0b1101'1111>{};

  template<>
  auto constexpr timer1_t::control_register<'C'> = timer1_t::control_register_type<'C', 0x82, 0b1110'0000>{};

  /**
   * Timer/Counter 3 -- 16-bit
   */
  struct timer3_t : timer<0x94, 16, 0x71, 8, 0b0010'1111>
  {
    using super = timer<0x94, 16, 0x71, 8, 0b0010'1111>;
    using super::control_register;
  } constinit timer3{};

  template<>
  auto constexpr timer3_t::control_register<'A'> = timer3_t::control_register_type<'A', 0x90, 0b1111'1111>{};

  template<>
  auto constexpr timer3_t::control_register<'B'> = timer3_t::control_register_type<'B', 0x91, 0b1101'1111>{};

  template<>
  auto constexpr timer3_t::control_register<'C'> = timer3_t::control_register_type<'C', 0x92, 0b1000'0000>{};

  /**
   * Timer/Counter 4 -- 10-bit
   */
  struct timer4_t : timer<0xbe, 10, 0x72, 8, 0b1110'0100>
  {
    using super = timer<0xbe, 10, 0x72, 8, 0b1110'0100>;
    using super::control_register;
  } constinit timer4{};

  template<>
  auto constexpr timer4_t::control_register<'A'> = timer4_t::control_register_type<'A', 0xc0, 0b1111'1111>{};

  template<>
  auto constexpr timer4_t::control_register<'B'> = timer4_t::control_register_type<'B', 0xc1, 0b1111'1111>{};

  template<>
  auto constexpr timer4_t::control_register<'C'> = timer4_t::control_register_type<'C', 0xc2, 0b1111'1111>{};

  template<>
  auto constexpr timer4_t::control_register<'D'> = timer4_t::control_register_type<'D', 0xc2, 0b1111'1111>{};

  template<>
  auto constexpr timer4_t::control_register<'E'> = timer4_t::control_register_type<'E', 0xc2, 0b1111'1111>{};

  /* GPIO Ports */

  auto constexpr port_b = gpio_port<0x05, 0b1111'1111>{};
  auto constexpr port_c = gpio_port<0x08, 0b1100'0000>{};
  auto constexpr port_d = gpio_port<0x0b, 0b1111'1111>{};
  auto constexpr port_e = gpio_port<0x0e, 0b0100'0100>{};
  auto constexpr port_f = gpio_port<0x11, 0b1111'0011>{};

}  // namespace platform

#endif