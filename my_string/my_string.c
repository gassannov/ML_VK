//
// Created by Марат Гасанов on 09.03.2022.
//
#include "my_string.h"


int str_compare(const char str1[], const char str2[]){
    size_t size = str_size(str2);
    if (str_size(str1) != size)
        return 0;
    for (size_t i = 0; i < size; ++i) {
        if(str1[i] != str2[i])
            return 0;
    }
    return 1;
}

size_t str_size(const char str[]){
    if(!str)
        return 0;
    size_t m = 0;
    while(str[m] != '\0')
        m++;
    return m;
}

int is_number(const char* str){
    size_t i = 0;
    while(str[i] != '\0'){
        if(!isdigit(str[i])){
            return 0;
        }
        i++;
    }
    if(i == 0){
        return 0;
    }
    return 1;
}

int number_file_str(FILE* file){
    int lines_count = 0;
    while (! feof(file))
    {
        if (fgetc(file) == '\n')
            lines_count++;
    }
    lines_count++;
    fseek(file, 0, SEEK_SET);
    return lines_count;
}

int max_line_file(FILE* file){
    size_t max_line = 0;
    size_t current_line = 0;
    char c = '\0';
    while(!feof(file)){
        if(c = fgetc(file) == '\n'){
            if(current_line > max_line)
                max_line = current_line;
            current_line = 0;
        }
        else{
            current_line++;
        }
    }
    if(current_line > max_line)
        max_line = current_line;
    fseek(file, 0, SEEK_SET);
    return max_line;
}