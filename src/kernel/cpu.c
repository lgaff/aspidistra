#include "types.h"
#include "cpu.h"


inline void cpuid(sdword code, sdword *a, sdword *d)
{
  // Note that even though only eax and edx are of interest here, ecx and ebx will also be modified
  asm volatile ("cpuid" : "=a"(*a), "=d"(*d) : "a" (code): "ecx", "ebx");
}

/*inline ubyte* cpuid_string(sdword code, udword where[4])
{
  magical_break();
  asm volatile("cpuid" : "=a"(*where), "=b"(*(where + 1)),
	       "=c"(*(where + 2)), "=d" (*(where + 3)) : "a"(code));
  magical_break();
  return where;
  }*/

