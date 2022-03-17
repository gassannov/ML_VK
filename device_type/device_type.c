//
// Created by Марат Гасанов on 09.03.2022.
//
#include "device_type.h"

storage_device_type str_to_type(char* str){
    if(str_compare(str, "cd") == 1){
        storage_device_type device_type = cd;
        return device_type;
    }

    else if (str_compare(str, "dvd") == 1){
        storage_device_type device_type = dvd;
        return device_type;
    }

    else if(str_compare(str, "usb") == 1){
        storage_device_type device_type = usb;
        return device_type;
    }

    else{
        return 0;
    }
}

char* type_to_str(storage_device_type deviceType){
    if(deviceType == cd){
        return "CD";
    }

    else if(deviceType == dvd){
        return "DVD";
    }

    else if(deviceType == usb){
        return "USB";
    }
    return "NONE";
}