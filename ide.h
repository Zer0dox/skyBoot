#ifndef BOOTLOADER_H
#define BOOTLOADER_H

// Definitions for IDE
#define IDE_PRIMARY_IO_BASE   0x1F0
#define IDE_SECONDARY_IO_BASE 0x170

// IDE Status and Error Registers
#define IDE_REG_STATUS        0x07
#define IDE_REG_ERROR         0x01

// IDE Command Registers
#define IDE_REG_COMMAND       0x07
#define IDE_REG_SECTOR_COUNT  0x02
#define IDE_REG_SECTOR_NUMBER 0x03
#define IDE_REG_CYLINDER_LOW  0x04
#define IDE_REG_CYLINDER_HIGH 0x05
#define IDE_REG_DRIVE_SELECT  0x06

// IDE Data Register
#define IDE_REG_DATA          0x00

// IDE Control Register
#define IDE_REG_CONTROL       0x0C

// IDE Drive Select Values
#define IDE_DRIVE_MASTER      0xA0
#define IDE_DRIVE_SLAVE       0xB0

// IDE Command Codes
#define IDE_CMD_IDENTIFY      0xEC
#define IDE_CMD_READ_SECTORS  0x20
#define IDE_CMD_WRITE_SECTORS 0x30

// IDE Status and Error Flags
#define IDE_STATUS_ERR        0x01
#define IDE_STATUS_DRQ        0x08
#define IDE_STATUS_RDY        0x40
#define IDE_STATUS_BSY        0x80

// Read byte from I/O port
static inline uint8_t inb(uint16_t port); 

// Write byte to I/O port
static inline void outb(uint16_t port, uint8_t value);

// Init IDE interafacec
int initialize_ide();


#endif