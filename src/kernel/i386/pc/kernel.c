#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include <string.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

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