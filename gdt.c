#include "gdt.h"

// GDT entry structure
struct gdt_entry {
    uint16_t limit_low;    // Lower 16 bits of the limit
    uint16_t base_low;     // Lower 16 bits of the base
    uint8_t base_middle;   // Next 8 bits of the base
    uint8_t access;        // Access flags
    uint8_t granularity;   // Granularity flags and high 4 bits of the limit
    uint8_t base_high;     // Last 8 bits of the base
} __attribute__((packed));

// GDT pointer structure
struct gdt_ptr {
    uint16_t limit;        // Upper 16 bits of all selector limits
    uint32_t base;         // Address of the first gdt_entry
} __attribute__((packed));

// GDT entries
struct gdt_entry gdt[4];

// GDT pointer
struct gdt_ptr gdtp;

// Function to set the value of one GDT entry
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access = access;
}

// Function to install the GDT
void gdt_install() {

    // Set up GDT pointer
    gdtp.limit = (sizeof(struct gdt_entry) * 4) - 1;
    gdtp.base = (uint32_t)&gdt;

    // Set up GDT entries
    set_gdt_entry(0, 0, 0, 0, 0);                // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0x92, 0xCF); // Stack Segment

    // Load the GDT using the LGDT instruction
    __asm__ volatile ("lgdt (%0)" : : "r" (&gdtp));

    // Test if GDT loading was successful by checking segment registers
    uint16_t cs, ds;
    __asm__ volatile (
        "mov %%cs, %0\n"
        "mov %%ds, %1\n"
        : "=g"(cs), "=g"(ds)
    );

    if (cs != 0x08 || ds != 0x10) {
        // An error occurred during GDT loading
        // You can print an error message or take appropriate action here
        print_str("Error: GDT installation failed.");
    }
}

// Function to enable protected mode
int enable_protected_mode() {
    
    // Check if the GDT is properly installed
    if (gdtp.limit == 0 || gdtp.base == 0) {
        return -1; // Error: GDT not initialized
    }

    // Enable protected mode by setting the PE bit in CR0
    __asm__ volatile (
        "mov %%cr0, %%eax\n\t"
        "or $0x1, %%eax\n\t"
        "mov %%eax, %%cr0\n\t"
        :
        :
        : "eax"
    );

    // Perform a far jump to flush the instruction prefetch queue
    __asm__ volatile (
        "ljmp $0x08, $next\n\t"
        "next:\n\t"
        :
        :
    );

    return 0; // Success
}
