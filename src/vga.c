#include <stdint.h>

#include "include/vga.h"
#include "include/io.h"
#include "include/assert.h"
#include "include/memory.h"

static uint8_t color;
static volatile VGAEntry* buffer = NULL;

uint8_t vga_entry_color(VGA_COLOR fg, VGA_COLOR bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}
void vga_set_cursor(uint16_t row, uint16_t col) {
    uint16_t pos = row * VGA_WIDTH + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void vga_mem_set(VGAEntry* src, uint8_t height)
{
    assert(src != NULL);

    memcpy(
        (void*)(buffer + (VGA_WIDTH * height)), 
        src + height * VGA_WIDTH, 
        VGA_WIDTH * (VGA_HEIGHT - height) * sizeof(VGAEntry)
    );
}

/// Setup VGA  default configuration with 80×25 text
/// 0x3D4   -> VGA CRT Index Controller Port
/// 0x3D5   -> VGA CRT Data Controller Port
/// 0xB8000 -> VGA Buffer that store text along it's color
///
/// @returns void
void vga_init(void) {
    color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    buffer = (VGAEntry*)0xB8000;

    // Setup the cursor shape
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
    vga_set_cursor(0, 0);

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
    if (buffer == NULL) return;

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
