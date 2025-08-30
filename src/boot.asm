use32
format elf
public start

FLAGS = (0x03 or (1 shl 2))

section '.multiboot' align 4
    dd 0x1BADB002               ; magic number
    dd FLAGS                    ; flags
    dd -(0x1BADB002 + FLAGS)    ; checksum

    dd 0                        ; header_addr (unused)
    dd 0                        ; load_addr (unused)
    dd 0                        ; load_end_addr (unused)
    dd 0                        ; bss_end_addr (unused)
    dd 0                        ; entry_addr (unused)

    dd 0                        ; Mode Type
    dd 1366                     ; Width
    dd 768                      ; Height
    dd 32                       ; Depth

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
