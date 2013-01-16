/** Liz is a minimalist monitor utility for bare metal development.
    Its primary function is to provide an interface for arbitrary loading
    of debug functions onto the heap for execution.

    It currently accomplishes this using Hexadecimal input of raw machine opcodes
    
    In support of this, Liz provides the following additional commands:

      - g :: (go) Executes the loaded program. 
             This implies the following operations:
	     1. Insert a ret after last loaded instruction
	     2. Call the loaded program.
	     3. Return control to Liz.
      - s :: (start) Sets the current location as the program entry point (For setting up data sections at the top of memory)
      - e :: (erase) Clobber the loaded program, returning allocated memory to the heap
      - d :: (data) Data mode, for loading constant data. This implements a subshell:
             <type> <data>, where <type> is one of:
             i: Integer constant.
	     l: Long Integer.
	     b: Byte constant in decimal.
	     c: ASCII character.
	     s: String literal encased in "s (Interpolated: \n\t\b\*).
	     e: Exit data mode

    Interface

      Liz provides a very simple interface for opcode input. Opcodes are entered in 
      hexadecimal at the prompt (a '>'), when Return is pressed, the opcode is 
      syntax-checked (In this case, this just means a string of [0-9a-zA-Z]*, nothing more),
      Then entered at the current offset into memory. Each time this is done, 
      the 'counter' is incremented, and the current address, byte offset from 
      the top of the heap, and the instruction number is displayed.
      Invalid opcodes will result in a '?' being displayed.      
**/


#include "types.h"
#include "stdio.h"
#include "string.h"
#include "liz.h"
#include "console.h"


void liz_main(udword *heap_start) {
     ubyte *cmd_buffer = (ubyte *)kmalloc(256);
     ubyte buf_idx = 0;
     heap_start = (udword *)kmalloc(512); // Initial allocation of memory for program. 
     ubyte c;
     ubyte load_val = 0;
     udword *program_counter;
     void (*entry_point)();
     uword heap_offset = 0;
     uword instruction = 0;

     program_counter = heap_start;
     entry_point = (void (*)())heap_start;

     for(;;) { // Liz runs as an infinite loop, there is nothing to exit from once here.
	  write_liz_prompt((udword)&program_counter, heap_offset, instruction);
	  while(c != '\n') {

	       c = getc(stdin_buffer);
	       *(cmd_buffer + buf_idx++) = c;
	       *(cmd_buffer + buf_idx) = '\0';
	       kprintf("c = %c", c);
	  }
	  if(!liz_syntax_check(cmd_buffer)) {
	       kprintf("?\n");
	       continue;
	  }
	  
	  switch(liz_parse(cmd_buffer)) {
	  case LIZ_GO:
	       *program_counter++ = 0xC3;
	       (*entry_point)();
	       kprintf("Program terminated.\n");
	       break;
	  case LIZ_START:
	       entry_point = (void(*)())program_counter;
	       write_liz_ok((udword)&program_counter);
	       break;
	  case LIZ_ERASE:
	       /* This is a soft erase, since we don't currently have any free(),
		  we just change the PC (and entry point) back to heap_start.
	       */
	       program_counter = heap_start;
	       entry_point = (void(*)())program_counter;
	       write_liz_ok((udword)&program_counter);
	       break;
	  case LIZ_DATA:
	       program_counter = liz_data(program_counter);
	       heap_offset = (&program_counter - &heap_start) / sizeof(uword);
	       write_liz_ok((udword)&program_counter);
	       break;
	  case LIZ_OPCODE:
	       /* Anything else we assume to be raw bytes */
	       buf_idx = 0;
	       while((c = *(cmd_buffer + buf_idx++)) != '\0') {
		    load_val = hextoi(c) << 4; // upper nibble.
		    c = *(cmd_buffer + buf_idx++);
		    if(c == '\0') {
			 kprintf("?\n");
			 break;
		    }
		    else {
			 load_val |= hextoi(c);
			 *program_counter++ = load_val;
			 heap_offset = (&program_counter - &heap_start) / sizeof(uword);
			 instruction++;
			 write_liz_ok((udword)&program_counter);
		    }
	       }
	       break;
	  case LIZ_ERROR:
	       kprintf("?\n");
	       break;
	  }
     }
}


void write_liz_prompt(udword pc, uword offset, uword instruction) {
     kprintf("PC=%d : OFF=%d\n%d> ", pc, offset, instruction);
}

void write_liz_ok (udword pc) {
     kprintf("%d OK\n", pc);
}

ubyte liz_syntax_check(ubyte *cmd) {
     ubyte c;
     uword idx = 0;
     while((c = *(cmd + idx++)) != '\0') {
	  if((c >= 48) && (c <= 57)) { /* [0-9] */ }
	  else if((c >= 65) && (c <= 90)) { /* [A-Z] */ }
	  else if((c >= 97) && (c <= 122)) { /* [a-z] */ }
	  else {
	       return 0;
	  }
     }
     return 1;
}

/* Evaluate the input command and return the command type */
liz_ops liz_parse(ubyte *cmd) {
     ubyte c = *cmd;
     ubyte idx = 0;

     switch(c) {
     case 'g':
	  return LIZ_GO;
	  break;
     case 's':
	  return LIZ_START;
	  break;
     case 'e':
	  return LIZ_ERASE;
	  break;
     case 'd':
	  return LIZ_DATA;
	  break;
	  /* as with syntax check, anything else is assumed to be hex opcodes
	     So we need to range check the entire command against [a-zA-Z0-9]
	  */
     default:
	  while(c != '\0') {
	       if((c >= 48) && (c <= 57)) { /* [0-9] */ }
	       else if((c >= 65) && (c <= 70)) { /* [A-Z] */ }
	       else if((c >= 97) && (c <= 102)) { /* [a-z] */ }
	       else {
		    return LIZ_ERROR;
	       }
	       c = *(cmd + ++idx);
	  }
	  return LIZ_OPCODE;
     }
}

/** data mode is handled here. The function continues until a double newline
    is encountered, each line is interpreted according to the specified data
    type (the first character entered), then each byte is written to the passed
    vaddr, which is incremented. Return value is the updated PC.
**/
udword *liz_data(udword *pc) {
     return pc;
}
