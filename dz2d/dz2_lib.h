#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "string.h"
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>

size_t max_word(const char* str, size_t str_len);