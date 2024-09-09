; load dh sectors to es:bx from drive dl
[bits 16]
disk_load:
	push dx		; push dx to stack as it is number of 
			; sectors we request to read, so that
			; we can later compare it to the number
			; of sectors actually read.

	mov ah, 0x02	; bios read sector function
	mov al, dh	; number (dh) of sectors we want to read
	mov ch, 0x00	; cylinder 0
	mov dh, 0x00	; track 0
	mov cl, 0x02	; sector 2 (since sector hase a base 1,
			; sector 1 is boot, so next is sector 2.
	int 0x13	; call bios read disk routine

	jc disk_error	; jump to disk error function
	pop dx		; get dx from stack
	cmp dh, al	; al is set to number of sectors actually
			; read, so if requested number of sectors 
			; isnt equal to number of sectors read
			; there is error
	jne disk_error	;	
	ret		

disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

; DATA
DISK_ERROR_MSG:
	db "disk read error!", 0	
