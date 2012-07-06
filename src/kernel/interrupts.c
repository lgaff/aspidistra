#include "types.h"
#include "console.h"
#include "interrupts.h"
#include "vga.h"

isr_t interrupt_handlers[256];

static ubyte *interrupt_types[19] =
  {
    "Division by zero",
    "Debug exception",
    "Non-maskable interrupt",
    "Breakpoint encountered",
    "Overflow detected",
    "Out of bounds",
    "Invalid opcode",
    "Coprocessor not present",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check exception",
    "Machine check exception"
  };

void isr_handler(registers_t regs)
{
  // Dummy interrupt handler just dumps a status message to the screen
  ubyte attribute = ATTRIB(VGA_BLK, VGA_WHI);
  if(interrupt_handlers[regs.interrupt_number] != 0)
    {
      isr_t handler = interrupt_handlers[regs.interrupt_number];
      handler(regs);
    }
  else
    {
      console_putstr(attribute, "Interrupt encountered: ");
      if (regs.interrupt_number >= 19)
	{
	  console_putstr(attribute, "System reserved interrupt ");
	}
      else
	{
	  console_putstr(attribute, interrupt_types[regs.interrupt_number]);
	}
      console_putstr(attribute, "(");
      console_putint(attribute, regs.interrupt_number);
      console_putstr(attribute, ")\n");
      console_putstr(attribute, "Error code supplied: ");
      console_putint(attribute, regs.error_code);
      console_putchar(attribute, '\n');
    }
}

void irq_handler(registers_t regs)
{
  // Send an end of interrupt signal to the PIC. 
  if(regs.interrupt_number >= 40) // need to signal the slave as well.
    {
      outb(0xA0, 0x20);
    }

  outb(0x20, 0x20); // Either way, we need to signal the master.
  if (interrupt_handlers[regs.interrupt_number] != 0)
    {
      isr_t handler = interrupt_handlers[regs.interrupt_number];
      handler(regs);
    }
}

void register_interrupt_handler(ubyte index, isr_t handler)
{
  interrupt_handlers[index] = handler;
}
