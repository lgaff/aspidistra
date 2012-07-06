;;; low-level GDT manipulation routines go here.
section .text
global gdt_flush

gdt_flush:
	mov eax, [esp + 4]
	lgdt [eax]

	;; We've loaded the GDT pointer passed from C land, now we need to reset all the data segment selectors to avoid a triple fault
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	;; now far jump to get into the right segment.
	jmp 0x08:.flush
.flush:
	ret

global idt_flush

idt_flush:
	mov eax, [esp + 4]
	lidt [eax]
	ret