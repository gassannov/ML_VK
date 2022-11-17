#include "dz2_lib.h"

//Индексы для разбиения массива
size_t *fork_idxs(const char *str, size_t str_len, size_t number_per_fork, size_t forks_number)
{
    if (!str || str_len <= 0)
    {
        return NULL;
    }

    size_t *idxs = (size_t *)malloc(sizeof(size_t) * (forks_number + 1));
    size_t i = 0;
    size_t idx = number_per_fork;

    while (idx < str_len)
    {
        while (isalpha(str[idx]))
        {
            idx++;
        }
        idx++;
        if (idx < str_len)
        {
            idxs[i] = idx;
            i++;
            idx += number_per_fork;
        }
    }
    idxs[i] = str_len + 1;
    i++;
    idxs[i] = 0;
    return idxs;
}

size_t max_word(const char *str, size_t str_len)
{
    if (!str || str_len <= 0)
    {
        return 0;
    }
    int mainpid = getpid();
    size_t FORKS_NUMBER = sysconf(_SC_NPROCESSORS_ONLN);
    pid_t* pids = (pid_t*)malloc(sizeof(pid_t)*FORKS_NUMBER);
    int wait_status = 0;
    size_t curr_len = 0;
    size_t max_word = 0;
    int is_word = 0;
    size_t upper_limit = 0;
    size_t down_limit = 0;
    int number_per_fork = str_len / FORKS_NUMBER;
    size_t longest_words = 0;
    int fd[2];
    if (pipe(fd) != 0)
    {
        printf("Opening pipe failed\n");
        return 1;
    }

    size_t *idxs = fork_idxs(str, str_len, number_per_fork, FORKS_NUMBER);
    size_t idxs_len = 0;
    while(idxs[idxs_len] != 0){idxs_len++;}


    for (size_t k = 0; k < FORKS_NUMBER; ++k)
    {   
        if (getpid() == mainpid)
        {
            pids[k] = fork();
            if (getpid() != mainpid)
            {
                break;
            }
        }
    }


    for (size_t i = 0; i < FORKS_NUMBER; ++i)
    {
        if (pids[i] == 0)
        {
            if (i < idxs_len)
            {
                down_limit = i ? idxs[i - 1] : 0;
                upper_limit = idxs[i];
                close(fd[0]);
                for (size_t j = down_limit; j < upper_limit; ++j)
                {   
                    if (isalpha(str[j]))
                    {
                        is_word = 1;
                        curr_len++;
                    }
                    else if (str[j] == ' ' || str[j] == '\n' || str[j] == '\0')
                    {
                        if (is_word)
                        {
                            if (curr_len > longest_words)
                            {
                                longest_words = curr_len;
                            }
                        }
                        curr_len = 0;
                        is_word = 0;
                    }
                    else
                    {
                        curr_len = 0;
                        is_word = 0;
                    }
                }
                write(fd[1], &longest_words, sizeof(size_t));
                close(fd[1]);
            }
            exit(EXIT_SUCCESS);
        }
    }

    if (getpid() == mainpid)
    {
        close(fd[1]);
        for (size_t j = 0; j < FORKS_NUMBER; ++j)
        {
            pid_t wait_pid = waitpid(pids[j], &wait_status, 0);
            if (!wait_pid)
            {
                printf("An error occured while wait process\n");
            }
        }
        for (size_t j = 0; j < idxs_len; ++j)
        {
            read(fd[0], &longest_words, sizeof(size_t));
            if (longest_words > max_word)
            {
                max_word = longest_words;
            }
        }
        close(fd[0]);
    }

    return max_word;
}