#pragma once

#include "vga.h"
#ifndef RORI_OS_TTY_H
#define RORI_OS_TTY_H

void tty_init();
void tty_putchar(char c);
void tty_set_color(VGA_COLOR fg, VGA_COLOR bg);
void tty_write(const char* str);
void tty_writeln(const char* str);
void tty_flush();

#endif
