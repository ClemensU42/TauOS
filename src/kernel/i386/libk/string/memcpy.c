#include <string.h>

#include <stddef.h>
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t n){
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (uint8_t*)src;

    for(size_t i = 0; i < n; i++)
        pdest[i] = psrc[i];

    return dest;
}