#include "include/interrupt.h"
#include "include/timer.h"
#include "include/types.h"
#include "include/grub.h"
#include "include/serial.h"
#include "include/fb.h"

void kmain(multiboot_info_t* mb_info, uint32_t magic) 
{
    if (magic != 0x2BADB002) {
        asm volatile("hlt");
    }

    serial_init();
    interrupt_init();
    serial_writeln("Hello, world!");
    sleep(1000);
    serial_writeln("From Kernel");

    framebuffer_t* fb = fb_init(mb_info);

    u32 x = 0;
    u32 y = 0;
    u32 xv = 5;
    u32 yv = 5;
    u32 color = 0xFF0000;

    u32 rect_w = 100;
    u32 rect_h = 100;

    while (1) {
        fb_clear(0x222222);
        fb_draw_rect(x, y, rect_w, rect_h, color);
        fb_commit();

        x += xv;
        y += yv;

        if (x + rect_w >= fb->width || x <= 0) {
            xv = -xv;
        }

        if (y + rect_h >= fb->height || y <= 0) {
            yv = -yv;
        }

        sleep(16);
    }

    asm volatile("hlt");
}
