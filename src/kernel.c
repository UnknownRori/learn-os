#include "include/common.h"
#include "include/serial.h"
#include "include/vga.h"

const char* msg = "Loading Rori OS Project...";

void kmain(void) {
    vga_init();
    vga_clear();
    serial_init();

    serial_write("Hello world!");

    vga_put_str(msg, VGA_GREEN, 2, 2);

    HALT;
}
