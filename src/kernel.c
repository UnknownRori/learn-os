#include "include/types.h"
#include "include/grub.h"
#include "include/serial.h"
void kmain(multiboot_info_t* mb_info, uint32_t magic) 
{
    if (magic != 0x2BADB002) {
        asm volatile("hlt");
    }

    serial_init();
    serial_writeln("Hello, world!");
    serial_writeln("From Kernel");


    asm volatile("hlt");
}
