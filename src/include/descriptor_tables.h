// descriptor_tables.h defines the structures for loading and manipulating the GDT and IDT
#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

static void gdt_set_gate(sdword, udword, udword, ubyte, ubyte);
static void idt_set_gate(ubyte index, udword base, uword selector, ubyte flags);

void init_tables();
static void initialise_gdt();
static void initialise_idt();

extern void gdt_flush(udword);
extern void idt_flush(udword);

struct gdt_entry
{
  uword limit_low;
  uword base_low;
  ubyte base_middle;
  ubyte access;
  ubyte granularity;
  ubyte base_high;
}__attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr
{
  uword limit;
  udword base;
}__attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct idt_entry
{
  uword base_low;
  uword selector;
  ubyte always0;
  ubyte flags;
  uword base_high;
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr
{
  uword limit;
  udword base;
}__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

#endif
