#include "include/common.h"
#include "include/serial.h"
#include "include/tty.h"
#include "include/vga.h"

#define RORI_LOG
#include "include/log.h"

void kmain(void) {
    serial_init();
    LOG("[+] Serial initialized");

    vga_init();
    vga_clear();
    LOG("[+] VGA Initialized");

    tty_init();
    LOG("[+] tty Initialized");

    LOG("[+] Booting");
    LOG("[+] Loading Rori OS Project...");

    HALT;
}
