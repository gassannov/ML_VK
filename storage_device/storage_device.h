//
// Created by Марат Гасанов on 09.03.2022.
//

#ifndef DZ1_STORAGE_DEVICE_H
#define DZ1_STORAGE_DEVICE_H

#include "device_type.h"
#include "stdbool.h"
#include "my_string.h"

typedef struct storage_device{
    char *serial_number;
    storage_device_type  device_type;
    int capacity;
    bool rewrite_permission;
} storage_device;

storage_device* storage_device_create(char* serial_number, storage_device_type device_type, int capacity, bool rewrite_permission);
storage_device* storage_device_create_by_str(char* str);

void storage_device_free(storage_device* device);

#endif //DZ1_STORAGE_DEVICE_H
