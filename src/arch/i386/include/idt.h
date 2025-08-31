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

#include "../../../include/types.h"

typedef struct {
    u16    isr_low;      // The lower 16 bits of the ISR's address
    u16    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    u8     reserved;     // Set to zero
    u8     attributes;   // Type and attributes; see the IDT page
    u16    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    u16	limit;
    u32	base;
} __attribute__((packed)) idtr_t;

/// Setup entry an entry inside Interrupt Descriptor Table
/// It require [`isr`] to point assembly code before jumping to C code
/// @params uint8_t vector
/// @params void*   isr
/// @params uint8_t flags
/// @returns void
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

/// Setup Interrupt Descriptor Table.
/// @return voids
void idt_init(void);

/// Setup Interrupt Descriptor Table.
/// @return voids
void idt_load(void);

#endif 
