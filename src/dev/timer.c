#include "timer.h"
#include "interrupts.h"
#include "console.h"


udword tick = 0;

static void timer_callback(registers_t regs)
{
  tick++;
}

void init_timer(udword frequency)
{
  console_putstr(DFL_ATTRIB, "Registering timer interrupt\n");
  register_interrupt_handler(IRQ0, &timer_callback);
  udword divisor = 1193180 / frequency;

  ubyte low = (ubyte)(divisor & 0xFF);
  ubyte high = (ubyte)((divisor >> 8) & 0xFF);

  outb(0x43, 0x36); // command byte to get the timer's attention

  // Now that the PIT is listening, we send the frequency divisor one byte at a time.
  outb(0x40, low);
  outb(0x40, high);
}

  
