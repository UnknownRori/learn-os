format elf
public start

section '.multiboot' align 4
    dd 0x1BADB002             ; magic number
    dd 0x00                   ; flags
    dd -(0x1BADB002 + 0x00)   ; checksum

section '.text' align 4
extrn kmain

start:
    mov esp, stack_top

    call kmain

    jmp $

section '.bss' align 16
    rb (1024*16)
stack_top:
