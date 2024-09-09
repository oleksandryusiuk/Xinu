[bits 16]

switch_to_pm:
	cli			; clear interrupts which bios set

	lgdt [gdt_descriptor]	; load gdt 

  	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm	; far jump to flush all pipelining instructions

[bits 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov gs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM
