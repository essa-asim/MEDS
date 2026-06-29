#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "memory.h"

#define MAX_INSTRUCTIONS 1024

int main(int argc, char *argv[])
{
    int unknown = 0;
    /* Check command-line arguments */
    if (argc != 2)
    {
        printf("Usage: %s <hex_file>\n", argv[0]);
        return 1;
    }

    /* Memory to store instructions */
    uint32_t memory[MAX_INSTRUCTIONS];

    /* Load hex file */
    int instruction_count = load_hex_file(argv[1],
                                          memory,
                                          MAX_INSTRUCTIONS);

    if (instruction_count < 0)
    {
        return 1;
    }

    printf("RISC-V RV32I Instruction Decoder\n");
    printf("=============================================\n\n");

    printf("%-12s %-10s   %s\n", "Address", "Machine Code", "Assembly");
    printf("----------------------------------------------------------\n");

    decoded_instr_t decoded;
    char assembly[100];

    uint32_t address = 0;

    for (int i = 0; i < instruction_count; i++)
    {
        decode_instruction(memory[i], &decoded);

        instruction_to_string(&decoded, assembly);

        printf("0x%08X   %08X       %s\n",
               address,
               memory[i],
               assembly);

        address += 4;

        if(strcmp(assembly,"UNKNOWN")==0)
        unknown++;

    }

    printf("\n");
    printf("---------------------------------------\n");
    printf("Decoded Instructions : %d\n", instruction_count);
    printf("Unknown Instructions : %d\n", unknown);
    printf("Successfully Decoded : %d\n", instruction_count - unknown);

    return 0;
}