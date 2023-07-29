#include "idt.h"

#include <stdint.h>

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

static idtr_t idtr;

extern void* isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
    // TODO: implement this crap
}

void idt_init(void){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t vector = 0; vector < 32; vector++){
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}