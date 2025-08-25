#include "include/vga.h"
#include <string.h>
#include "include/assert.h"

static uint8_t color;
static volatile VGAEntry* buffer;

uint8_t vga_entry_color(VGA_COLOR fg, VGA_COLOR bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

void vga_mem_set(VGAEntry* src)
{
    buffer[0] = src[0];
    memcpy((void*)buffer, src, VGA_WIDTH * VGA_HEIGHT * sizeof(VGAEntry));
}

void vga_init(void) {
    color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    buffer = (VGAEntry*)0xB8000;
    vga_clear();
}

void vga_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            buffer[y * VGA_WIDTH + x] = (VGAEntry) {
                .ch = ' ',
                .color = color,
            };
        }
    }
}

void vga_put_entry_at(char c, uint8_t col, size_t x, size_t y) {
    assert(x <= VGA_WIDTH);
    assert(y <= VGA_HEIGHT);

    buffer[y * VGA_WIDTH + x] = (VGAEntry) {
        .ch = c,
        .color = col,
    };
}

void vga_put_str(const char* str, uint8_t color, size_t x, size_t y)
{
    while (*str != 0) {
        if (*str >= 0x20 && *str <= 0x7e) {
            vga_put_entry_at(*str, color, x, y);
        } else if (*str == '\n') {
            x = 0;
            y += 1;
        } else {
            vga_put_entry_at(0xfe, color, x, y);
        }
        str += 1;
        x += 1;
    }
}

void vga_setcolor(uint8_t col) {
    color = col;
}
