#include <stdint.h>

#include "include/idt.h"
#include "include/common.h"
#include "include/serial.h"
#include "include/timer.h"

#define RORI_LOG
#include "include/log.h"

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256] __attribute__((aligned(8))) = {0} ;
static idtr_t idtr;

extern void* isr_stub_table[];
extern void exception_stub(void);


void exception_handler(void);
void timer_handler(void);
static inline uint16_t read_cs(void) {
    uint16_t sel;
    asm volatile ("mov %%cs, %0" : "=r"(sel));
    return sel;
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    uint32_t addr = (uint32_t)isr;
    idt[vector].isr_low   = addr & 0xFFFF;
    idt[vector].kernel_cs = read_cs();
    idt[vector].reserved  = 0;
    idt[vector].attributes = flags;
    idt[vector].isr_high  = (addr >> 16) & 0xFFFF;
}

static inline void pic_remap(void)
{
    asm volatile("cli");

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
}


void idt_init()
{
    pic_remap();

    for (int i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i], 0x8E);
    }
    timer_init();

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}

__attribute__((noreturn))
void exception_handler(void) {
    LOG("[-] Exception Handler Hit!")
    HALT;
}
