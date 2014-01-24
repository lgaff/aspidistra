#include "types.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "console.h"
#include "multiboot.h"
#include "cpu.h"
#include "stdio.h"
#include "liz.h"

extern void magical_break();
extern ubyte *print_buffer;
extern udword *heap_start;

ubyte dummy_func(ubyte xx)
{
  xx += 1;
  return xx;
}
ubyte *txt_buf_wrong = (ubyte *)0xDEADBEEF;
void _main(multiboot_info_t *mbd, unsigned int magic)
{
  uword offset = 0;
  udword end_addr = 0;
  udword total_available_pmem;
  udword total_reserved_pmem;
  ubyte *vendor_string = "            ";

  ubyte c;

  console_clear();
  console_putstr(DFL_ATTRIB, "aspidistra: A feeble attempt at an operating system\n");

  init_tables();
  init_paging();
  init_keyboard();
  
  vsprintf(print_buffer, "multiboot flags are: %08x\n", mbd->flags);
  console_putstr(DFL_ATTRIB, print_buffer);
  show_memory_map(mbd);
  vsprintf(print_buffer, "CPU: %s\n", cpuid_string(0, vendor_string));
  console_putstr(DFL_ATTRIB, print_buffer);
  construct_mmap(mbd);

  console_putstr(DFL_ATTRIB, "Entering a loop!");
  for(;;) {}
}
