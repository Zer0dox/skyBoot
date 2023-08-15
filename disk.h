#ifndef DISK_H
#define DISK_H

static int initialize_ide();

static int initialize_ahci();

static int initialize_nvme();

int initialize_disk_controller();

#endif