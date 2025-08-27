/// TIMER.h - v0.0
/// This file handle timer interrupt.
///
/// # Status:
/// -
///
/// # References:
/// - https://wiki.osdev.org/Programmable_Interval_Timer

#pragma once

#include "tty.h"
#ifndef RORI_OS_TIMER_H
#define RORI_OS_TIMER_H

void timer_init();
void sleep(unsigned long ms);

#endif

