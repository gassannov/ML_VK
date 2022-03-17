#include "my_task.h"


int number_of_valid_devices(size_t rewrite_size, FILE* file){
    int count = 0;
    FILE* output_file = fopen("dz1_output_text.txt", "w");
    if (!file || !output_file){
        printf("cannot open file\n");
        return 0;
    }
    fprintf(output_file, "Devices:\n");
    int max_line = max_line_file(file);
    char* buffer = malloc(sizeof(char) * (max_line+2));
    storage_device* device = NULL;
    while(!feof(file)){
        if(fgets(buffer, max_line+2, file)){
            device = storage_device_create_by_str(buffer);
            if (device){
                if (device->capacity > rewrite_size){
                    fprintf(output_file, "serial_number: %s\n", device->serial_number);
                    fprintf(output_file, "device_type: %s\n", type_to_str(device->device_type));
                    fprintf(output_file, "capacity: %d\n", device->capacity);
                    if(device->rewrite_permission == true)
                        fprintf(output_file, "rewrite_permission: yes\n");
                    else
                        fprintf(output_file, "rewrite_permission: no\n");
                    count++;
                    fprintf(output_file, "\n");
                }
            }
            storage_device_free(device);
        }
    }
    fprintf(output_file, "%d - devices\n", count);
    free(buffer);
    fclose(output_file);

    return count;
}