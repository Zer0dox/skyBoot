__asm__(".code16gcc\n"); // Tell GCC that we are working in 16-bit mode

#include <stdint.h>
#include "gdt.h"
#include "stack.h"

void sys_hang(const char* str) {

    print_str(str);
    while(0) {}
}

void disable_interrupts() {

    __asm__ volatile ("cli");
    
    // Check if interrupts enabled
    unsigned short flags;
    __asm__ volatile ("pushf; pop %0" : "=g"(flags));
    
    if (flags & (1 << 9)) {

        // Bit 9 of the flags register indicates interrupts are enabled
        // You can print an error message or take appropriate action here
        sys_hang("Error: Interrupts were not successfully disabled.");
    }
}

// Function to print a character on the screen
void print_char(char ch) {
    __asm__ volatile (
        "int $0x10" : : "a"(0x0E00 | ch), "b"(0x0007)
    );
}

// Function to print a string on the screen
void print_str(const char *str) {
    while (*str) {
        print_char(*str++);
    }
}

// Entry point for the bootloader
void boot_main(void) {

    print_str("Init skyBoot v1.0.0");

    disable_interrupts();
    gdt_install();
    if(enable_protected_mode() != 0) {
        sys_hang("Error: GDT not initilized.");
    }
    setup_stack();

}

// Boot sector signature
__asm__ (
    ".section .sig\n"
    ".globl _start\n"
    "_start:\n"
    ".word 0xAA55\n"
);
