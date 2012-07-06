// Common system functions declared here.
#ifndef COMMON_H
#define COMMON_H

extern udword *kspace_end;

udword placement_address = (udword)&kspace_end;

void memset(ubyte *ptr, ubyte value, udword count);

udword kmalloc(udword sz);

void dump_registers(registers_t regs);

#endif  
