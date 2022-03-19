#ifndef STORAGE_DEVICE

#define STORAGE_DEVICE

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"

typedef enum device_class
{
    cd = 1,
    dvd = 2,
    usb = 3
} device_class;

device_class str_to_type(char *str);
const char *type_to_str(device_class d_class);

typedef struct storage_device
{
    char *serial_number;
    device_class device_type;
    size_t capacity;
    bool rewrite_permission;
} storage_device;

storage_device *create_device(char *serial_number, device_class d_class, size_t capacity, bool rewrite_permission);
storage_device *create_device_by_str(char *str);
void free_device(storage_device *device);
size_t valid_device_count(FILE *input_file, FILE *output_file, size_t size);

int str_count(FILE *file);
int max_line(FILE *file);

#endif STORAGE_DEVICE