use32
format elf

section '.text' executable
public keyboard_stub

extrn keyboard_handler

keyboard_stub:
    cli

    pusha
    push ds
    push es
    push fs
    push gs

    call keyboard_handler
    mov al, 0x20
    out 0x20, al  ; Master PIC EOI

    pop gs
    pop fs
    pop es
    pop ds
    popa

    sti
    iret
