//
// Created by Марат Гасанов on 09.03.2022.
//

#include "my_string.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef DZ1_DEVICE_TYPE_H
#define DZ1_DEVICE_TYPE_H

typedef enum storage_device_type{
    cd = 1,
    dvd = 2,
    usb = 3
} storage_device_type;

storage_device_type str_to_type(char* str);
char* type_to_str(storage_device_type deviceType);

#endif //DZ1_DEVICE_TYPE_H
