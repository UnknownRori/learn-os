#pragma once

#ifndef RORI_OS_ASSERT_H
#define RORI_OS_ASSERT_H

#include "common.h"
#include "cpu.h"

#ifndef ASSERT_LOG
    #include "serial.h"
    #define ASSERT_LOG serial_write
#endif

#define ERR_MSG  "[-] Assert Failed at [" __FILE__ ":" TOSTRING(__LINE__) "]: "

#define assert(EXPR)    \
    do {                \
        if (!(EXPR)) {  \
            ASSERT_LOG(ERR_MSG #EXPR "\n"); \
            halt();     \
        }               \
    } while (0);        


#endif
