#include "include/common.h"
#include "include/vga.h"

void kmain(void) {
    const char* msg = "Loading Rori OS Project...";
    vga_init();
    vga_clear();
    vga_setcolor(VGA_RED);
    vga_put_str(msg, VGA_GREEN, 2, 2);
    vga_put_str(msg, VGA_GREEN, 100, 100);
    vga_put_str(msg, VGA_GREEN, 4, 4);

    HALT;
}
