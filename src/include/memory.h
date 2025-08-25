#pragma once

#ifndef RORI_OS_MEMORY_H
#define RORI_OS_MEMORY_H

#include <stdint.h>
#include <stddef.h>

void memset(void *ptr, uint8_t val, size_t size);
void memcpy(void *dst, const void *src, size_t size);

#endif
