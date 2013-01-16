// Standard conversion functions. A lot of this overlaps with 
// functions traditionally defined in stdlib.h

#include "types.h"
#include "stdconv.h"

ubyte hextoi(ubyte c) {
     // Case conversion to make the lower logic easier. 
     // return values out of the range 0-15 can be considered an error.
     if(c >= 65) {
	  c |= 32;
     }
     if((c >= 48) && (c <= 57)) {
	  c -= 48;
     }
     if (c >= 65) {
	  c -= 55;
     }
     // At this point, any values out of range 0-15 are incorrect.
     if(c > 15) {
	  c = 16;
     }
     return c;
}
