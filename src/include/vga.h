#pragma once

#ifndef RORI_OS_VGA_H
#define RORI_OS_VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_LIGHT_BROWN = 14,
    VGA_WHITE = 15,
} VGA_COLOR;

typedef struct {
    uint8_t ch;
    uint8_t color;
} __attribute__((packed)) VGAEntry;

uint8_t vga_entry_color(VGA_COLOR fg, VGA_COLOR bg);
void vga_mem_set(VGAEntry* src, uint8_t height);

void vga_init(void);
void vga_clear(void);
void vga_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void vga_put_str(const char* str, uint8_t color, size_t x, size_t y);
void vga_setcolor(uint8_t color);
void vga_set_cursor(uint16_t row, uint16_t col);

#endif
