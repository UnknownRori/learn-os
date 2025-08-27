/// VGA.h - v0.0
/// This file handle raw interface with VGA CRT, currently on 80×25 text mode.
///
/// # I/O Port:
/// - 0x3D4 -> VGA CRT Index Controller Port
/// - 0x3D5 -> VGA CRT Data Controller Port
///
/// # Status:
/// - Properly abstract the buffer part
/// - Need to jump to 320x200 linear 256-color mode
///     - abstracting text glyph
///     - keeping the API more or less the same
///
/// # References:
/// - https://wiki.osdev.org/VGA_Hardware
/// - https://wiki.osdev.org/Text_Mode_Cursor
/// - https://www.reddit.com/r/osdev/comments/qyd0w8/problems_understanding_vga_registers_0x3d4_and/

#pragma once

#ifndef RORI_OS_VGA_H
#define RORI_OS_VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/// Color code of 80×25 text mode are used, in actual it only need 4 bit
typedef enum {
    VGA_BLACK           = 0,
    VGA_BLUE            = 1,
    VGA_GREEN           = 2,
    VGA_CYAN            = 3,
    VGA_RED             = 4,
    VGA_MAGENTA         = 5,
    VGA_BROWN           = 6,
    VGA_LIGHT_GREY      = 7,
    VGA_DARK_GREY       = 8,
    VGA_LIGHT_BLUE      = 9,
    VGA_LIGHT_GREEN     = 10,
    VGA_LIGHT_CYAN      = 11,
    VGA_LIGHT_RED       = 12,
    VGA_LIGHT_MAGENTA   = 13,
    VGA_LIGHT_BROWN     = 14,
    VGA_WHITE           = 15,
} VGA_COLOR;

/// This struct represent how data are stored on VGA buffer memory as 16 bit (2 byte)
typedef struct {
    uint8_t ch;
    uint8_t color;
} __attribute__((packed)) VGAEntry;

/// Pack 2 [`VGA_COLOR`] into single [`uint8_t`]
/// @params     VGA_COLOR fg
/// @params     VGA_COLOR bg
/// @returns void
uint8_t vga_entry_color(VGA_COLOR fg, VGA_COLOR bg);

/// Set the VGA Buffer from src buffer provided
/// It accept height to skip how many line from top
/// @params     VGAENtry* src
/// @params     uint8_t   height
/// @returns void
void vga_mem_set(VGAEntry* src, uint8_t height);

/// Initialize the VGA C module to allow interfacing with VGA chip
/// by setting up necessary cmmand to I/O Port
/// @params void
void vga_init(void);

/// Clear the entire VGA buffer with color put using [`vga_set_color`]
/// @params void
void vga_clear(void);

/// Put character entry with color that already packed on specific X and Y coordinate
/// @params char    c
/// @params uint8_t color
/// @params size_t  x
/// @params size_t  y
/// @params void
void vga_put_entry_at(char c, uint8_t color, size_t x, size_t y);

/// Put string into buffer along with color that already packed on specific X and Y coordinate
/// @params const char*     str
/// @params uint8_t         color
/// @params size_t          x
/// @params size_t          y
/// @params void
void vga_put_str(const char* str, uint8_t color, size_t x, size_t y);

/// Set color for [`vga_clear`] function
/// @params uint8_t color
/// @params void
void vga_setcolor(uint8_t color);

/// Set VGA cursor position
/// @params uint16_t         row
/// @params uint16_t         col
/// @params void
void vga_set_cursor(uint16_t row, uint16_t col);

#endif
