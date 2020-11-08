#include <platform/bits.hpp>
#include <platform/core.hpp>
#include <platform/interrupts.hpp>
#include <platform/mcu.hpp>

auto constexpr timeout = static_cast<uint16_t>(-1) - platform::s_to_timer_ticks<16'000'000, platform::timer_clock::divide_clock_by_1024>(1.0);

int main()
{
  platform::port_c.ddr.set(platform::bits<7>{});

  platform::timer1.interrupt_mask.set(platform::bits<0>{});
  platform::timer1.control_register<'A'>.write<0>();
  platform::timer1.control_register<'B'>.set(platform::bits<0, 2>{});
  platform::timer1.counter_register.write<timeout>();

  platform::enable_interrupts();

  if (platform::status_register.is_set<platform::status_flag::interrupt_enable>())
  {
    platform::port_c.port.set(platform::bits<7>{});
  }

  while (true)
  {
  }
}

// Timer/Counter 1 Overflow
extern "C" [[gnu::signal, gnu::used]] auto __vector_20() -> void
{
  // platform::port_c.toggle<7>();
  platform::timer1.counter_register.write<timeout>();
}
