#include "include/keyboard.h"
#include "include/idt.h"
#include "include/serial.h"
#include <stdint.h>

#define KBD_BUF_SIZE 256
extern void keyboard_stub();
void keyboard_handler();
static unsigned char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,
    '\\','z','x','c','v','b','n','m',',','.','/',
    0,
    '*',
    0,
    ' ',
    0
};

static char kbd_buffer[KBD_BUF_SIZE];
static int kbd_head = 0;
static int kbd_tail = 0;

static inline int kbd_available() {
    return kbd_head != kbd_tail;
}

static inline char kbd_pop() {
    char c;
    while (!kbd_available());
    c = kbd_buffer[kbd_tail];
    kbd_tail = (kbd_tail + 1) % KBD_BUF_SIZE;
    return c;
}

static inline void kbd_push(char c) {
    int next = (kbd_head + 1) % KBD_BUF_SIZE;
    if (next != kbd_tail) {
        kbd_buffer[kbd_head] = c;
        kbd_head = next;
    }
}

char getch() {
    return kbd_pop();
}

void keyboard_init()
{
    idt_set_descriptor(0x21, keyboard_stub, 0x8E);

    // Enable keyboard mask
    uint8_t mask = inb(21);
    mask &= ~(1 << 1);
    outb(0x21, mask);
}


void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        // Key release, ignore for now
    } else {
        char c = scancode_table[scancode];
        if (c) {
            kbd_push(c);
            serial_putchar(c);
        }
    }

    return;
}
