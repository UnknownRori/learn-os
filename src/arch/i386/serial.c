#include "include/io.h"
#include "../../include/serial.h"

#define COM1 0x3f8

void serial_init()
{
    outb(COM1 + 1, 0b00000000); // Disable interrupts
    outb(COM1 + 3, 0b10000000); // Set DLAB on
    outb(COM1 + 0, 0b00000001); // Set lower byte divisor
    outb(COM1 + 1, 0b00000000); // Set lower byte divisor
    outb(COM1 + 3, 0b00000011); // 8 bit data 1 stop bit
    outb(COM1 + 2, 0b11000111); // Enable FIFO, clear them, 14-byte threshold
    outb(COM1 + 4, 0b00001011); // IRQs enabled, RTS/DSR set
}

static inline u8 serial_is_empty()
{
    return inb(COM1 + 5) & 0b00100000;
}

void serial_write_byte(u8 value)
{
    while (!serial_is_empty()) {};
    outb(COM1, value);
}

void serial_write(const char* str)
{
    while (*str) {
        serial_write_byte(*str);
        str++;
    }
}

void serial_writeln(const char* str)
{
    serial_write(str);
    serial_write_byte('\n');
}
