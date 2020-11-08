#ifndef CAMERA_CONTROL_PLATFORM_INTERRUPTS_HPP
#define CAMERA_CONTROL_PLATFORM_INTERRUPTS_HPP

#include "platform/core.hpp"

namespace platform
{

  auto inline enable_interrupts() -> void
  {
    asm("sei");
  }

  auto inline disable_interrupts() -> void
  {
    asm("cli");
  }

  struct interrupt_lock
  {
    interrupt_lock()
    {
      disable_interrupts();
    }
  };

}  // namespace platform

#endif