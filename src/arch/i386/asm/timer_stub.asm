use32
format elf

section '.text' executable
public timer_stub

extrn timer_handler

timer_stub:
    cli
    pusha
    call timer_handler
    mov al, 0x20
    out 0x20, al  ; Master PIC EOI
    popa
    sti
    iret
