// 4 bit text mode console driver for startup diagnostics.
#include "vga.h"
#include "console.h"
#include "io.h"
#include "types.h"

ubyte cursor_x = 0;
ubyte cursor_y = 0;

uword *console_buffer = (uword *)0xB8000;


void console_putchar(ubyte attribute, ubyte character)
{
  /* This needs to accomplish some stuff first off:
     - Construct the word to send to the console, consisting of 
       The character code ORed with the attribute value. We need to handle
       special control characters separately where they arise.
     - Call console_scroll, in case the cursor position is about to move off screen
     - Send the word to the console, and update the hardware cursor position.
  */

  uword cell = character | (attribute << 8);

  switch(character)
    {
    case 0x08: // backspace
      /* If we're at row/col 0, we ignore this. otherwise we move back to the next
	 logical cursor position and clear the contents there. */
      if (cursor_x == 0)
	{
	  if (cursor_y > 0)
	    {
	      cursor_y--; // go back one line.
	      cursor_x = VGA_X - 1; // Last column
	    }
	}
      else 
	{
	  cursor_x--;
	}
      break;
    case '\t': // tabstops are handled by adding 8 to the x position, ANDing with ~7 to align against 8 cell boundaries.
      cursor_x = (cursor_x + 8) & ~7;
      break;
    case '\r': // carriage return sends the cursor back to column 0
      cursor_x = 0;
      break;
    case '\n': // Newline should move us down a line.
      cursor_y++;
      cursor_x = 0;
      break;
    default:
      if(character >= ' ') // Make sure the character is printable first
	{
	  console_buffer[cursor_y * VGA_X + cursor_x] = cell;
	  cursor_x++;
	}
      break;
    }
      if(cursor_x >= VGA_X)
	{
	  cursor_x = 0;
	  cursor_y++;
	}
      console_scroll();
}

void console_putint(ubyte attribute, sdword number)
{
  // Largest number we can display with an unsigned dword is 4294967295 (2**32-1)
  // So we need char storage for 10 bytes
  ubyte int_vals[10];
  ubyte temporary = 0;
  udword index = 10;
  udword raise = 1;

  if(number < 0)
    console_putchar(DFL_ATTRIB, '-');
  while(index--)
    {
      temporary = number % 10;
      int_vals[index] = temporary;
      number = (number - temporary) / 10;
    }
  // Now, we'll skip leading 0's
  index = 0;
  while(int_vals[index] == 0 && index < 9)
    index++;
  
  while(index <= 9)
    {
      temporary = int_vals[index] + 48; // 48 == ascii table offset of '0';
      console_putchar(attribute, temporary);
      index++;
    }
}
      
void console_puthex(ubyte attribute, udword number)
{
  // hex values are a bit easier, we can drive this using a series of shifts.
  ubyte hex_vals[8]; // each hex value represents 4 bits.
  udword index = 0;
  ubyte temporary = 0;

  for(index = 0; index < 8;index++)
    {
      temporary = (number >> index*4) & 0x0000000F;
      hex_vals[index] = temporary;
    }

  console_putstr(attribute, "0x");
  while(index--)
    {
      if (hex_vals[index] > 9)
	temporary = hex_vals[index] + 55;
      else
	temporary = hex_vals[index] + 48;
      console_putchar(attribute, temporary);
    }
}

void console_putstr(ubyte attribute, ubyte *string)
{
  // repeated application of console_putchar
  udword index = 0;
  while (*string != '\0')
    {
      console_putchar(attribute, *string);
      *string++;
    }
}

void console_scroll()
{
  /* Scrolling the console is accomplished by overwriting the nth row with
     the full contents of the n+1th row. In doing so, the contents of the
     first row are lost. the last row must also be cleared.
  */
  static ubyte attribute = ATTRIB(VGA_BLK, VGA_WHI);
  uword blank = 0x20 | (attribute << 8);
  uword index;
  uword *current_row = console_buffer;


  if (cursor_y >= VGA_Y)
    {
      for(index = 0;index < (VGA_Y - 1) * VGA_X;index++)
	{
	  console_buffer[index] = console_buffer[index + VGA_X];
	}

      for(index = 0;index < VGA_X;index++)
	{
	  console_buffer[index + (VGA_Y - 1) * VGA_X] = blank;
	}
      cursor_y = VGA_Y - 1;
    }
  console_update_cursor();
  
}

void console_update_cursor()
{
  uword cursor_pos = cursor_y * VGA_X + cursor_x;
  outb(VGA_IO_CRT1_CTL, VGA_IDX_CRTC_CLHR); // wake up the control port to receive input
  outb(VGA_IO_CRT1_OUT, cursor_pos >> 8); // High byte.
  outb(VGA_IO_CRT1_CTL, VGA_IDX_CRTC_CLLR); // same again, for low byte
  outb(VGA_IO_CRT1_OUT, cursor_pos);
}


void console_clear()
{
  static uword blank = ' ' | ATTRIB(VGA_BLK, VGA_WHI) << 8;
  uword index = 0;
  for(index = 0;index < (VGA_X * VGA_Y);index++)
    {
      console_buffer[index] = blank;
    }
}
