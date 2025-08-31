#include "include/idt.h"
#include "include/io.h"
#include "../../include/cpu.h"
#include "../../include/memory.h"

static idt_entry_t idt[255];
static idtr_t idtr;

/// Remaping the 8259 Programmable interrupt controller (PIC) so it doesnt collide with IRQ
/// So it start at 0x20 (since 0-32 is exception handler)
///
/// # References
/// -  https://wiki.osdev.org/8259_PIC
static inline void pic_remap(void)
{
    outb(0x20, 0x11); // Start initialization sequence (ICW1) for Master PIC (port 0x20 = command)
    outb(0xA0, 0x11); // Same for Slave PIC (port 0xA0 = command)
    outb(0x21, 0x20); // Master PIC’s IRQs will start at 0x20
    outb(0xA1, 0x28); // Slave PIC’s IRQs will start at 0x28
    outb(0x21, 0x04); // Slave PIC’s IRQs will start at 0x28
    outb(0xA1, 0x02); // Tell Master PIC: there’s a slave on IRQ2
    outb(0x21, 0x01); // Master PIC in 8086/88 (MCS-80/85) mode
    outb(0xA1, 0x01);
}

/// Setup entry an entry inside Interrupt Descriptor Table
/// It require [`isr`] to point assembly code before jumping to C code
/// @params uint8_t vector
/// @params void*   isr
/// @params uint8_t flags
/// @returns void
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    uint32_t addr = (uint32_t)isr;
    idt[vector].isr_low   = addr & 0xFFFF;
    idt[vector].kernel_cs = 0x08;
    idt[vector].reserved  = 0;
    idt[vector].attributes = flags;
    idt[vector].isr_high  = (addr >> 16) & 0xFFFF;
}

/// Setup Interrupt Descriptor Table and enable interrupt.
/// and automatically register timer interrupt.
/// @return voids
void idt_init()
{
    pic_remap();
    memset(&idt, 0, sizeof(idt));
}

/// Setup Interrupt Descriptor Table.
/// @return voids
void idt_load(void)
{
    idtr.limit = (u16)sizeof(idt_entry_t) * 256 - 1;
    idtr.base = (u32)&idt;

    /// Store the index and enable interrupt
    __asm__ volatile ("lidt %0" : : "m"(idtr));
}
