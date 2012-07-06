// String manipulatin' routines beyond console primitives belong here

#include "types.h"
#include "stdarg.h"
#include "string.h"
#include "console.h"

extern ubyte *print_buffer;

void vsprintf(ubyte *output_str, ubyte *fmt, va_list args)
{
  // What follows is a fairly hairy looking scanner. 
  // error-checking is not my current priority, so be prepared for this to fail unless you drive it right.

  ubyte *string_parameter = (ubyte *)kmalloc(128);
  ubyte *param_pos = string_parameter;
  sword len;
  
  
  ubyte flags;
  sbyte width;
  ubyte precision;
  ubyte done = 0;
  uword index = 0;
  sdword varag;

  varag = va_start(args, fmt);

  for(index=0;index < 512;index++)
    {
      *(output_str + index) = '\0';
    }

  index = 0;
  while(*fmt)
    {
      done = 0;
      if(*fmt != '%')
	{
	  *(output_str + index) = *fmt++;
	  index++;
	}
      else
	{
	  flags = 0;
	  while(!done)
	    {
	      *fmt++; // skip the escape %
	      switch(*fmt)
		{
		case '\'': flags |= GROUP; break;
		case '-' : flags |= LEFT; break;
		case '+' : flags |= SIGN; break;
		case ' ' : flags |= SPACE; break;
		case '#' : flags |= ALT; break;
		case '0' : flags |= ZEROPAD; break;
		default: done++; break;
		}
	    }
	  // flags should now be set, next value is the optional field width
	  if(*fmt >= 0x30  && *fmt <= 0x39)
	    {
	      width = *fmt - 0x30;
	      *fmt++;
	    }
	  else
	    width = -1;

	  // TODO: there's a bunch of extra functionality in the printf standard that's not being 
	  // included here. precision, conversion qualifiers, other.

	  // Now we see what value we're returning
	  switch(*fmt++)
	    {
	      
	    case 'c': // character
	      string_parameter[0] = (ubyte)va_arg(args, udword);
	      len = 1;
	      string_parameter[1] = '\0';
	      break;
	      
	    case 's': // String.
	      string_parameter = va_arg(args, ubyte *);
	      len = strlen(string_parameter);
	      break;

	    case 'd': // Integer (base 10)
	      varag = va_arg(args, sdword);
	      if(varag > 0 && flags & SIGN)
		{
		  *(output_str + index) = '+';
		  index++;
		}
	      else if(varag > 0 && flags & SPACE)
		{
		  *(output_str + index) = ' ';
		  index++;
		}
	      string_parameter = itoa(varag);
	      len = strlen(string_parameter);
	      break;
	      
	    case 'o': // octal
	      string_parameter = octtoa(va_arg(args, udword));
	      len = strlen(string_parameter);
	      break;
	      
	    case 'x': // lowercase hex
	      flags |= CASE;
	    case 'X': // uppercase hex
	      *(output_str + index) = '0';
	      index++;
	      *(output_str + index) = 'x';
	      index++;
	      string_parameter = hextoa(va_arg(args, udword));
	      if(flags & CASE)
		{
		  string_parameter = strtolower(string_parameter);
		}
	      len = strlen(string_parameter);
	      break;

	    case 'b': // binary
	      string_parameter = bintoa(va_arg(args, udword));
	      len = strlen(string_parameter);
	      break;

	    case '%': // pass the % right through.
	      string_parameter[0] = '%';
	      len = 1;
	      string_parameter[1] = '\0';
	      break;

	    default: // Does nothing at the moment (essentially silently ignores malformed strings.
	      break;
	    }
	  if(flags & ZEROPAD && !(flags & LEFT))
	    {
	      while(len < width--)
		{
		  *(output_str + index) = '0';
		  index++;
		}
	    }
	  
	  // now we need to pad the field if necessary, then add the string parameter to it
	  if(!(flags & LEFT))
	    {
	     while(len < width--)
	       {
		 *(output_str + index) = ' ';
		 index++;
	       }
	    }
	  while(*string_parameter)
	    {
	      *(output_str + index) = *string_parameter++;
	      index++;
	    }
	  if(flags & LEFT)
	    {
	      while (len < width--)
		{
		  *(output_str + index) = ' ';
		  index++;
		}
	    }
	     
	  
	  // Done, clean up and continue.
	  len = 0;
	  string_parameter = param_pos;
	}
    }
  *(output_str + index) = '\0';
  //  return output_str;
}

void kprintf(ubyte *fmt, va_list args)
{
  vsprintf(print_buffer, fmt, args);
  console_putstr(DFL_ATTRIB, print_buffer);
} 

udword _atoi(ubyte *str, ubyte base)
{
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ubyte current_char;
  udword return_value = 0;
  udword place_value = 1;
  udword digit_value = 0;
  ubyte index = 0;

  while(*str++)
    {
      current_char = *str;
      if(current_char > 96 && current_char < 123)
	current_char &= 0xDF; // do a quick case conversion.
      for(index = 0;index < base;index++)
	{
	  if(current_char == digits[index])
	    digit_value = index * place_value;
	}
      return_value += digit_value;
      digit_value = 0;
    }
  return return_value;
}

ubyte *_itoa(sdword number, uword base)
{
  ubyte *return_string = (ubyte *)kmalloc(33); // longest representable value in base 2 (assuming word size) is 32 + null character
  ubyte digit = 0;
  ubyte index;
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
      
  for(index = 0;index <= 32; index++)
    {
      return_string[index] = '\0';
    }
  if(number < 0)
    { // flip the bits and add 1 for abs. This includes a bug. Too tired to fix right now.
      number = -number;
      return_string[0] = '-';
      index++;
    }


  if(base < 2 || base > 36) // cannot represent these values.
    {
        return return_string;
    }
  index = 32;
  while(number > 0 && index)
    {
      digit = number % base;
      return_string[--index] = digits[digit];
      number = (number - digit) / base;
    }
  // remove leading zeroes.
  digit = 0;
  while(index <= 32)
    {
      return_string[digit++] = return_string[index++];
    }
  return_string[index] = '\0';
  return return_string;
}
      
udword strlen(ubyte *str)
{
  udword len = 0;
  while(*str++)
    {
      len++;
    }
  return len;
}

ubyte *strtolower(ubyte *str)
{
  uword index = 0;
  while(*(str + index))
    {
      if(*(str + index) > 64 && *(str + index) < 91)
	*(str + index) |= 0x20;
      index++;
    }
  return str;
}

ubyte *strtoupper(ubyte *str)
{
  uword index = 0;
  while(*(str + index))
    {
      if(*(str + index) > 96 && *(str + index) < 123)
	*(str + index) &= 0xDF;
    }
  return str;
}

