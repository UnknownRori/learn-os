/// KEYBOARD.h - v0.0
/// This file handle Keyboard driver.
///
/// # I/O Port
/// - 0x60 -> Keyboard Data Port
///
/// # Status:
/// - In the future it might need to be seperated to avoid cluterring the main source.
///
/// # References:
/// - https://wiki.osdev.org/PS/2_Keyboard
/// - http://forum.osdev.org/viewtopic.php?t=9746
/// - https://wiki.osdev.org/%228042%22_PS/2_Controller#Translation

#pragma once

#ifndef RORI_OS_KEYBOARD_H
#define RORI_OS_KEYBOARD_H

#define MAX_KEYBOARD_BUFFER 256

/// Initialize and enable keyboard interrupt
/// @params void
void keyboard_init();

/// Get the current char from keyboard event
/// @returns void
char getch();

#endif
