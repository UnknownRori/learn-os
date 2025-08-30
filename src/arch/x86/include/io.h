#pragma once

#ifndef RORI_IO_H
#define RORI_IO_H

#include "../../../include/types.h"

u8 inb(u16 port);
void outb(u16 port, u8 value);

#endif
