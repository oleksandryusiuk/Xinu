[bits 16]
print_hex:
	pusha
	mov cx, 0
; let us have 0x1a3c as input in dx
start_hex:
	mov ax, dx
	cmp cx, 4
	je hex_final
	and ax, 0x000f
	add al, 0x30
	cmp al, 0x39
	jle step2
	add al, 0x07
step2:
	mov bx, HEX_OUT + 5
	sub bx, cx
	mov [bx], al
	shr dx, 4	
	inc cx
	jmp start_hex
	

hex_final:
	mov bx, HEX_OUT
	call print_string
	popa
	ret
	

; DATA
HEX_OUT:
	db '0x0000', 0
