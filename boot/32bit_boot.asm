
[org 0x7c00]
  KERNEL_OFFSET equ 0x1000

  mov [BOOT_DRIVE], dl

  mov bp, 0x9000
  mov sp, bp

  mov bx, MSG_REAL_MODE
  call print_string
  call print_nl

  call load_kernel

  call switch_to_pm


  jmp $

%include "boot/boot_print.asm"
%include "boot/disk_load.asm"
%include "boot/gdt.asm"
%include "boot/32bit_print.asm"
%include "boot/32bit-switch.asm"
[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL
  call print_string

  mov bx, KERNEL_OFFSET		; set parameters to disk load routine
  mov dh, 26			; so we load first 26 sectors of disk
  mov dl, [BOOT_DRIVE]		; (excluding boot sector) from boot disk
  call disk_load		; to address KERNEL_OFFSET
  ret
load_task_register:
  mov ax, 0x20
  ltr ax
  ret

[bits 32]


BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_string_pm
  
  call KERNEL_OFFSET		; jump to kernel.
  jmp $

; DATA
MSG_REAL_MODE db "Started successfully in 16-bit Real mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bit protected mode", 0
BOOT_DRIVE db 0
MSG_LOAD_KERNEL db "loading kernel into memory", 0
; bootsector
times 510-($-$$) db 0
dw 0xaa55
