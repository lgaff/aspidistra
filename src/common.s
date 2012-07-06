	.file	"common.c"
	.text
	.globl	memset
	.type	memset, @function
memset:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movl	%edx, -32(%rbp)
	movb	%al, -28(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movzbl	-28(%rbp), %edx
	movb	%dl, (%rax)
	addq	$1, -8(%rbp)
	subl	$1, -32(%rbp)
.L2:
	cmpl	$0, -32(%rbp)
	jne	.L3
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	memset, .-memset
	.section	.rodata
	.align 8
.LC0:
	.string	"OH HOW DID THIS GET HERE I AM NOT GOOD WITH COMPUTER"
	.text
	.globl	dump_registers
	.type	dump_registers, @function
dump_registers:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	movl	$.LC0, %esi
	movl	$15, %edi
	call	console_putstr
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	dump_registers, .-dump_registers
	.ident	"GCC: (Debian 4.7.1-2) 4.7.1"
	.section	.note.GNU-stack,"",@progbits
