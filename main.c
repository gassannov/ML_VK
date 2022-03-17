#include "my_task.h"

int main(void){
FILE* input_file = fopen("dz1_source_text.txt", "r");
        int number = number_of_valid_devices(567, input_file);
    fclose(input_file);
    return 0;
}