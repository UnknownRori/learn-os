#include "include/exception.h"
#include "include/idt.h"

#define RORI_LOG
#include "../../include/log.h"
#include "../../include/cpu.h"

extern void* isr_stub_table[];
extern void exception_stub(void);


void exception_handler(void);

void exception_init()
{
    for (int i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i], 0x8E);
    }
}

__attribute__((noreturn))
void exception_handler(void) {
    LOG("[-] Exception Handler Hit!");
    halt();
}
