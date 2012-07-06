#include "types.h"
#include "descriptor_tables.h"
#include "interrupts.h"

gdt_entry_t gdt_entries[5]; // null, code, data, umode code, umode data.
gdt_ptr_t gdt_pointer;
idt_entry_t idt_entries[256]; 
idt_ptr_t idt_pointer;

void init_tables()
{
  initialise_gdt();
  initialise_idt();
}

static void initialise_gdt()
{
  gdt_pointer.limit = (sizeof(gdt_entry_t) * 5) - 1;
  gdt_pointer.base = (udword)&gdt_entries;

  // now we set our gdt entries. we want a flat memory space for both kernel and userland

  gdt_set_gate(0, 0, 0, 0, 0);   // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  gdt_flush((udword)&gdt_pointer);
}

static void gdt_set_gate(sdword index, udword base, udword limit, ubyte access, ubyte granularity)
{
  gdt_entries[index].base_low = (base & 0xFFFF);
  gdt_entries[index].base_middle = (base >> 16) & 0xFF;
  gdt_entries[index].base_high = (base >> 24) & 0xFF;
  
  gdt_entries[index].limit_low = (limit & 0xFFFF);
  gdt_entries[index].granularity = (limit >> 16) & 0x0F;
  
  gdt_entries[index].granularity |= granularity & 0xF0;
  gdt_entries[index].access = access;
}
 
static void initialise_idt()
{
  idt_pointer.limit = sizeof(idt_entry_t) * 256 -1;
  idt_pointer.base = (udword)&idt_entries;


  memset((ubyte *)&idt_entries, 0, sizeof(idt_entry_t)*256);


  // The 8259 PIC(s) irq lines on the PC are by default configured to listen on the first 16 interrupt gates.
  // This causes a problem when anything routine happens like say, a page fault. 
  // To get around this, it's necessary as part of the startup process to map the 16 IRQ lines onto interrupt gates
  // that are not in use.
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_set_gate(0, (udword)isr0, 0x08, 0x8E);
  idt_set_gate(1, (udword)isr1, 0x08, 0x8E);
  idt_set_gate(2, (udword)isr2, 0x08, 0x8E);
  idt_set_gate(3, (udword)isr3, 0x08, 0x8E);
  idt_set_gate(4, (udword)isr4, 0x08, 0x8E);
  idt_set_gate(5, (udword)isr5, 0x08, 0x8E);
  idt_set_gate(6, (udword)isr6, 0x08, 0x8E);
  idt_set_gate(7, (udword)isr7, 0x08, 0x8E);
  idt_set_gate(8, (udword)isr8, 0x08, 0x8E);
  idt_set_gate(9, (udword)isr9, 0x08, 0x8E);
  idt_set_gate(10, (udword)isr10, 0x08, 0x8E);
  idt_set_gate(11, (udword)isr11, 0x08, 0x8E);
  idt_set_gate(12, (udword)isr12, 0x08, 0x8E);
  idt_set_gate(13, (udword)isr13, 0x08, 0x8E);
  idt_set_gate(14, (udword)isr14, 0x08, 0x8E);
  idt_set_gate(15, (udword)isr15, 0x08, 0x8E);
  idt_set_gate(16, (udword)isr16, 0x08, 0x8E);
  idt_set_gate(17, (udword)isr17, 0x08, 0x8E);
  idt_set_gate(18, (udword)isr18, 0x08, 0x8E);
  idt_set_gate(19, (udword)isr19, 0x08, 0x8E);
  idt_set_gate(20, (udword)isr20, 0x08, 0x8E);
  idt_set_gate(21, (udword)isr21, 0x08, 0x8E);
  idt_set_gate(22, (udword)isr22, 0x08, 0x8E);
  idt_set_gate(23, (udword)isr23, 0x08, 0x8E);
  idt_set_gate(24, (udword)isr24, 0x08, 0x8E);
  idt_set_gate(25, (udword)isr25, 0x08, 0x8E);
  idt_set_gate(26, (udword)isr26, 0x08, 0x8E);
  idt_set_gate(27, (udword)isr27, 0x08, 0x8E);
  idt_set_gate(28, (udword)isr28, 0x08, 0x8E);
  idt_set_gate(29, (udword)isr29, 0x08, 0x8E);
  idt_set_gate(30, (udword)isr30, 0x08, 0x8E);
  idt_set_gate(31, (udword)isr31, 0x08, 0x8E);
  // 8259 PIC controlled IRQ's follow.
  idt_set_gate(32, (udword)irq0, 0x08, 0x8E);
  idt_set_gate(33, (udword)irq1, 0x08, 0x8E);
  idt_set_gate(34, (udword)irq2, 0x08, 0x8E);
  idt_set_gate(35, (udword)irq3, 0x08, 0x8E);
  idt_set_gate(36, (udword)irq4, 0x08, 0x8E);
  idt_set_gate(37, (udword)irq5, 0x08, 0x8E);
  idt_set_gate(38, (udword)irq6, 0x08, 0x8E);
  idt_set_gate(39, (udword)irq7, 0x08, 0x8E);
  idt_set_gate(40, (udword)irq8, 0x08, 0x8E);
  idt_set_gate(41, (udword)irq9, 0x08, 0x8E);
  idt_set_gate(42, (udword)irq10, 0x08, 0x8E);
  idt_set_gate(43, (udword)irq11, 0x08, 0x8E);
  idt_set_gate(44, (udword)irq12, 0x08, 0x8E);
  idt_set_gate(45, (udword)irq13, 0x08, 0x8E);
  idt_set_gate(46, (udword)irq14, 0x08, 0x8E);
  idt_set_gate(47, (udword)irq15, 0x08, 0x8E);

  idt_flush((udword)&idt_pointer);
}

static void idt_set_gate(ubyte index, udword base, uword selector, ubyte flags)
{
  idt_entries[index].base_low = base & 0xFFFF;
  idt_entries[index].base_high = (base >> 16) & 0xFFFF;

  idt_entries[index].selector = selector;
  idt_entries[index].always0 = 0;

  idt_entries[index].flags = flags /* | 0x60 */;
}

