#ifndef BOOTLOADER_H
#define BOOTLOADER_H

// Function to print a character on the screen
void print_char(char ch);

// Function to print a string on the screen
void print_str(const char *str);

// Entry point for the bootloader
void boot_main(void);

// Function to disable interrupts (applicable to later stages of the bootloader)
void disable_interrupts();

// For now, error handler..
void sys_hang(const char *str);

#endif // BOOTLOADER_H