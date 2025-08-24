#pragma once

#ifndef RORI_OS_ASSERT_H
#define RORI_OS_ASSERT_H

#include "vga.h"
#include "common.h"

#define ERR_MSG  "Assertion Failed at [" __FILE__ ":" TOSTRING(__LINE__) "]"

#define assert(EXPR)    \
    do {                \
        if (!(EXPR)) {    \
            vga_put_str(ERR_MSG #EXPR, vga_entry_color(VGA_WHITE, VGA_RED), 0, 0); \
            HALT;       \
        }               \
    } while (0);        \


#endif
