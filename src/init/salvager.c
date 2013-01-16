/* Basic salvager prompt loop */

#include "types.h"
#include "stdio.h"
#include "salvager.h"
#include "console.h"

uword *VGA = (uword *)0xB8000; // Debug that shizzle.

/* Kernel debugger console. Accepts simple commands for examining 
   and updating locations in memory. 
   
   COMMANDS IMPLEMENTED
   
   COMMANDS TO IMPLEMENT
   peek <addr> # Peek at a virtual address in memory. show result on screen
   poke <addr> <val> # Update value at addr with val
   stat # Dump register state
*/

void salvager_loop()
{
  ubyte *cmd_line = kmalloc(512);
  ubyte c;
  uword s;
  ubyte index = 0;
  kprintf("Cmd buffer is %08x\n", &cmd_line);
  while(1) // Erk!
    {
      kprintf("> ");
      while (c != '\n')
	{ 	 
	  c = getc(stdin_buffer);
	  *(cmd_line + index) = c;
	  *(cmd_line + index + 1) = '\0';
	  index++;
	  kprintf("%c", c);
	}
      kprintf("%s", eval(parse(lex(c))));
      kprintf("%s", cmd_line);
      c = '\0';
      
      index = 0;
    }
}


