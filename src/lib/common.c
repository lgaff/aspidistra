// Common routines for kernel business go here.
#include "types.h"
#include "common.h"
#include "console.h"

extern ubyte *print_buffer;

void memset(ubyte *ptr, ubyte value, udword count)
{
  ubyte *tmp = (ubyte *)ptr;
  for( ; count != 0; count--)
    *tmp++ = value;
}

/* this is *NOT* leak-safe. Doing memory allocations this way pretty much guarantees the memory cannot be free'd */
udword kmalloc(udword sz)
{
  udword tmp = placement_address;
  placement_address += sz;
  return tmp;
}

void dump_registers(registers_t regs)
{
  vsprintf(print_buffer, "\neax: %08x\tebx: %08x\tecx: %08x\tedx: %08x\n", regs.eax, regs.ebx, regs.ecx, regs.edx);
  console_putstr(DFL_ATTRIB, print_buffer);
  vsprintf(print_buffer, "edi: %08x\tesi: %08x\tebp: %08x\tesp: %08x\n", regs.edi, regs.esi, regs.ebp, regs.esp);
  console_putstr(DFL_ATTRIB, print_buffer);
  vsprintf(print_buffer, "eip: %08x\tds:  %08x\tss:  %08x\tcs:  %08x\n", regs.eip, regs.ds, regs.ss, regs.cs);
  console_putstr(DFL_ATTRIB, print_buffer);
  for(;;);

  //vsprintf(print_buffer, "FLAGS: %032b\n", regs.eflags);
  //console_putstr(DFL_ATTRIB, print_buffer);

}
