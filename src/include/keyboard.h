#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef struct keyboard_state 
{
  ubyte lock_state; /* bit 0 = caps, 1 = num, 2 = scroll */
  ubyte mod_state;
} keyboard_state_t;

#define MOD_CTL 0x1
#define MOD_ALT 0x2
#define MOD_SHFT 0x4
#define MOD_ESC 0x8
#define LCK_CAPS 0x1
#define LCK_SCRL 0x2
#define LCK_NUM 0x4


enum scan_codes 
  {
    KP_ESCAPE = 0x01,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_0,
    KP_MINUS,
    KP_EQUALS,
    KP_BKSP,
    KP_TAB,
    KP_Q,
    KP_W,
    KP_E,
    KP_R,
    KP_T,
    KP_Y,
    KP_U,
    KP_I,
    KP_O,
    KP_P,
    KP_LSQBRACE,
    KP_RSQBRACE,
    KP_RET,
    KP_LCTRL,
    KP_A,
    KP_S,
    KP_D,
    KP_F,
    KP_G,
    KP_H,
    KP_J,
    KP_K,
    KP_L,
    KP_SEMICOLON,
    KP_QUOTE,
    KP_BACKTICK,
    KP_LSHIFT,
    KP_BACKSLASH,
    KP_Z,
    KP_X,
    KP_C,
    KP_V,
    KP_B,
    KP_N,
    KP_M,
    KP_COMMA,
    KP_PERIOD,
    KP_SLASH,
    KP_RSHIFT,
    KP_NUMPAD_STAR,
    KP_LALT,
    KP_SPACE,
    KP_CAPS_LOCK,
    KP_F1,
    KP_F2,
    KP_F3,
    KP_F4,
    KP_F5,
    KP_F6,
    KP_F7,
    KP_F8,
    KP_F9,
    KP_F10,
    KP_NUM_LOCK,
    KP_SCROLL_LOCK,
    KP_NUMPAD_7,
    KP_NUMPAD_8,
    KP_NUMPAD_9,
    KP_NUMPAD_MINUS,
    KP_NUMPAD_4,
    KP_NUMPAD_5,
    KP_NUMPAD_PLUS,
    KP_NUMPAD_1,
    KP_NUMPAD_2,
    KP_NUMPAD_3,
    KP_NUMPAD_0,
    KP_NUMPAD_PERIOD,
    /* scancodes 0x54-56 are not used */
    KP_F11 = 0x57,
    KP_F12,
    /* scancodes 0x59 - 0x80 are not used */
    KR_ESCAPE = 0x81,
    KR_1,
    KR_2,
    KR_3,
    KR_4,
    KR_5,
    KR_6,
    KR_7,
    KR_8,
    KR_9,
    KR_0,
    KR_MINUS,
    KR_EQUALS,
    KR_BKSP,
    KR_TAB,
    KR_Q,
    KR_W,
    KR_E,
    KR_R,
    KR_T,
    KR_Y,
    KR_U,
    KR_I,
    KR_O,
    KR_P,
    KR_LSQBRACE,
    KR_RSQBRACE,
    KR_RET,
    KR_LCTRL,
    KR_A,
    KR_S,
    KR_D,
    KR_F,
    KR_G,
    KR_H,
    KR_J,
    KR_K,
    KR_L,
    KR_SEMICOLON,
    KR_QUOTE,
    KR_BACKTICK,
    KR_LSHIFT,
    KR_BACKSLASH,
    KR_Z,
    KR_X,
    KR_C,
    KR_V,
    KR_B,
    KR_N,
    KR_M,
    KR_COMMA,
    KR_PERIOD,
    KR_SLASH,
    KR_RSHIFT,
    KR_NUMPAD_STAR,
    KR_LALT,
    KR_SPACE,
    KR_CAPS_LOCK,
    KR_F1,
    KR_F2,
    KR_F3,
    KR_F4,
    KR_F5,
    KR_F6,
    KR_F7,
    KR_F8,
    KR_F9,
    KR_F10,
    KR_NUM_LOCK,
    KR_SCROLL_LOCK, /* Note, this happens instantaneously with a scroll lock press event */
    KR_NUMPAD_7,
    KR_NUMPAD_8,
    KR_NUMPAD_9,
    KR_NUMPAD_MINUS,
    KR_NUMPAD_4,
    KR_NUMPAD_5,
    KR_NUMPAD_PLUS,
    KR_NUMPAD_1,
    KR_NUMPAD_2,
    KR_NUMPAD_3,
    KR_NUMPAD_0,
    KR_NUMPAD_PERIOD,
    /* Scancodes 0xD4 - D6 are unused */
    KR_F11 = 0xD7, KR_F12
    /* Scancodes 0xD9 - 0xDF are unused */
    /* More scancodes follow, but are for multimedia and so forth. */
  };
    
    


#define KBD_CTRL_PORT_B 0x61
#define KBD_DATA_PORT   0x60
#define KBD_CMD_REG     0x60
#define KBD_STATUS_REG  0x64

// Command port commands
#define KBD_CMD_READ0 0x20
#define KBD_CMD_READ2 0x21
#define KBD_CMD_READ3 0x22
#define KBD_CMD_READ4 0x23
#define KBD_CMD_READ5 0x24
#define KBD_CMD_READ6 0x25
#define KBD_CMD_READ7 0x26
#define KBD_CMD_READ8 0x27
#define KBD_CMD_READ9 0x28
#define KBD_CMD_READ10 0x29
#define KBD_CMD_READ11 0x2A
#define KBD_CMD_READ12 0x2B
#define KBD_CMD_READ13 0x2C
#define KBD_CMD_READ14 0x2D
#define KBD_CMD_READ15 0x2E
#define KBD_CMD_READ16 0x2F
#define KBD_CMD_READ17 0x30
#define KBD_CMD_READ18 0x31
#define KBD_CMD_READ19 0x32
#define KBD_CMD_READ20 0x33
#define KBD_CMD_READ21 0x34
#define KBD_CMD_READ22 0x35
#define KBD_CMD_READ23 0x36
#define KBD_CMD_READ24 0x37
#define KBD_CMD_READ25 0x38
#define KBD_CMD_READ26 0x39
#define KBD_CMD_READ27 0x3A
#define KBD_CMD_READ28 0x3B
#define KBD_CMD_READ29 0x3C
#define KBD_CMD_READ30 0x3D
#define KBD_CMD_READ31 0x3E
#define KBD_CMD_READ32 0x3F

#define KBD_CMD_WRIT0 0x60
#define KBD_CMD_WRT1 0x61
#define KBD_CMD_WRT2 0x62
#define KBD_CMD_WRT3 0x63
#define KBD_CMD_WRT4 0x64
#define KBD_CMD_WRT5 0x65
#define KBD_CMD_WRT6 0x66
#define KBD_CMD_WRT7 0x67
#define KBD_CMD_WRT8 0x68
#define KBD_CMD_WRT9 0x69
#define KBD_CMD_WRT10 0x6A
#define KBD_CMD_WRT11 0x6B
#define KBD_CMD_WRT12 0x6C
#define KBD_CMD_WRT13 0x6D
#define KBD_CMD_WRT14 0x6E
#define KBD_CMD_WRT15 0x6F
#define KBD_CMD_WRT16 0x70
#define KBD_CMD_WRT17 0x71
#define KBD_CMD_WRT18 0x72
#define KBD_CMD_WRT19 0x73
#define KBD_CMD_WRT20 0x74
#define KBD_CMD_WRT21 0x75
#define KBD_CMD_WRT22 0x76
#define KBD_CMD_WRT23 0x77
#define KBD_CMD_WRT24 0x78
#define KBD_CMD_WRT25 0x79
#define KBD_CMD_WRT26 0x7A
#define KBD_CMD_WRT27 0x7B
#define KBD_CMD_WRT28 0x7C
#define KBD_CMD_WRT29 0x7D
#define KBD_CMD_WRT30 0x7E
#define KBD_CMD_WRT31 0x7F

#define KBD_CMD_DSBL2 0xA7
#define KBD_CMD_ENBL2 0xA8
#define KBD_CMD_TST2 0xA9

#define KBD_CMD_DSBL1 0xAD
#define KBD_CMD_ENBL1 0xAE
#define KBD_CMD_TST1 0xAB

#define KBD_CMD_RCOP 0xD0
#define KBD_CMD_WCOP 0xD1
#define KBD_CMD_WRTO1 0xD2
#define KBD_CMD_WRTO2 0xD3
#define KBD_CMD_WRTI2 0xD4

#define KBD_CMD_PULSE 0xF0



extern void init_keyboard();

static void keyevent_alert(registers_t regs);

#endif
