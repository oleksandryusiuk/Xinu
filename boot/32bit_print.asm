[bits 32]
; accepts string address at ebx and prints it
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_string_pm_loop:
	mov al, [ebx]
	mov ah, WHITE_ON_BLACK

	cmp al, 0
	je done
	
	mov [edx], ax
	add ebx, 1
	add edx, 2

	jmp print_string_pm_loop

done:
	popa
	ret

print_nl:
	pusha

	mov ah, 0x0e	; teletype routine
	mov al, 0x0a	; newline char
	int 0x10
	mov al, 0x0d
	int 0x10
	popa
	ret
