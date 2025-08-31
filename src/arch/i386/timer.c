#include "include/idt.h"
#include "include/io.h"
#include "../../include/timer.h"

#define IRQ_0 0x20
#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQUENCY 1193182

static volatile unsigned long ticks = 0;

extern void timer_stub(void);

void timer_init()
{

    idt_set_descriptor(IRQ_0, timer_stub, 0x8E);

    // Enable timer interrupt
    uint8_t mask = inb(0x21);
    outb(0x21, mask & ~1);

    // Set it's frequency
    uint16_t divisor = PIT_FREQUENCY / 1000;
    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);
}


void timer_handler(void) {
    ticks += 1;
    return;
}

/// TODO : ms in this part is misleading
void sleep(unsigned long ms) {
    unsigned long target = ticks + (ms / 10); 
    while (ticks < target) {
        asm volatile("hlt");
    }
}
