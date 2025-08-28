#include "include/common.h"
#include "include/idt.h"
#include "include/keyboard.h"
#include "include/serial.h"
#include "include/timer.h"
#include "include/tty.h"
#include "include/vga.h"
#include "include/gdt.h"

#define RORI_LOG
#include "include/log.h"

void init()
{
    serial_init();
    LOG("[+] Serial initialized");

    gdt_init();
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

void draw_header(const char* title)
{
    // TODO: Dynamically set the text position
    for (int i = 0; i < VGA_WIDTH; i++) {
        vga_put_entry_at(' ', vga_entry_color(VGA_WHITE, VGA_BLUE), i, 0);
    }
    vga_put_str(title, vga_entry_color(VGA_WHITE, VGA_BLUE), 30, 0);

}

void kmain(void)
{
    init();

    draw_header("UnknownRori's OS");

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
