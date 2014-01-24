#include "types.h"
#include "cpu.h"


inline void cpuid(sdword code, sdword *a, sdword *d)
{
  // Note that even though only eax and edx are of interest here, ecx and ebx will also be modified
  asm volatile ("cpuid" : "=a"(*a), "=d"(*d) : "a" (code): "ecx", "ebx");
}
