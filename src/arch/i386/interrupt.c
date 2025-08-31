#include "include/exception.h"
#include "include/idt.h"
#include "include/gdt.h"
#include "include/timer.h"

#include "../../include/interrupt.h"
#include "../../include/cpu.h"


void interrupt_init()
{
    interrupt_disable();
        gdt_init();

        idt_init();
        exception_init();
        timer_init();

        idt_load();
    interrupt_enable();
}
