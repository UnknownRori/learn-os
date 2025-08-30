#pragma once

#ifndef RORI_FB_H
#define RORI_FB_H

#include "types.h"

typedef struct {
    void* addr;
    u32 pitch;
    u32 width;
    u32 height;
    u8  bpp;
} framebuffer_t;

void fb_init(framebuffer_t fb_new);
void fb_commit();
void fb_clear(u32 color);
void fb_draw_rect(int x, int y, int w, int h, u32 color);

#endif
