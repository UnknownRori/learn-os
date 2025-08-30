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

    uint32_t* fb = (uint32_t*)mb_info->framebuffer_addr;
    u32 width = mb_info->framebuffer_width;
    u32 height = mb_info->framebuffer_height;
    for (u32 row = 0; row < height; row++) {
        for (u32 col = 0; col < width; col++) {
            fb[row * width + col] = 0xFFFFFF;
        }
    }

    asm volatile("hlt");
}
