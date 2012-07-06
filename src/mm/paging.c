// Paging routines.

#include "types.h"
#include "paging.h"
#include "console.h"

extern ubyte *print_buffer;

void page_fault_handler(registers_t regs)
{
  udword fault_addr;
  asm volatile("mov %%cr2, %0" : "=r" (fault_addr));
  vsprintf(print_buffer, "Page fault occurred.\nFaulting address: %08x\n", fault_addr);
  console_putstr(DFL_ATTRIB, print_buffer);

  dump_registers(regs);
  for(;;);
}

void init_paging()
{
  register_interrupt_handler(14, &page_fault_handler);
}
