#include "include/io.h"

/// This function send out byte to I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns void
void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


/// This function receive byte from I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns void
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
