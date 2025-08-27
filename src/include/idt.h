/// IDT.h - v0.0
/// This file handle Interrupt Descriptor Table.
///
/// # Status:
/// - Expand Exception Handling to account type of exception (ie double fault, page fault, etc).
///
/// # References:
/// - https://wiki.osdev.org/IDT
/// - https://wiki.osdev.org/IRQ
/// - https://wiki.osdev.org/Interrupts
/// - https://wiki.osdev.org/8259_PIC

#pragma once

#ifndef RORI_OS_IDT_H
#define RORI_OS_IDT_H

#include <stdint.h>

typedef struct {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
    uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t     reserved;     // Set to zero
    uint8_t     attributes;   // Type and attributes; see the IDT page
    uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t	limit;
    uint32_t	base;
} __attribute__((packed)) idtr_t;

/// Setup entry an entry inside Interrupt Descriptor Table
/// It require [`isr`] to point assembly code before jumping to C code
/// @params uint8_t vector
/// @params void*   isr
/// @params uint8_t flags
/// @returns void
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

/// Setup Interrupt Descriptor Table and enable interrupt.
/// and automatically register timer interrupt.
/// @return voids
void idt_init(void);

#endif 
