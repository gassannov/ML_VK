#include "storage_device.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

int is_number(const char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
        i++;
    }
    if (i == 0)
    {
        return 0;
    }
    return 1;
}

device_class str_to_type(char *str)
{
    if (!strcmp(str, "cd"))
    {
        device_class device_type = cd;
        return device_type;
    }

    else if (!strcmp(str, "dvd"))
    {
        device_class device_type = dvd;
        return device_type;
    }

    else if (!strcmp(str, "usb"))
    {
        device_class device_type = usb;
        return device_type;
    }

    else
    {
        return 0;
    }
}

char *type_to_str(device_class d_class)
{
    if (d_class == cd)
    {
        return "CD";
    }

    else if (d_class == dvd)
    {
        return "DVD";
    }

    else if (d_class == usb)
    {
        return "USB";
    }

    return NULL;
}

storage_device *create_device(char *serial_number, device_class d_class, int capacity, bool rewrite_permission)
{

    if (serial_number == NULL || !d_class || !capacity || !(rewrite_permission == true || rewrite_permission == false))
    {
        return NULL;
    }
    storage_device *storageDevice = (storage_device *)malloc(sizeof(storage_device));

    if (!storageDevice)
    {
        return NULL;
    }
    storageDevice->serial_number = serial_number;
    storageDevice->device_type = d_class;
    storageDevice->capacity = capacity;
    storageDevice->rewrite_permission = rewrite_permission;
    return storageDevice;
}

storage_device *create_device_by_str(char *str)
{
    char *sep = " ";
    char *divided_str = strtok(str, sep);
    int i = 1;
    char *serial_number = NULL;
    int capacity;
    bool rewrite_permission;
    device_class device_type = 0;
    while (divided_str != NULL && i <= 4)
    {
        switch (i)
        {
        case 1:
            serial_number = divided_str;
            break;

        case 2:
            device_type = str_to_type(divided_str);
            break;

        case 3:
            if (is_number(divided_str))
                capacity = atoi(divided_str);
            else
                return NULL;
            break;

        case 4:
            if (divided_str[0] == 'y')
                rewrite_permission = true;
            else if (divided_str[0] == 'n')
                rewrite_permission = false;
            else
                return NULL;
            break;
        default:
            break;
        }

        divided_str = strtok(NULL, sep);
        i++;
    }
    return create_device(serial_number, device_type, capacity, rewrite_permission);
}

void print_in_file(FILE *file, storage_device *device)
{
    fprintf(file, "serial_number:%s\ndevice_type:%s\ncapacity:%d\nrewrite_accebility:%d\n\n", device->serial_number, type_to_str(device->device_type), device->capacity, device->rewrite_permission);
    
}

void free_device(storage_device *device)
{
    if (device)
    {
        free(device);
        device = NULL;
    }
}

size_t valid_device_count(FILE *input_file, FILE *output_file, size_t size)
{
    size_t count = 0;
    storage_device *device;
    char buffer[BUFFER_SIZE];
    size_t max_len = BUFFER_SIZE;
    char *str = malloc(max_len);
    str[0] = '\0';
    while (fgets(buffer, BUFFER_SIZE, input_file) != NULL)
    {
        size_t current_len = strlen(str);
        size_t buffer_len = strlen(buffer);
        if (max_len - current_len < buffer_len)
        {
            max_len *= 2;
            if ((str = realloc(str, max_len)) == NULL)
            {
                free(str);
                return 1;
            }
        }
        strncpy(str + current_len, buffer, max_len - current_len);
        current_len += buffer_len;
        if (str[current_len - 1] == '\n')
        {
            device = create_device_by_str(str);
            if (device)
            {
                if (device->capacity > size)
                {
                    print_in_file(output_file, device);
                    free_device(device);
                    count++;
                }
            }
            str[0] = '\0';
            current_len = 0;
        }
    }
    device = create_device_by_str(str);
    if (device)
    {
        if (device->capacity > device)
        {
            print_in_file(output_file, device);
            free_device(device);
            count++;
        }
    }
    free(str);
    return count;
}
