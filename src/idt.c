#include <stdint.h>

#include "include/idt.h"
#include "include/common.h"
#include "include/serial.h"
#include "include/timer.h"

#define RORI_LOG
#include "include/log.h"

static idt_entry_t idt[256] __attribute__((aligned(0x10))) = {0} ;
static idtr_t idtr;

/// Exception handler stub from assembly code [stub_exception.asm]
extern void* isr_stub_table[];
extern void exception_stub(void);


void exception_handler(void);

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    uint32_t addr = (uint32_t)isr;
    idt[vector].isr_low   = addr & 0xFFFF;
    idt[vector].kernel_cs = 0x08;
    idt[vector].reserved  = 0;
    idt[vector].attributes = flags;
    idt[vector].isr_high  = (addr >> 16) & 0xFFFF;
}

/// Remaping the 8259 Programmable interrupt controller (PIC) so it doesnt collide with IRQ
/// So it start at 0x20 (since 0-32 is exception handler)
///
/// # References
/// -  https://wiki.osdev.org/8259_PIC
static inline void pic_remap(void)
{
    asm volatile("cli");

    outb(0x20, 0x11); // Start initialization sequence (ICW1) for Master PIC (port 0x20 = command)
    outb(0xA0, 0x11); // Same for Slave PIC (port 0xA0 = command)
    outb(0x21, 0x20); // Master PIC’s IRQs will start at 0x20
    outb(0xA1, 0x28); // Slave PIC’s IRQs will start at 0x28
    outb(0x21, 0x04); // Slave PIC’s IRQs will start at 0x28
    outb(0xA1, 0x02); // Tell Master PIC: there’s a slave on IRQ2
    outb(0x21, 0x01); // Master PIC in 8086/88 (MCS-80/85) mode
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

    /// Store the index and enable interrupt
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}

/// Exception handler
/// TODO : Make more info what is getting trigerred
__attribute__((noreturn))
void exception_handler(void) {
    LOG("[-] Exception Handler Hit!")
    HALT;
}
