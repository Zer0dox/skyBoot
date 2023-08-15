#include <stdint.h>
#include "ide.h"

// Function to read a byte from an I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Function to write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Function to initialize the IDE disk controller
int initialize_ide() {
    // Select the primary channel's master drive
    outb(IDE_PRIMARY_IO_BASE + IDE_REG_DRIVE_SELECT, IDE_DRIVE_MASTER);

    // Send the IDENTIFY command to the command register
    outb(IDE_PRIMARY_IO_BASE + IDE_REG_COMMAND, IDE_CMD_IDENTIFY);

    // Wait for the controller to become ready or report an error
    int timeout = 10000; // Adjust as needed
    while (timeout--) {
        uint8_t status = inb(IDE_PRIMARY_IO_BASE + IDE_REG_STATUS);

        if (status & IDE_STATUS_ERR) {
            return -1; // Error occurred
        }

        if (!(status & IDE_STATUS_BSY) && (status & IDE_STATUS_DRQ)) {
            break; // Controller is ready
        }
    }

    if (timeout <= 0) {
        return -2; // Timeout error
    }

    // Read the identification data (optional)
    uint16_t identification_data[256];
    for (int i = 0; i < 256; i++) {
        identification_data[i] = inb(IDE_PRIMARY_IO_BASE + IDE_REG_DATA);
    }

    // Additional initialization steps may be required based on the identification data

    return 0; // Success
}
