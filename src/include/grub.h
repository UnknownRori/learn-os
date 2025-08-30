#pragma once

#ifndef RORI_GRUB_H
#define RORI_GRUB_H

#include "types.h"

#include <stdint.h>

typedef struct multiboot_info {
    uint32_t flags;

    // Valid if (flags[0] == 1)
    uint32_t mem_lower;
    uint32_t mem_upper;

    // Valid if (flags[1] == 1)
    uint32_t boot_device;

    // Valid if (flags[2] == 1)
    uint32_t cmdline;

    // Valid if (flags[3] == 1)
    uint32_t mods_count;
    uint32_t mods_addr;

    // Valid if (flags[4] or flags[5] set)
    uint32_t syms[4];

    // Valid if (flags[6] == 1)
    uint32_t mmap_length;
    uint32_t mmap_addr;

    // Valid if (flags[7] == 1)
    uint32_t drives_length;
    uint32_t drives_addr;

    // Valid if (flags[8] == 1)
    uint32_t config_table;

    // Valid if (flags[9] == 1)
    uint32_t boot_loader_name;

    // Valid if (flags[10] == 1)
    uint32_t apm_table;

    // Valid if (flags[11] == 1)
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    // Valid if (flags[12] == 1) -- Framebuffer info
    uint64_t framebuffer_addr;   // MUST be 64-bit
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;
    uint16_t reserved;
} __attribute__((packed)) multiboot_info_t;

#endif
