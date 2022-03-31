#include <stdio.h>
#include <stdlib.h>
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
#define FORKS_NUMBER 10

int main()
{

    // VAR INITIALIZE AND DATA PREPARING

    const char *filename = "../large.txt";

    int fd = open(filename, O_RDWR); // или O_RDWR
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
    int str_size = strlen(shared_memory);

    printf("strlen is: %d\n", str_size);

    clock_t begin = clock();
    printf("max_len_of_word is : %d\n", max_word(shared_memory, str_size));
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    return 0;
}