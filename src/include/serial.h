/// SERIAL.h - v0.0
/// This file handle serial connection in the I/O port
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

#pragma once

#ifndef RORI_OS_SERIAL_H
#define RORI_OS_SERIAL_H

#include <stdint.h>

/// QEMU is in COM1
#define COM1 0x3F8

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
