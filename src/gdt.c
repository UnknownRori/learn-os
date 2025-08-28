#include "include/gdt.h"

static gdt_entry_t gdt[3];
static gdtr_t gdtr;

/// Assembly stub
extern void gdt_flush(void* gdtr_ptr);

static void gdt_set(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[i].limit_low    = (uint16_t)(limit & 0xFFFF);
    gdt[i].base_low     = (uint16_t)(base  & 0xFFFF);
    gdt[i].base_mid     = (uint8_t)((base  >> 16) & 0xFF);
    gdt[i].access       = access;
    gdt[i].granularity  = (uint8_t)(((limit >> 16) & 0x0F) | (gran & 0xF0));
    gdt[i].base_high    = (uint8_t)((base  >> 24) & 0xFF);
}

static void gdt_install(void)
{
    // 0: null
    gdt_set(0, 0, 0, 0, 0);

    // 1: kernel code, flat 4GB
    // access = 0x9A (present|ring0|code|executable|readable)
    // gran   = 0xCF (4K gran|32-bit|limit high nibble=0xF)
    gdt_set(1, 0, 0xFFFFF, 0x9A, 0xCF);

    // 2: kernel data, flat 4GB
    // access = 0x92 (present|ring0|data|writable)
    gdt_set(2, 0, 0xFFFFF, 0x92, 0xCF);

    gdtr.limit = (uint16_t)(sizeof(gdt) - 1);
    gdtr.base  = (uint32_t)&gdt[0];

    gdt_flush(&gdtr);
}

void gdt_init(void)
{
    asm volatile("cli");
    gdt_install();
    asm volatile("sti");
}
