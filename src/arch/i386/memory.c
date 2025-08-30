#include "../../include/memory.h"
#include "../../include/assert.h"

void memset(void *ptr, uint8_t val, size_t size) {
    assert(ptr != NULL);

    uint8_t *p = (uint8_t*)ptr;
    for (size_t i = 0; i < size; ++i) {
        p[i] = val;
    }
}

void memcpy(void *dst, const void *src, size_t size) {
    assert(dst != NULL);
    assert(src != NULL);

    uint8_t *d = (uint8_t*)dst;
    const uint8_t *s = (const uint8_t*)src;

    assert(d + size <= s || s + size <= d);

    for (size_t i = 0; i < size; ++i) {
        d[i] = s[i];
    }
}
