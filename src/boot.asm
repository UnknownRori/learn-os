use32
format elf
public start

section '.multiboot' align 4
    dd 0x1BADB002             ; magic number
    dd 0x00                   ; flags
    dd -(0x1BADB002 + 0x00)   ; checksum

section '.text' align 4
extrn kmain

start:
    ; Arguments from GRUB
    ; EAX = multiboot magic
    ; EBX = pointer to multiboot_info struct

    ; Since GRUB handle our bootloader we can focus on preparing calling our 
    ; Kernel code in C since C uses stack we need to set it up first
    ; And GRUB already set up 32-bit protected mode so the stack is on
    ; ESP register
    mov esp, stack_top

    push eax
    push ebx
    call kmain

    ; Hang the entire kernel with infinte loop
    jmp $

section '.bss' align 16
    rb (1024*16)
stack_top:
