#include "types.h"
#include "mem.h"
#include "console.h"
#include "multiboot.h"

extern ubyte *print_buffer;
// Kernel memory allocation/deallocation/manipulation routines

void memcpy(void *dest, const void *source, udword count)
{
  ubyte* dst = (ubyte *)dest;
  ubyte* src = (ubyte *)source;
  --dst; // pre-increment these so we align properly.
  --src; 
  while(count--);
    {
      *++dst = *++src;
    }  
}

void show_memory_map(multiboot_info_t *mbd)
{
  uword offset = 0;
  udword end_addr = 0;
  udword total_avl = 0;
  udword total_rsv = 0;

 if(mbd->flags & (1 << 6))
    {
      multiboot_mmap_t* mmap = (multiboot_mmap_t*)mbd->mmap_addr;
      vsprintf(print_buffer,"Memory map present at address %08x, size %08x\n", mbd->mmap_addr, mbd->mmap_length);
      console_putstr(DFL_ATTRIB, print_buffer);

      kprintf("|REGION\t|BASE\t \t|END\t \t|SIZE\t \t|TYPE\t|\n");
      while(mmap < mbd->mmap_addr + mbd->mmap_length)
	{
	  end_addr = mmap->base_low + mmap->length_low;
	  vsprintf(print_buffer, "%-d\t|%08x\t|%08x\t|%-9d\t|%s\t|\n",
		   ++offset,mmap->base_low,end_addr,mmap->length_low,mmap_types[mmap->type-1]);
	  console_putstr(DFL_ATTRIB, print_buffer);
	  if(mmap->type == 1)
	    total_avl += mmap->length_low;
	  if(mmap->type == 2)
	    total_rsv += mmap->length_low;

	  mmap = (multiboot_mmap_t*)((udword)mmap + mmap->size + sizeof(udword));
	}
      kprintf("%dK Available physical memory\n", (total_avl / 1024));
      kprintf("%dK Reserved\n", (total_rsv / 1024));
    }
}
  

