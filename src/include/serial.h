/// SERIAL.h - v0.0
/// This file handle raw I/O communication between host with a port connected into
/// It exposes assembly instruction to send and receive from I/O Port
///
/// # I/O Port:
/// - 0x3F8 -> COM 1 (QEMU)
/// - 0x2F8 -> COM 2
///
/// # Status:
/// - Need to separate between raw inb and outb from serial_write or maybe
///   abstract it so it can accept port but that only depend on target chip
///
/// # References
/// - https://wiki.osdev.org/Serial_Ports
/// - https://wiki.osdev.org/Inline_Assembly

#pragma once

#ifndef RORI_OS_SERIAL_H
#define RORI_OS_SERIAL_H

#include <stdint.h>

/// QEMU is in COM1
#define COM1 0x3F8

/// This function send out byte to I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns void
void outb(uint16_t port, uint8_t val);

/// This function receive byte from I/O port
/// @params uint16_t    port
/// @params uint8_t     val
/// @returns uint8_t
uint8_t inb(uint16_t port);

/// -----------------------------------
/// QEMU-Related
/// -----------------------------------

/// Initialize serial port COM 1 for QEMU serial debugging
/// @returns void
void serial_init();

/// Initialize serial port COM 1 for QEMU serial debugging
/// @returns void
void serial_putchar(char c);
void serial_write(const char* s);
void serial_writeln(const char* s);

#endif
