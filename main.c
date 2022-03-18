#include "storage_device.h"

int main(void)
{
    FILE* input_file = fopen("../input.txt", "r");
    FILE* output_file = fopen("../output.txt", "w");

    if(!input_file || !output_file){
        return 0;
    }
    
    int write_size;
    printf("type write data size: ");
    if(!scanf("%d", &write_size)){
        return 1;
    }

    int count = valid_device_count(input_file, output_file, write_size);

    fclose(input_file);
    fclose(output_file);

    return 0;
}