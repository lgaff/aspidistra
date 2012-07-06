;;; Stub.s is the entry point after booting from GRUB. From here we'll initialise the cpu environment in this order:
;;; * GDT for a flat address space (implicitly disabling segmentation in favor of paging)
;;; * IDT loading
;;; * remap IRQs 0-15 to ISR 32-47
;;; * Initialise the ISR vectors using a common handler (that does nothing)
;;; * register interrupt handlers for important interrupts (for now, this means page faults)
;;; * Load a page directory with 4 meg pages, id-mapping the first page for now
;;; * enable paging and long jump to 3.01 GiB (we need to be careful until this is done)
;;; paging and vmem, and temporary interrupt handler stubs.
;;; so everything here needs to be either translated to physical address 1MiB, or position independant.


global _loader
extern _main
	
MODULEALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text
align 4
mBoot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

loader equ (_loader - 0xC0000000)
global loader

_loader:
	