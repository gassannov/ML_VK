#include <gtest/gtest.h>
#include "stdio.h"

extern "C"{
    #include "device_type.h"
    #include "storage_device.h"
    #include "stdbool.h"
    #include "my_string.h"
    #include "my_task.h"
}

TEST(type, Test){
    storage_device_type CD = cd;
    storage_device_type USB_STR = str_to_type("usb");
    storage_device_type DVD_STR = str_to_type("dvd");
    storage_device_type CD_STR = str_to_type("cd");
    storage_device_type NONE_STR = str_to_type("none");
    EXPECT_EQ(0, NONE_STR);
    EXPECT_EQ(dvd, DVD_STR);
    EXPECT_EQ(cd, CD_STR);
    EXPECT_EQ(usb, USB_STR);
    EXPECT_EQ(cd, CD);
}

TEST(type, TestStrCountInFile){
    char* str = "foo\nbar\nfoo";
    FILE* file = fmemopen(str, 12, "r");
    int str_number = number_file_str(file);
    EXPECT_EQ(3, str_number);
}

TEST(type, TestMaxLineInFile){
    char* str = "foo\nbaaar\nfooo";
    FILE* file = fmemopen(str, 14, "r");
    int str_number = max_line_file(file);
    EXPECT_EQ(5, str_number);
}

TEST(type, TestOnBasicStorageDeviceCreate){
    storage_device_type CD = cd;
    int capacity = 10000;
    bool rewrite_accebility = true;
    char* str = type_to_str(CD);
    storage_device* device = storage_device_create(str, CD, capacity, rewrite_accebility);
    EXPECT_TRUE(device != NULL);
    EXPECT_EQ(10000, device->capacity);
    EXPECT_EQ(true, rewrite_accebility);
    EXPECT_EQ(cd, device->device_type);
    storage_device_free(device);
}

TEST(type, TestOnStorageDeviceCreateByStr){
    char input_str[] = "serial_number cd 1000 y";
    storage_device* device = storage_device_create_by_str(input_str);
    EXPECT_TRUE(device != NULL);
    EXPECT_EQ(1000, device->capacity);
    EXPECT_EQ(true, device->rewrite_permission);
    EXPECT_EQ(cd, device->device_type);
    storage_device_free(device);
}

TEST(type, TestOnWrongCreateByStr){
    char input_str[] = "serial_number usbb 10 n";
    storage_device* device = storage_device_create_by_str(input_str);
    EXPECT_TRUE(device == NULL);
}

TEST(type, TestOnMyTask){
    char str[] = "sx cd 10 y\n lx cd 10 n\n l ccd 10 y";
    FILE* file = fmemopen(str, 36, "r");
    int n = number_of_valid_devices(2, file);
    EXPECT_EQ(2, n);
}