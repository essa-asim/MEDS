#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

int load_hex_file(const char *filename,
                  uint32_t memory[],
                  int max_instructions)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("Error opening hex file");
        return -1;
    }

    char line[32];
    int count = 0;

    while (fgets(line, sizeof(line), fp) &&
           count < max_instructions)
    {
        memory[count] =
            (uint32_t)strtoul(line, NULL, 16);

        count++;
    }

    fclose(fp);

    return count;
}
