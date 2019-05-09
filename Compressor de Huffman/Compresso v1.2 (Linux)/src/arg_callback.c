#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <sys/types.h>
#if !defined(linux) && !defined(__linux) && !defined(__linux__)
    #include <sys/sysctl.h>
#endif

#include "arg_callback.h"

static uint64_t getAvailableMemory()
{
    static uint64_t size = 0;

#if defined(linux) || defined(__linux) || defined(__linux__)
    if (size == 0)
    {
        long page_size = 0;
        long page_count = 0;

        page_size = sysconf(_SC_PAGESIZE);
        page_count = sysconf(_SC_PHYS_PAGES);
        size = page_size * page_count;
    }
#else
    if (size == 0)
    {
        int mib[2] = {CTL_HW, HW_MEMSIZE};
        size_t len = sizeof(size);

        sysctl(mib, 2, &size, &len, NULL, 0);
    }
#endif

    return size;
}

bool set_block_size(const char *option, const char *arg, void *userdata)
{
    static uint64_t page_size = 0;
    static uint64_t page_count = 0;

    if (arg == NULL)
        return false;

    uint32_t *block_size = (uint32_t*)userdata;
    char *endptr;
    uint64_t tmp = strtoll(arg, &endptr, 10);

    if (endptr == arg || tmp < 1)
    {
        if (option != NULL)
            fprintf(stderr, "O valor do tamanho do bloco de memoria deve ser um inteiro valido\n");
        return false;
    }

    if (strcmp(endptr, "kB") == 0)
        tmp *= 1024;
    else if (strcmp(endptr, "MB") == 0)
        tmp *= 1024 * 1024;
    else if (strcmp(endptr, "GB") == 0)
        tmp *= 1024 * 1024 * 1024;
    else
    {
        if (option != NULL)
            fprintf(stderr, "O sufixo do tamanho do bloco de memoria pode ser kB ou MB ou GB\n");
        return false;
    }

    if (page_size == 0)
        page_size = sysconf(_SC_PAGESIZE);
    if (page_count == 0)
        page_count = sysconf(_SC_PHYS_PAGES);

    if (tmp >= getAvailableMemory())
    {
        if (option != NULL)
            fprintf(stderr, "O tamanho do bloco de memoria requisitado é maior que o espaco em memoria\n");
        return false;
    }

    if (tmp > UINT_MAX)
    {
        if (option != NULL)
            fprintf(stderr, "O tamanho do bloco de memoria é grande demais: definindo-o para o valor maximo: %u bytes\n", UINT_MAX);
        *block_size = UINT_MAX;
    }
    else
        *block_size = tmp;

    return true;
}

bool set_output_filename(const char *option, const char *arg, void *userdata)
{
    (void)option;

    const char **out_filename = (const char**)userdata;
    if (strlen(arg) == 0)
    {
        fprintf(stderr, "Voce precisa especificar um nome pro arquivo de saida\n");
        return false;
    }

    *out_filename = arg;
    return true;
}

bool set_thread_number(const char *option, const char *arg, void *userdata)
{
    if (arg == NULL)
        return false;

    int *number_of_thread = (int*)userdata;
    char *endptr;
    int tmp = strtol(arg, &endptr, 10);

    if (arg == endptr || tmp < 1)
    {
        if (option != NULL)
            fprintf(stderr, "O numero de threads deve ser um inteiro valido\n");
        return false;
    }

    *number_of_thread = tmp;
    return true;
}

bool set_memlimit(const char *option, const char *arg, void *userdata)
{
    if (arg == NULL)
        return false;

    uint64_t *max_memory = (uint64_t*)userdata;
    char *endptr;
    uint64_t tmp = strtoll(arg, &endptr, 10);

    if (endptr == arg || tmp < 1)
    {
        if (option != NULL)
            fprintf(stderr, "Voce precisa especificar um numero valido para o tamanho de memoria\n");
        return false;
    }

    if (strcmp(endptr, "kB") == 0)
        tmp *= 1024;
    else if (strcmp(endptr, "MB") == 0)
        tmp *= 1024 * 1024;
    else if (strcmp(endptr, "GB") == 0)
        tmp *= 1024 * 1024 * 1024;
    else
    {
        if (option != NULL)
            fprintf(stderr, "O sufixo de memoria maxima pode ser kB ou MB ou GB\n");
        return false;
    }

    *max_memory = tmp;
    return true;
}

bool set_compress(const char *option, const char *arg, void *userdata)
{
    (void)option;
    (void)arg;

    int *compression = (int*)userdata;
    *compression = 1;
    return true;
}

bool set_decompress(const char *option, const char *arg, void *userdata)
{
    (void)option;
    (void)arg;

    int *compression = (int*)userdata;
    *compression = 0;
    return true;
}

bool set_test(const char *option, const char *arg, void *userdata)
{
    (void)option;
    (void)arg;

    int *test_integrity = (int*)userdata;
    *test_integrity = 1;
    return true;
} 