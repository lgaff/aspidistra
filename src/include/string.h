#ifndef STRING_H
#define STRING_H

// flags for *printf's
#define GROUP   1 /* include thousands separator for integer values */
#define LEFT    2 /* left-justify the field */
#define SIGN    4 /* signed conversions should always include either '+' or '-' */
#define SPACE   8 /* include a space where a '+' would be if SIGN is not specified. ignored if SIGN flag set. */
#define ALT     16 /* alternative conversion format. means hex values get 0x, other radices get a radix affix */
#define ZEROPAD 32 /* pad field length with zeroes. */
#define CASE    64 /* lowercase hex */

void vsprintf(ubyte *output_str, ubyte *fmt, va_list args); // Prints a formatted string to the console. Only useful while in text mode.

void kprintf(ubyte *fmt, va_list args);

// Both of these conversion functions assume 0-9 A-Z as the order of magnitudes. 
// This sets a maximum base size of 36.
ubyte *_itoa(sdword number, uword base); // base-independant integer to ascii conversion. explicitly null-terminated

udword _atoi(ubyte *str, ubyte base); // base-independant ascii to integer conversion. 

#define atoi(number) _atoi(number, 10)
#define hextoi(number) _atoi(number, 16)
#define bintoi(number) _atoi(number, 2)
#define octtoi(number) _atoi(number, 8)

#define itoa(number) _itoa(number, 10)
#define hextoa(number) _itoa(number, 16)
#define bintoa(number) _itoa(number, 2)
#define octtoa(number) _itoa(number, 8)

udword strlen(ubyte *str);

ubyte *strtolower(ubyte *str); 
ubyte *strtoupper(ubyte *str); 

#endif

