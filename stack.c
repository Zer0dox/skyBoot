#include <stdint.h>

// Define the stack size
#define STACK_SIZE 4096

// Stack memory
uint8_t stack[STACK_SIZE];

// Function to set up the stack
void setup_stack() {
    
    uint32_t stack_top = (uint32_t)&stack[STACK_SIZE];

    // Load the stack segment selector into SS (0x18 corresponds to the fourth entry in the GDT)
    __asm__ volatile ("mov $0x18, %%ax\n\t"
                      "mov %%ax, %%ss\n\t"
                      "mov %0, %%esp\n\t"
                      : 
                      : "r" (stack_top)
                      : "ax");
}

