//
// Created by Марат Гасанов on 09.03.2022.
//
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#ifndef DZ1_SUPPORT_H
#define DZ1_SUPPORT_H

char* input_str();
int str_compare(const char str1[], const char str2[]);
size_t str_size(const char* str);
int is_number(const char* str);
int number_file_str(FILE* file);
int max_line_file(FILE* file);

#endif //DZ1_SUPPORT_H
