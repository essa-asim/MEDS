#include "decoder.h"
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------
 * Decode a 32-bit RISC-V instruction into its fields
 *---------------------------------------------------------*/
void decode_instruction(uint32_t instruction,
                        decoded_instr_t *decoded)
{
    /* Store the original instruction */
    decoded->raw = instruction;

    /* Common fields */
    decoded->opcode = EXTRACT_BITS(instruction, 6, 0);
    decoded->rd     = EXTRACT_BITS(instruction, 11, 7);
    decoded->funct3 = EXTRACT_BITS(instruction, 14, 12);
    decoded->rs1    = EXTRACT_BITS(instruction, 19, 15);
    decoded->rs2    = EXTRACT_BITS(instruction, 24, 20);
    decoded->funct7 = EXTRACT_BITS(instruction, 31, 25);

    /* Immediate value
       (will be updated later for different instruction types) */
    decoded->imm = 0;
}


/*----------------------------------------------------------
 * Convert decoded instruction to assembly string
 *---------------------------------------------------------*/
void instruction_to_string(const decoded_instr_t *decoded,
                           char *buffer)
{
    switch (decoded->opcode)
    {
        case OP_R_TYPE:

            switch (decoded->funct3)
            {
                case 0x0:

                    if (decoded->funct7 == 0x00)
                    {
                        sprintf(buffer,
                                "add x%u, x%u, x%u",
                                decoded->rd,
                                decoded->rs1,
                                decoded->rs2);
                    }
                    else if (decoded->funct7 == 0x20)
                    {
                        sprintf(buffer,
                                "sub x%u, x%u, x%u",
                                decoded->rd,
                                decoded->rs1,
                                decoded->rs2);
                    }
                    else
                    {
                        strcpy(buffer, "UNKNOWN");
                    }

                    break;

                case 0x1:

                    sprintf(buffer,
                            "sll x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                case 0x2:

                    sprintf(buffer,
                            "slt x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                case 0x3:

                    sprintf(buffer,
                            "sltu x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                case 0x4:

                    sprintf(buffer,
                            "xor x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                case 0x5:

                    if (decoded->funct7 == 0x00)
                    {
                        sprintf(buffer,
                                "srl x%u, x%u, x%u",
                                decoded->rd,
                                decoded->rs1,
                                decoded->rs2);
                    }
                    else if (decoded->funct7 == 0x20)
                    {
                        sprintf(buffer,
                                "sra x%u, x%u, x%u",
                                decoded->rd,
                                decoded->rs1,
                                decoded->rs2);
                    }
                    else
                    {
                        strcpy(buffer, "UNKNOWN");
                    }

                    break;

                case 0x6:

                    sprintf(buffer,
                            "or x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                case 0x7:

                    sprintf(buffer,
                            "and x%u, x%u, x%u",
                            decoded->rd,
                            decoded->rs1,
                            decoded->rs2);
                    break;

                default:

                    strcpy(buffer, "UNKNOWN");
                    break;
            }

            break;

        default:

            strcpy(buffer, "UNKNOWN");
            break;
    }
}
