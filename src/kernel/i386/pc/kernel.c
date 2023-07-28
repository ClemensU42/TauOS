#include <stdint.h>
#include <stddef.h>
#include <limine.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void* memcpy(void* dest, const void* src, size_t n){
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (uint8_t*)src;

    for(size_t i = 0; i < n; i++)
        pdest[i] = psrc[i];

    return dest;
}

void* memset(void* s, int c, size_t n){
    uint8_t* p = (uint8_t*)s;
    
    for(size_t i = 0; i < n; i++)
        p[i] = (uint8_t)c;
    
    return s;
}

void *memmove(void* dest, const void* src, size_t n){
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t *psrc = (const uint8_t*)src;

    if(src > dest){
        for(size_t i = 0; i < n; i++)
            pdest[i] = psrc[i];
    } else if(src < dest){
        for(size_t i = n; i > 0; i--){
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n){
    const uint8_t *p1 = (const uint8_t*)s1;
    const uint8_t *p2 = (const uint8_t*)s2;

    for(size_t i = 0; i < n; i++)
        if(p1[i] != p2[i])
            return p1[i] < p2[i] ? -1 : 1;

    return 0;
}

// halt and catch fire function
static void hcf(void){
    asm("cli");
    for(;;)
        asm("hlt");
}

void _start(void){
    // Ensure we got a framebuffer
    if(framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1){
        hcf();
    }

    struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];

    // Note: we assume the framebuffer model is RGB with 32-bit pixels
    for(size_t i = 0; i < 100; i++){
        uint32_t* fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffffff;
    }

    // We're done, just hang
    hcf();
}