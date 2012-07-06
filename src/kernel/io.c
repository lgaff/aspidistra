#include "types.h"
#include "io.h"

void outb(uword port, ubyte val)
{
  asm volatile("outb %1, %0" 
	       :
	       : "dN" (port), "a" (val));
}

void outw(uword port, uword val)
{
  asm volatile("outw %1, %0" 
	       :
	       : "dN" (port), "a" (val));
}

ubyte inb(uword port)
{
  ubyte ret;
  asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

uword inw(uword port)
{
  uword ret;
  asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

