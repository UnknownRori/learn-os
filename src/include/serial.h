#pragma once

#ifndef RORI_SERIAL_H
#define RORI_SERIAL_H

#include "types.h"

void serial_init();
void serial_write_byte(u8);
void serial_write(const char*);
void serial_writeln(const char*);

#endif
