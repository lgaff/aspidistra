#include "types.h"
#include "stdio.h"

uword stdin_buffer_pos = 0;

ubyte getc(ubyte *buffer)
{
     magical_break();
     ubyte c;
     // This process blocks until a char is found on the input buffer. 
     while(stdin_buffer_pos == 0) // buffer empty
     {

	  //_sleep(10); // This function doesn't exist yet.
     }
     magical_break();
     stdin_buffer_pos--;
     c = *(stdin_buffer + stdin_buffer_pos);
     
     return c;
}

ubyte *gets(ubyte *buffer)
{
  ubyte current_c;
  udword index = 0;
  ubyte *str_buf = (ubyte *)kmalloc(512); // 512 bytes is the length of the keyboard buffer.
  while(current_c != '\n')
    {
      current_c = getc(stdin_buffer);
      *(str_buf + index++) = current_c;
    }
  return str_buf;
}
    

    
