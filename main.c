#include "storage_device.h"

int main(void)
{
    FILE* input_file = fopen("../input.txt", "r");
    FILE* output_file = fopen("../output.txt", "w");

    if(!input_file ){
        if (!output_file){
            fclose(output_file);
        }
        fclose(input_file);
        return 0;
    }

    if(!output_file){
        fclose(output_file);
        return 0;
    }
    
    int write_size;
    printf("type write data size: ");
    if(!scanf("%d", &write_size)){
        return 1;
    }

    int count = valid_device_count(input_file, output_file, write_size);

    printf("Количество устройств на которые можно записать данные размера %d: %d\n", write_size, count);

    fclose(input_file);
    fclose(output_file);

    return 0;
}