use32
format elf

section '.text' executable
public isr_stub_table

extrn exception_handler

macro ISR_STUB num {
isr_stub_#num:
    cli
    pusha
    push num
    call exception_handler
    popa
    sti
    iret
}

rept 32 i {
    ISR_STUB i
}

isr_stub_table:
rept 32 i {
    dd isr_stub_#i
}
