#pragma once

#ifndef RORI_OS_COMMON_H
#define RORI_OS_COMMON_H

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define HALT do {   \
    for(;;) {}      \
    asm volatile("hlt");\
} while(0)          \

#endif
