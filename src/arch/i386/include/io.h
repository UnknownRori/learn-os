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

#ifndef RORI_IO_H
#define RORI_IO_H

#include "../../../include/types.h"

u8 inb(u16 port);
void outb(u16 port, u8 value);

#endif
