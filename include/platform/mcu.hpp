#ifndef CAMERA_CONTROL_PLATFORM_MCU_HPP
#define CAMERA_CONTROL_PLATFORM_MCU_HPP

#define PLATFORM_MCU_INCLUDED

#ifdef __AVR_ATmega32U4__
#include "platform/mcu/atmega32u4.hpp"
#else
#error "Unknown MCU"
#endif

#undef PLATFORM_MCU_INCLUDED

#endif