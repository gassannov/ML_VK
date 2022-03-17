//
// Created by Марат Гасанов on 09.03.2022.
//
#include "storage_device.h"


storage_device* storage_device_create(char* serial_number, storage_device_type device_type, int capacity, bool rewrite_permission){
    if (serial_number == NULL || !device_type || !capacity || !(rewrite_permission == true || rewrite_permission == false)) {
        return NULL;
    }
    storage_device* storageDevice = (storage_device*)malloc(sizeof(storage_device));
    
    if(!storageDevice){
        return NULL;
    }
    storageDevice->serial_number = serial_number;
    storageDevice->device_type = device_type;
    storageDevice->capacity = capacity;
    storageDevice->rewrite_permission = rewrite_permission;
    return storageDevice;
}

storage_device* storage_device_create_by_str(char* str){
    char* sep = " ";
    char* divided_str = strtok(str, sep);
    int i = 1;
    char* serial_number = NULL;
    int capacity;
    bool rewrite_permission;
    storage_device_type device_type = 0;
    
    while(divided_str != NULL && i <= 4){
        switch (i){
            case 1:
                serial_number = divided_str;
                break;

            case 2:
                device_type = str_to_type(divided_str);
                break;

            case 3:
                if(is_number(divided_str))
                    capacity = atoi(divided_str);
                else
                    return NULL;
                break;

            case 4:
                if(divided_str[0] == 'y')
                    rewrite_permission = true; 
                else if(divided_str[0] == 'n')
                    rewrite_permission = false;
                else
                return NULL;
                break;
            default:
                break;
        }

        divided_str = strtok (NULL,sep);
        i++;
    } 

    return storage_device_create(serial_number, device_type, capacity, rewrite_permission);
}

void storage_device_free(storage_device* device){
    if(device){
        free(device);
        device = NULL;
    }
}

