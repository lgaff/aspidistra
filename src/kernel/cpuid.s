	;; Test if cpuid is supported by the CPU

	;; If cpuid is supported, then bit 20 in eflags will be writable.
global cpu_supports_cpuid
cpu_supports_cpuid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 0x20000
	push eax
	popfd
	pushfd
	pop eax
	xor eax, ecx
	shr eax, 21
	and eax, 1
	push ecx
	popfd
	ret

global cpuid_string
cpuid_string:	
	push ebp
	mov ebp, esp
	pusha
		
	mov eax, [ebp+8] 	; cpuid command
	cpuid			; e[bcd]x are all clobbered by this.
	mov eax, [ebp+12]	; pointer to 12 byte buffer where we can shove the vendor id
	mov [eax], ebx
	mov [eax + 4], edx
	mov [eax + 8], ecx
	popa
	leave
	ret