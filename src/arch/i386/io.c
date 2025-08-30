#include "include/io.h"


/// This function send out byte to I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns void
void outb(u16 port, u8 val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


/// This function receive byte from I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns void
u8 inb(u16 port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
