#include "include/types.h"
#include "include/serial.h"
void kmain(void** headers, uint32_t magic) 
{
    (void) headers;
    if (magic != 0x2BADB002) {
        asm volatile("hlt");
    }

    serial_init();
    serial_writeln("Hello, world!");
    serial_writeln("From Kernel");


    asm volatile("hlt");
}
