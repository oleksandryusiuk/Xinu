[bits 16]
print_string:
	pusha

start:
        mov al, [bx]
        cmp al, 0
        je the_end
        mov ah, 0x0e ; teletype routine
        int 0x10
        inc bx
        jmp start

the_end:
	popa
	ret

