format elf
public start

section '.multiboot' align 4
    dd 0x1BADB002             ; magic number
    dd 0x00                   ; flags
    dd -(0x1BADB002 + 0x00)   ; checksum

section '.text' align 4
start:
    mov edi, 0xB8000          ; VGA memory
    mov ax, 0x1F48            ; 'H' with white on blue background
    stosw
    mov ax, 0x1F69            ; 'i'
    stosw

    jmp $
