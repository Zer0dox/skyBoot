#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Function to install the GDT
void gdt_install();

// Function to enable protected mode
int enable_protected_mode();

#endif // GDT_H

