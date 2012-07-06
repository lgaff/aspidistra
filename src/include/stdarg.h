// standalone stdarg implementation for aspidistrOS
#ifndef STDARG_H
#define STDARG_H

typedef ubyte *va_list;

#define STACKITEM sdword;

// CDECL calling convention tells us that the calling function has pushed args onto the 
// stack in reverse order. this means that when we pop them back off they will be in normal order.

// va_list args are therefore on the top of the stack after all other args are handled. 
// So the va_list macros need to "pop" (in reality, add an offset to the stack pointer from the last
// known parameter + count of already popped va_args to retrieve va_arg x. 
// each pop should add 1 times the word size of the system (x86, this means 32 bit). The macro is responsible for a
// cast to the data type that the va_arg should be.

// Standard va_list macros: va_arg, va_start, va_end.

/* va_rounded_size determines the word-aligned size of the passed argument to be returned to the function
   In theory (practise?) this probably should always evaluate to 4 */
#define __va_rounded_size(TYPE) \
(((sizeof(TYPE) + sizeof(sdword) - 1) /  sizeof(sdword)) * sizeof(sdword))

/* va_start determines the address of the first argument passed in the va_list structure ("Structure").
   AP: Should be a pointer to the passed va_list.
   LASTARG: address of the last fixed argument passed in by the caller */
#define va_start(AP, LASTARG) \
  (AP = ((ubyte *) &(LASTARG) + __va_rounded_size (LASTARG)))

/* Retrieve the next argument passed according to its type. */
#define va_arg(AP, TYPE) \
  (AP += __va_rounded_size (TYPE), *((TYPE *) (AP - __va_rounded_size (TYPE))))

#define va_end(AP)

#endif
