// declarations for VGA console IO

#include "types.h"
#ifndef _CONSOLE_H
#define _CONSOLE_H

#define DFL_ATTRIB 0x0F
// Put an attributed character at current cursor location
void console_putchar(ubyte attribute, ubyte character);

// numeric data niceties.
void console_putint(ubyte attribute, sdword number);

void console_puthex(ubyte attribute, udword number);

// As above for strings
void console_putstr(ubyte attribute, ubyte *string);

// scroll the console buffer by one row. scrollback is purged.
void console_scroll();

// Update the hardware cursor position
void console_update_cursor();

// clear the console.
void console_clear();

#endif
