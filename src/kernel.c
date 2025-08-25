#include "include/common.h"
#include "include/idt.h"
#include "include/serial.h"
#include "include/timer.h"
#include "include/tty.h"
#include "include/vga.h"

#define RORI_LOG
#include "include/log.h"

void kmain(void) {
    serial_init();
    LOG("[+] Serial initialized");

    idt_init();
    LOG("[+] Setup interrupts");

    vga_init();
    vga_clear();
    LOG("[+] VGA Initialized");

    tty_init();
    LOG("[+] tty Initialized");

    LOG("[+] Booting");

    sleep(1000);

    LOG("[+] Loading Rori OS Project...");


    HALT;
}
