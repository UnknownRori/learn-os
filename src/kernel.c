#include "include/common.h"
#include "include/serial.h"
#include "include/tty.h"
#include "include/vga.h"

void kmain(void) {
    serial_init();
    serial_writeln("[+] Serial initialized");
    vga_init();
    vga_clear();

    vga_put_str("[+] VGA Initialized", vga_entry_color(VGA_WHITE, VGA_BLACK), 0, 0);
    tty_init();

    serial_writeln("[+] Booting...");
    tty_writeln("[+] Booting...");
    tty_writeln("[+] Loading Rori OS Project...");

    HALT;
}
