// Keyboard scan code table

#ifndef SCANCODE_H
#define SCANCODE_H

/* Useful keypad release scancodes */

const static ubyte ascii_conversion[128] =
  {
    0, /* Null */
    0, /* ESC */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
    '\n', /* Return */
    0, /* Left Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, /* Right shift */ 
    '*', /* Keypad * */
    0, /* Left alt */
    ' ', 
    0, // Caps Lock
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1-F10
    0, // Num Lock
    0, /* Scroll Lock */
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // Key pad
    0, 0, 0, // Nothing
    0, 0 // F11, F12
  };

/* Probably not the optimal solution, but it works :) */

const static ubyte shift_conversion[128] =
  {
    0, /* Null */
    0, /* ESC */
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
    '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 
    '\n', /* RETURN */
    0, /* LEFT CONTROL */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 
    0, /* LEFT SHIFT */
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 
    0, /* RIGHT SHIFT */ 
    '*', /* KEYPAD * */
    0, /* LEFT ALT */
    ' ', 
    0, // CAPS LOCK
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1-F10
    0, // NUM LOCK
    0, /* SCROLL LOCK */
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // KEY PAD
    0, 0, 0, // NOTHING
    0, 0 // F11, F12
  };

#endif
