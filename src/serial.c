#include "include/serial.h"
#include "include/assert.h"

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

///---------------------------------------
/// Serial write to QEMU
///---------------------------------------

void serial_init()
{
    outb(COM1 + 1, 0b00000000);    // Disable interrupts
    outb(COM1 + 3, 0b10000000);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0b00000011);    // Divisor low byte (115200 / 3 = 38400 baud)
    outb(COM1 + 1, 0b00000000);    // Divisor high byte
    outb(COM1 + 3, 0b00000011);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0b11000111);    // Enable FIFO, clear them, 14-byte threshold
    outb(COM1 + 4, 0b00001011);    // IRQs enabled, RTS/DSR set
}

int serial_is_transmit_empty() {
    return inb(COM1 + 5) & 0b01000000;
}
void serial_putchar(char c) {
    while (!serial_is_transmit_empty());
    outb(COM1, c);
}

void serial_write(const char* s) {
    assert(s != NULL);

    while (*s) {
        serial_putchar(*s++);
    }
}

void serial_writeln(const char* s) {
    serial_write(s);
    serial_putchar('\n');
}
