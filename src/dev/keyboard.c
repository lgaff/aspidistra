#include "types.h"
#include "keyboard.h"
#include "stdio.h"
#include "scancodes.h"
#include "interrupts.h"

ubyte lock_state = 0;
ubyte mod_state = 0;
ubyte *stdin_buffer;

void init_keyboard()
{
  stdin_buffer = kmalloc(512);
  kprintf("Registering keyboard interrupt.\n", "");
  register_interrupt_handler(IRQ1, &keyevent_alert);
}

static void keyevent_alert(registers_t regs)
{
  ubyte status_reg;
  enum scan_codes scan_code;
  ubyte ascii_val;
  /* Need to read the keyboard status register first. 
     Bit 0 denotes the status of the output buffer. 1 means data is available.
  */
  //  kprintf("D ");
  status_reg = inb(KBD_STATUS_REG);
  /* Check/set keyboard state flags */
  if(status_reg)
    {
      //  kprintf("R ");
      scan_code = inb(KBD_DATA_PORT);
      //      kprintf("SC=%02x", scan_code);
      switch(scan_code)	
	{
	case KP_CAPS_LOCK:
	  lock_state ^= LCK_CAPS;
	  break;
	case KP_NUM_LOCK:
	  lock_state ^= LCK_NUM;
	  break;
	case KP_SCROLL_LOCK:
	  lock_state ^= LCK_SCRL;
	  break;
	case KP_LALT:
	  mod_state |= MOD_ALT;
	  break;
	case KR_LALT:
	  mod_state &= ~MOD_ALT;
	case KP_LCTRL:
	  mod_state |= MOD_CTL;
	  break;
	case KR_LCTRL:
	  mod_state &= ~MOD_CTL;
	  break;
	case KP_LSHIFT:
	  mod_state |= MOD_SHFT;
	  break;
	case KR_LSHIFT:
	  mod_state &= ~MOD_SHFT;
	  break;
	case KP_ESCAPE:
	  mod_state |= MOD_ESC;
	  break;
	case KR_ESCAPE:
	  mod_state &= ~MOD_ESC;
	  break;
	  /* That takes care of state transitions. Now we need to handle printable characters.
	     I've ignored all other non-printable keys for now, as I'm not entirely sure of the best
	     way to  handle them...
	  */
	default:
	  if(scan_code <= KR_ESCAPE)
	    {
	      if(mod_state & MOD_SHFT)
		{
		  //kprintf("SH+ ");
		  ascii_val = shift_conversion[scan_code];
		}
	      else 
		{
		  //kprintf("SH- ");
		  ascii_val = ascii_conversion[scan_code];
		}
	      
	      if(lock_state & LCK_CAPS)
		{
		  //kprintf(" -C");
		  // we need to convert case unless shift is pressed.
		  if ((ascii_val >= 65 && ascii_val <= 90) || (ascii_val >= 97 && ascii_val <= 122))
		    ascii_val ^= 0x20;
		}
	      else
		//kprintf(" +C=%c", ascii_val);
		// Put the character into the stdin buffer
		//	  magical_break();
		*(stdin_buffer + stdin_buffer_pos) = ascii_val;
	      //kprintf(" +B=%c", *(stdin_buffer + stdin_buffer_pos));
	      stdin_buffer_pos++;
	      *(stdin_buffer + stdin_buffer_pos) = '\0'; // Make sure to null terminate so we know where the end of the string is.
	    }
	  // TODO handle modifier keys appropriately
	  status_reg = inb(KBD_STATUS_REG);
	  break;
	}

    }
      //  kprintf("\n");
}
