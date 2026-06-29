#include <stdio.h>
#include <stdlib.h>

#include "decoder.h"

int main(int argc, char *argv[])
{
    /* Check command-line arguments */
    if (argc != 2)
    {
        printf("Usage: %s <hex_file>\n", argv[0]);
        return 1;
    }

    /* Open hex file */
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    printf("RISC-V RV32I Instruction Decoder\n");
    printf("=============================================\n\n");

    printf("%-12s %-10s %s\n", "Address", "Hex", "Assembly");
    printf("----------------------------------------------------------\n");

    char line[32];
    uint32_t instruction;
    uint32_t address = 0;

    decoded_instr_t decoded;
    char assembly[100];

    while (fgets(line, sizeof(line), fp))
    {
        instruction = (uint32_t)strtoul(line, NULL, 16);

        decode_instruction(instruction, &decoded);

        instruction_to_string(&decoded, assembly);

        printf("0x%08X %-10s %s\n",
               address,
               line,
               assembly);

        address += 4;
    }

    fclose(fp);

    return 0;
}
