#ifndef MEM_H
#define MEM_H
#include "multiboot.h"

#define PG_SIZE 4096

ubyte *mmap_types[5] =
  {
    "AVAL",
    "RSVD",
    "ACPI",
    "NVLT",
    "BDMM"
  };


/* Once we know the size of physical memory, we want to construct a linked list of PG_SIZE bytes of contiguous memory 
   so we can allocate page frames properly. The multiboot memory map will be used to walk through the memory structure
   and create this structure. 
*/
typedef struct physical_page_node 
{
  udword *next;
  udword *address;
  uword present;
} physical_page_node_t;

/* Constructs a linked list of all physical page frames the system can support. Walks the multiboot memory map 
   structure to avoid reserved and unavailable regions. */
extern physical_page_node_t* construct_mmap(multiboot_info_t *mbd);

extern void memcpy(void *dest, const void *source, udword count);

extern void show_memory_map(multiboot_info_t *mbd);

#endif
