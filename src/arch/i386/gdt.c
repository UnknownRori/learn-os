#include "include/gdt.h"

static gdt_entry_t gdt[3];
static gdtr_entry_t gdtr;

static void gdt_set(int i, u32 base, u32 limit, u8 access, u8 gran);
extern void gdt_flush(void* gdtr);

void gdt_init()
{
    // Null segment
    gdt_set(0, 0, 0, 0, 0);

    // Kernel code segment
    gdt_set(1, 0, 0xFFFF, 0x9A, 0xCF);

    // Kernel data segment
    gdt_set(2, 0, 0xFFFF, 0x92, 0xCF);

    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (u32)&gdt[0];
    gdt_flush(&gdtr);
}


static void gdt_set(int i, u32 base, u32 limit, u8 access, u8 gran)
{
    gdt[i].limit_low = limit & 0xFFFF;
    gdt[i].base_low = base & 0xFFFF;
    gdt[i].base_mid = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;
    gdt[i].access = access;
    gdt[i].granularity = ((limit > 16) & 0x0F) | (gran & 0xF0);
}
