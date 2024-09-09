gdt_start:

; NULL segment (32 bits)
gdt_null:
	dd 0x0
	dd 0x0

; base =0 x0 , limit =0 xfffff ,
; 1 st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
; 2 nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b

gdt_code:
	  ; base = 0x0, limit = 0xfffff
	  ; 1st flag: (present: always true for existing segments), privilege 00(highest), descriptor type - 1 (should be 1 if this is code/data segment) -> 1001b
	  ; type flags: code - 1(is it code segment) conforming (can this code be executed from lower privilege levels - no) 0 \n
	  ; readable 1 (to read constants) accessed 0 (cpu automatically sets it to 1 when uses it) -> 1010b
	  ; 2nd flags: granularity 1 (multiplies limit by 0x1000) 32bit mem - 1, 64bits 0, AVL 0. -> 1100b
	dw 0xffff	; limit (bit 0-15)
	dw 0x0		; base (bits 0-15)
	db 0x0		; base (bits 16-23)
	db 10011010b	; 1st flags, type flags
	db 11001111b	; 2st flags, Limit (bits 16-19)
	db 0x0		; Base (bits 24-31)

gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

tss_descriptor:
        dw tss + 3
        dw tss
        dw 0x8900
        dw 0x0000

gdt_end:
	

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start
; calculate useful constants for the locations of code and data segments, -> null seg at 0x00, code seg at 0x08, data seg at 0x10 (16th byte)
CODE_SEG equ gdt_code - gdt_start 
DATA_SEG equ gdt_data - gdt_start
tss:
  dd 0
