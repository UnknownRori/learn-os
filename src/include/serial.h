/// file: serial.c
/// This file handle
/// wiki.osdev.org/Serial_Ports

#pragma once

#ifndef RORI_OS_SERIAL_H
#define RORI_OS_SERIAL_H

#include <stdint.h>

#define COM1 0x3F8

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

void serial_init();
void serial_putchar(char c);
void serial_write(const char* s);

#endif
