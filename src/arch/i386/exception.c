#include "include/exception.h"
#include "include/idt.h"

#define RORI_LOG
#include "../../include/log.h"
#include "../../include/cpu.h"


void exception_handler(u32);

extern void* isr_stub_table[];
extern void exception_stub();
static const char* exception_code[] = {
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device not Available",
    "Double Fault",
    "Coprocessor Segment Overrun (reserved)",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "-- Intel Reserved --",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    " -- Reserved --",
    "External Interrupt",
};
void exception_init()
{
    for (int i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i], 0x8E);
    }
}

__attribute__((noreturn))
void exception_handler(u32 code) {
    LOG("Exeption Hit!");
    serial_write("Exception: ");
    serial_write(exception_code[code % 32]);
    serial_write("\n");
    halt();
}
