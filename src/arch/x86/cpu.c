#include "../../include/cpu.h"

void halt()
{
    for (;;) {}
    asm volatile("hlt");
}
