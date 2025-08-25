#pragma once

#include "tty.h"
#ifndef RORI_OS_LOG_H
#define RORI_OS_LOG_H

#ifdef RORI_LOG
#include "common.h"
#include "tty.h"
#include "serial.h"

#define LOG(TXT) \
    do { \
        serial_writeln("[" __FILE__ ":" TOSTRING(__LINE__) "]: " TXT); \
        tty_writeln("[" __FILE__ ":" TOSTRING(__LINE__) "]: " TXT); \
    } while (0); 
#else
#define LOG(TXT)
#endif

#endif

