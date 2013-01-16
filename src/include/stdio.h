// Standard input/output.
#ifndef STDIO_H
#define STDIO_H

#define STDOUT_BEGIN 0xB8000

extern ubyte *stdin_buffer;

extern uword stdin_buffer_pos;



extern ubyte getc(ubyte *buffer); // returns a single character from buffer.

extern ubyte *gets(ubyte *buffer); // returns a null-terminated string from buffer

//extern void putc(ubyte *buffer, ubyte c); // replacement for console_putchar.

//extern void puts(ubyte *buffer, ubyte *str) // replacement for console_putstr.

#endif
