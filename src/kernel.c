void kmain(void) {
    volatile char* vga = (volatile char*)0xB8000;
    const char* msg = "Hello from C!";
    int i = 0;

    while (msg[i]) {
        vga[i * 2] = msg[i];
        vga[i * 2 + 1] = 0x0F;
        i++;
    }

    for (;;); // hang
}
