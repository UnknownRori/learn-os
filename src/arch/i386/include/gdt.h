#pragma once

#ifndef RORI_GDT_H
#define RORI_GDT_H

#include "../../../include/types.h"

typedef struct gdt_entry_t
{
    u16    limit_low;
    u16    base_low;
    u8     base_mid;
    u8     access;
    u8     granularity;
    u8     base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdtr_entry_t
{
    uint16_t	limit;
    uint32_t	base;
} __attribute__((packed)) gdtr_entry_t;

void gdt_init();

#endif
