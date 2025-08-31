#include "../../include/fb.h"
#include "../../include/memory.h"
#include "../../include/assert.h"

// TODO : Very fragile back buffer
#define WIDTH  1366
#define HEIGHT 768
static uint32_t backbuffer[WIDTH * HEIGHT];

static framebuffer_t fb = {0};

static void put_pixel(int x, int y, u32 color)
{
    assert((x >= 0 && x <= fb.width) && (y >= 0 && y <= fb.height));
    backbuffer[y * fb.width + x] = color;
}

void fb_init(framebuffer_t fb_new)
{
    fb = fb_new;
}

void fb_clear(u32 color)
{
    // memset(backbuffer, color, sizeof(backbuffer));
}

void fb_draw_rect(int x, int y, int w, int h, u32 color)
{

    for (int row = y; row < h + y; row++) {
        for (int col = x; col < w + x; col++) {
            put_pixel(col, row, color);
        }
    }
}

void fb_commit()
{
    for (int y = 0; y < HEIGHT; y++) {
        uint32_t* src = backbuffer + y * fb.width;
        uint32_t* dst = (uint32_t*)((uint8_t*)fb.addr + y * fb.pitch);
        memcpy(dst, src, fb.width * sizeof(uint32_t));
    }
}
