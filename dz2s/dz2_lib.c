#include "dz2_lib.h"

int max_word(const char* str, size_t str_len){
    size_t curr_len = 0;
    size_t max_word = 0;
    int is_word = 0;

    for (size_t j = 0; j < str_len; ++j)
    {
        if ((str[j] >= 'A' && str[j] <= ('A' + 25)) || (str[j] >= 'a' && str[j] <= ('a' + 25)) ){
            is_word = 1; 
            curr_len++;
        }
        else if(str[j] == ' ' || str[j] == '\n'){
            if(is_word){
                if (curr_len > max_word)
                {
                    max_word = curr_len;
                }
            }
            curr_len = 0;
            is_word = 0;
        }
        else{
            curr_len = 0;
            is_word = 0;
        }
    }
    if(curr_len > max_word){
        max_word = curr_len;
    }
    return max_word;
}
