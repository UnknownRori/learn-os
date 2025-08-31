#include "../../include/fb.h"
#include "../../include/grub.h"
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

framebuffer_t* fb_init(multiboot_info_t* mb_info)
{
    fb = (framebuffer_t){
        .addr = (void*)mb_info->framebuffer_addr,
        .pitch = mb_info->framebuffer_pitch,
        .width = mb_info->framebuffer_width,
        .height = mb_info->framebuffer_height,
        .bpp = mb_info->framebuffer_bpp,
    };
    return &fb;
}

void fb_clear(u32 color)
{
    memset(backbuffer, color, sizeof(backbuffer));
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
