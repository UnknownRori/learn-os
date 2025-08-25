#include "include/common.h"
#include "include/idt.h"
#include "include/keyboard.h"
#include "include/serial.h"
#include "include/timer.h"
#include "include/tty.h"
#include "include/vga.h"

#define RORI_LOG
#include "include/log.h"

void init()
{
    serial_init();
    LOG("[+] Serial initialized");

    idt_init();
    keyboard_init();
    LOG("[+] Setup interrupts");

    vga_init();
    vga_clear();
    LOG("[+] VGA Initialized");

    tty_init();
    LOG("[+] tty Initialized");

    LOG("[+] Booting");

    tty_write("[+] Loading Rori OS Project");
    serial_write("[+] Loading Rori OS Project");
    for (int i = 0; i < 4;i ++) {
        tty_write(".");
        serial_write(".");
        tty_flush();
        sleep(100);
    }

    serial_write("\n------------------------\n");
    tty_writeln("\n------------------------\n");
}

void kmain(void)
{
    init();

    tty_write("$ ");
    tty_flush();
    while (1) {
        char c = getch();
        tty_putchar(c);
        if (c == '\n') {
            tty_write("$ ");
        }
        tty_flush();
    }

    HALT;
}
