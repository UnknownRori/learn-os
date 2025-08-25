#include "include/timer.h"
#include "include/idt.h"

#define RORI_LOG
#include "include/log.h"

static volatile unsigned long ticks = 0;

extern void timer_stub(void);

void timer_init()
{
    idt_set_descriptor(0x20, timer_stub, 0x8E);

    // Enable timer interrupt
    uint8_t mask = inb(0x21);
    outb(0x21, mask & ~1);
}


void timer_handler(void) {
    ticks += 1;
    return;
}
void sleep(unsigned long ms) {
    unsigned long target = ticks + (ms / 10); 
    while (ticks < target) {
        asm volatile("hlt");
    }
}
