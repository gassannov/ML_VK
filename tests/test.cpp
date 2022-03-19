#include <gtest/gtest.h>
#include "stdio.h"

extern "C"
{
#include "storage_device.h"
#include "stdbool.h"
}

TEST(type, TestOnTypeFunctions)
{
    device_class CD = cd;
    device_class USB_STR = str_to_type("usb");
    device_class DVD_STR = str_to_type("dvd");
    device_class CD_STR = str_to_type("cd");
    EXPECT_EQ(dvd, DVD_STR);
    EXPECT_EQ(cd, CD_STR);
    EXPECT_EQ(usb, USB_STR);
    EXPECT_EQ(cd, CD);
    EXPECT_STREQ("USB", type_to_str(USB_STR));
    EXPECT_STREQ("CD", type_to_str(CD_STR));
}

TEST(device, TestOnBasicStorageDeviceCreate)
{
    device_class CD = cd;
    size_t capacity = 10000;
    bool rewrite_accebility = true;
    char *str = "str";
    storage_device *device = create_device(str, CD, capacity, rewrite_accebility);
    EXPECT_TRUE(device != NULL);
    EXPECT_EQ(10000, device->capacity);
    EXPECT_EQ(true, rewrite_accebility);
    EXPECT_EQ(cd, device->device_type);
    free_device(device);
}

TEST(device, TestOnStorageDeviceCreateByStr)
{
    char input_str[] = "serial_number cd 1000 y";
    storage_device *device = create_device_by_str(input_str);
    EXPECT_TRUE(device != NULL);
    EXPECT_EQ(1000, device->capacity);
    EXPECT_EQ(true, device->rewrite_permission);
    EXPECT_EQ(cd, device->device_type);
    free_device(device);
}

TEST(device, TestOnWrongCreateByStr)
{
    char input_str[] = "serial_number usbb 10 n";
    storage_device *device = create_device_by_str(input_str);
    EXPECT_TRUE(device == NULL);
    free_device(device);
}

TEST(device, TestOnValidDeviceCount)
{
    char input_str[] = "s dvd 1 n\nss dvd 3 y\nv dvd 1 y\n";
    FILE *file = fmemopen(input_str, 34, "r");
    size_t count = valid_device_count(file, stdin, 2);
    EXPECT_EQ(1, count);
    fclose(file);
}

TEST(device, TestOnLongStr)
{
    char input_str[] = "his is very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very  very very long str";
    FILE *file = fmemopen(input_str, 34, "r");
    size_t count = valid_device_count(file, stdin, 2);
    EXPECT_EQ(count, 0);
    fclose(file);
}
