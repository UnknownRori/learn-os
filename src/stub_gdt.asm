use32
format elf

section '.text' executable
public gdt_flush

gdt_flush:
    mov     eax, [esp+4]
    lgdt    [eax]

    jmp     0x08:flush_cs

flush_cs:
    ; load data segment registers with selector 0x10 (GDT entry 2)
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    ret
