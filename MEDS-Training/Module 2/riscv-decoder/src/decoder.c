#include "decoder.h"

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
