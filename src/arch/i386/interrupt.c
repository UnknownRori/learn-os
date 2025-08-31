#include "include/gdt.h"
#include "../../include/interrupt.h"

void interrupt_init()
{
    gdt_init();
}
