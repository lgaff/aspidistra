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
  
physical_page_node_t* construct_mmap(multiboot_info_t *mbd)
{
  /* We can't use malloc() until this is run, so we need to use kmalloc() for now and move it once we 
     know where we can and can't allocate memory.
     page node struct is 12 bytes long, assuming 4KiB pages this is a maximum of 12 megs... Too much to
     do all at once because we're not handling page faults yet. So, we'll size the first 32 megs of ram
     for now, and then later we can size the rest (if it exists).

     32 megs at 12 bytes/entry =
        32768 KiB
	8192 4 KiB pages
	96 KiB map.

     We should have enough free space in the boot page table to map this without a problem (we mapped 1-4 MiB at 3.01 GiB, 
     so one would hope there's enough
  */
  multiboot_mmap_t *mmap = (multiboot_mmap_t *)mbd->mmap_addr;
  udword region = 0;
  udword frame_address = 0;
  udword frame_index = 0;
  udword region_frames = 0;

  physical_page_node_t *start = kmalloc(sizeof(physical_page_node_t));
  physical_page_node_t *next;
  physical_page_node_t *tmp;

  //  while(mmap->length_low >= 4096 && mmap < mbd->mmap_addr + mbd->mmap_length)
  //    {
      region++;
      vsprintf(print_buffer, "Region %d: Start %08x, %d bytes\n", region, mmap->base_low, mmap->length_low);
      console_putstr(DFL_ATTRIB, print_buffer);
      // initial frame address has to be rounded up to the nearest 4k boundary.
      frame_address = mmap->base_low + 4095;
      frame_address = frame_address - ((mmap->base_low + 4095) % 4096);
      vsprintf("Page-aligned to %08x. ", frame_address);
      region_frames = ((mmap->length_low - (mmap->length_low % 4096)) - frame_address) / 4096;
      vsprintf("Region frames %d. ", region_frames);
      //    }

      


  return start;
}
