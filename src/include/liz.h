#ifndef LIZ_H
#define LIZ_H

extern void liz_main(udword *);

typedef enum liz_ops {
     LIZ_GO,
     LIZ_START,
     LIZ_ERASE,
     LIZ_DATA,
     LIZ_OPCODE,
     LIZ_ERROR
} liz_ops;

enum liz_types {
     LIZ_INT,
     LIZ_LONG,
     LIZ_CHAR,
     LIZ_BYTE,
     LIZ_STR,
     LIZ_EXIT
};

void write_liz_prompt(udword pc, uword offset, uword instruction);

void write_liz_ok(udword addr);

ubyte liz_syntax_check(ubyte *cmd);

liz_ops liz_parse(ubyte *cmd);

udword *liz_data(udword *pc);

#endif
