
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "string.h"
#include <fcntl.h>
#include <time.h>
#include "dz2_lib.h"

#define ARR_SIZE 100000000
#define TEXT_NUMBER 5

int main()
{
    char filename[19] = "../texts/test0.txt";
    double test_times[TEXT_NUMBER] = {0};

    for (int i = 0; i < TEXT_NUMBER; ++i)
    {   
        filename[13] = '0'+i;

        int fd = open(filename, O_RDWR);
        struct stat st;
        stat(filename, &st);

        size_t file_size = st.st_size;

        char *shared_memory = mmap(NULL,
                               file_size,
                               PROT_READ | PROT_WRITE,
                               MAP_PRIVATE,
                               fd,
                               0);

        if (shared_memory == MAP_FAILED)
        {
            printf("mmap failed\n");
            close(fd);
            return 1;
        }
        size_t str_size = strlen(shared_memory);

        clock_t begin = clock();
        size_t len = max_word(shared_memory, str_size);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        test_times[i] = time_spent;
        close(fd);
        printf("File %d, max len is: %lu\n", i, len);
    }
    double sum = 0;
    for (int i = 0; i < TEXT_NUMBER; ++i)
    {
        sum += test_times[i];
    }

    printf("Среднее время работы: %f\n", (sum/TEXT_NUMBER));

    return 0;
}