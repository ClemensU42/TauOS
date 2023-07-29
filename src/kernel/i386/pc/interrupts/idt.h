#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
    uint16_t    isr_low;        // lower 16 bits of ISR's address
    uint16_t    kernel_cs;      // GDT segment selector that the CPU will load into cs before calling the ISR
    uint8_t     ist;            // The IST in TSS that the CPU will load into RSP; set to zero for now
    uint8_t     attributes;     // type and attributes
    uint16_t    isr_mid;        // the higher 16 bits of the lower 32 bits of the ISR's address
    uint32_t    isr_high;       // the higher 32 bits of the ISR's address
    uint32_t    reserved;       // set to zero
}__attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t        limit;
    uint64_t        base;
}__attribute__((packed)) idtr_t;

void idt_init(void);
#endif