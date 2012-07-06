#ifndef MEM_H
#define MEM_H
#include "multiboot.h"

ubyte *mmap_types[5] =
  {
    "AVAL",
    "RSVD",
    "ACPI",
    "NVLT",
    "BDMM"
  };



void memcpy(void *dest, const void *source, udword count);

void show_memory_map(multiboot_info_t *mbd);
#endif
