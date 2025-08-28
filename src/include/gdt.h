/// GDT.h - v0.0
/// This file handle Global Descriptor Table.
///
/// # Status:
/// - 
///
/// # References:
/// - https://wiki.osdev.org/Global_Descriptor_Table
/// - https://wiki.osdev.org/GDT_Tutorial

#pragma once

#ifndef RORI_OS_GDT_H
#define RORI_OS_GDT_H

#include <stdint.h>

typedef struct {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t	limit;
    uint32_t	base;
} __attribute__((packed)) gdtr_t;

/// Setup Global Descriptor Table
/// @return voids
void gdt_init(void);

#endif 
