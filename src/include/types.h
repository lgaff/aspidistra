// types.h declares system data type defintions
#ifndef TYPES_H
#define TYPES_H

typedef unsigned char ubyte;
typedef          char sbyte;
typedef unsigned short uword;
typedef          short sword; // haha
typedef unsigned int  udword;
typedef          int  sdword;
typedef unsigned long uqword;
typedef          long sqword;

typedef struct registers
{
  udword ds;
  udword edi, esi, ebp, esp, ebx, edx, ecx, eax;
  udword interrupt_number, error_code;
  udword eip, cs, eflags, useresp, ss;
} registers_t;

typedef struct mboot_memory_map 
{
  udword size;
  udword base_low, base_high;
  udword length_low, length_high;
  udword type;
} multiboot_mmap_t;

#endif
