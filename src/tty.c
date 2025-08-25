#include <stdint.h>

#include "include/memory.h"
#include "include/tty.h"
#include "include/vga.h"

static uint8_t x = 0;
static VGA_COLOR fg = VGA_WHITE;
static VGA_COLOR bg = VGA_BLACK;
static volatile VGAEntry buffer[VGA_HEIGHT][VGA_WIDTH] = {0};

inline static void clear_line()
{
   for (int8_t col = 0; col < VGA_WIDTH; ++col) {
        buffer[VGA_HEIGHT - 1][col] = (VGAEntry){
            .ch = ' ',
            .color = vga_entry_color(fg, bg)
        };
   }
}

inline static void new_line() {
    x = 0;
    for (uint8_t row = 2; row < VGA_HEIGHT; ++row) {
        for (uint8_t col = 0; col < VGA_WIDTH; ++col) {
            buffer[row - 1][col] = buffer[row][col];
        }
    }
    clear_line();
    tty_flush();
}

void tty_init()
{
    memset((void*)buffer, 0, sizeof(buffer));
    x = 0;
}

void tty_flush()
{
    vga_mem_set((VGAEntry*)buffer, 1);
}

void tty_set_color(VGA_COLOR fg2, VGA_COLOR bg2)
{
    fg = fg2;
    bg = bg2;
}

void tty_putchar(char c)
{
    if (c == '\n') {
        new_line();
    } else if (c == '\b') {
        uint8_t color = vga_entry_color(fg, bg);

        x -= 1;
        buffer[VGA_HEIGHT - 1][x] = (VGAEntry) {
            .ch = ' ',
            .color = color,
        };

    } else {
        uint8_t color = vga_entry_color(fg, bg);

        buffer[VGA_HEIGHT - 1][x] = (VGAEntry) {
            .ch = c,
            .color = color,
        };

        x += 1;
        if (x >= VGA_WIDTH) {
            new_line();
        }
    }
    vga_set_cursor(VGA_HEIGHT - 1, x);
}
void tty_write(const char* str)
{
    while (*str) {
        tty_putchar(*str);
        str += 1;
    }
}
void tty_writeln(const char* str)
{
    tty_write(str);
    tty_putchar('\n');
}
