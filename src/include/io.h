/// IO.h - v0.0
/// This file handle raw I/O communication between host with a port connected into
/// It exposes assembly instruction to send and receive from I/O Port
///
/// # Status:
/// - 
///
/// # References
/// - https://wiki.osdev.org/Serial_Ports
/// - https://wiki.osdev.org/Inline_Assembly

#pragma once

#ifndef RORI_OS_IO_H
#define RORI_OS_IO_H

#include <stdint.h>
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

#endif
