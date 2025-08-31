#include "../../include/cpu.h"

void halt()
{
    for (;;) {}
    asm volatile("hlt");
}


void interrupt_enable()
{
    asm volatile("sti");
}

void interrupt_disable()
{
    asm volatile("cli");
}
