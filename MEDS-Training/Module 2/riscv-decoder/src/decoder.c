#include "decoder.h"
#include <stdio.h>
#include <string.h>

/* Private helper functions */
static void decode_r_type(const decoded_instr_t *decoded, char *buffer);
static void decode_i_type(const decoded_instr_t *decoded, char *buffer);
static void decode_load(const decoded_instr_t *decoded, char *buffer);
static void decode_store(const decoded_instr_t *decoded, char *buffer);
static void decode_branch(const decoded_instr_t *decoded, char *buffer);
static void decode_u_type(const decoded_instr_t *decoded, char *buffer);
static void decode_jump(const decoded_instr_t *decoded, char *buffer);


 /* Decode a 32-bit RISC-V instruction into its fields */

void decode_instruction(uint32_t instruction,
                        decoded_instr_t *decoded)
{
    decoded->raw = instruction;

    decoded->opcode = EXTRACT_BITS(instruction, 6, 0);
    decoded->rd     = EXTRACT_BITS(instruction, 11, 7);
    decoded->funct3 = EXTRACT_BITS(instruction, 14, 12);
    decoded->rs1    = EXTRACT_BITS(instruction, 19, 15);
    decoded->rs2    = EXTRACT_BITS(instruction, 24, 20);
    decoded->funct7 = EXTRACT_BITS(instruction, 31, 25);

    switch (decoded->opcode)
    {
        /* I-Type */
        case OP_I_TYPE:
        case OP_LOAD:
        case OP_JALR:

            decoded->imm = (int32_t)instruction >> 20;
            break;

        /* S-Type */
        case OP_STORE:

            decoded->imm =
                (EXTRACT_BITS(instruction,31,25) << 5) |
                 EXTRACT_BITS(instruction,11,7);

            if(decoded->imm & 0x800)
                decoded->imm |= 0xFFFFF000;

            break;

        /* B-Type */
        case OP_BRANCH:

            decoded->imm =
                (EXTRACT_BITS(instruction,31,31) << 12) |
                (EXTRACT_BITS(instruction,7,7) << 11) |
                (EXTRACT_BITS(instruction,30,25) << 5) |
                (EXTRACT_BITS(instruction,11,8) << 1);

            if(decoded->imm & 0x1000)
                decoded->imm |= 0xFFFFE000;

            break;

        /* U-Type */
        case OP_LUI:
        case OP_AUIPC:

            decoded->imm = instruction & 0xFFFFF000;
            break;

        /* J-Type */
        case OP_JAL:

            decoded->imm =
                (EXTRACT_BITS(instruction,31,31) << 20) |
                (EXTRACT_BITS(instruction,19,12) << 12) |
                (EXTRACT_BITS(instruction,20,20) << 11) |
                (EXTRACT_BITS(instruction,30,21) << 1);

            if(decoded->imm & 0x100000)
                decoded->imm |= 0xFFE00000;

            break;

        default:
            decoded->imm = 0;
            break;
    }
}


 /* Convert decoded instruction to assembly string */

void instruction_to_string(const decoded_instr_t *decoded,
                           char *buffer)
{
    switch(decoded->opcode)
    {
        case OP_R_TYPE:
            decode_r_type(decoded, buffer);
            break;

        case OP_I_TYPE:
            decode_i_type(decoded, buffer);
            break;
        
        case OP_LOAD:
            decode_load(decoded, buffer);
            break;

        case OP_STORE:
            decode_store(decoded, buffer);
            break;

        case OP_BRANCH:
            decode_branch(decoded, buffer);
            break;

        case OP_LUI:
        case OP_AUIPC:
            decode_u_type(decoded, buffer);
            break;

        case OP_JAL:
        case OP_JALR:
            decode_jump(decoded, buffer);
            break;

        default:
            strcpy(buffer, "UNKNOWN");
            break;
    }
}

static void decode_r_type(const decoded_instr_t *decoded,
                          char *buffer)
{
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
}

static void decode_i_type(const decoded_instr_t *decoded,
                          char *buffer)
{
    switch (decoded->funct3)
    {
        case 0x0:
            sprintf(buffer,
                    "addi x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        case 0x1:
            sprintf(buffer,
                    "slli x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm & 0x1F);
            break;

        case 0x2:
            sprintf(buffer,
                    "slti x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        case 0x3:
            sprintf(buffer,
                    "sltiu x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        case 0x4:
            sprintf(buffer,
                    "xori x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        case 0x5:

            if (decoded->funct7 == 0x00)
            {
                sprintf(buffer,
                        "srli x%u, x%u, %d",
                        decoded->rd,
                        decoded->rs1,
                        decoded->imm & 0x1F);
            }
            else if (decoded->funct7 == 0x20)
            {
                sprintf(buffer,
                        "srai x%u, x%u, %d",
                        decoded->rd,
                        decoded->rs1,
                        decoded->imm & 0x1F);
            }
            else
            {
                strcpy(buffer, "UNKNOWN");
            }
            break;

        case 0x6:
            sprintf(buffer,
                    "ori x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        case 0x7:
            sprintf(buffer,
                    "andi x%u, x%u, %d",
                    decoded->rd,
                    decoded->rs1,
                    decoded->imm);
            break;

        default:
            strcpy(buffer, "UNKNOWN");
            break;
    }
}

static void decode_load(const decoded_instr_t *decoded,
                        char *buffer)
{
    switch(decoded->funct3)
    {
        case 0x0:
            sprintf(buffer,
                    "lb x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x1:
            sprintf(buffer,
                    "lh x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x2:
            sprintf(buffer,
                    "lw x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x4:
            sprintf(buffer,
                    "lbu x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x5:
            sprintf(buffer,
                    "lhu x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        default:
            strcpy(buffer,"UNKNOWN");
    }
}

static void decode_store(const decoded_instr_t *decoded,
                         char *buffer)
{
    switch(decoded->funct3)
    {
        case 0x0:
            sprintf(buffer,
                    "sb x%u, %d(x%u)",
                    decoded->rs2,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x1:
            sprintf(buffer,
                    "sh x%u, %d(x%u)",
                    decoded->rs2,
                    decoded->imm,
                    decoded->rs1);
            break;

        case 0x2:
            sprintf(buffer,
                    "sw x%u, %d(x%u)",
                    decoded->rs2,
                    decoded->imm,
                    decoded->rs1);
            break;

        default:
            strcpy(buffer,"UNKNOWN");
    }
}

static void decode_branch(const decoded_instr_t *decoded,
                          char *buffer)
{
    switch(decoded->funct3)
    {
        case 0x0:
            sprintf(buffer,
                    "beq x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        case 0x1:
            sprintf(buffer,
                    "bne x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        case 0x4:
            sprintf(buffer,
                    "blt x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        case 0x5:
            sprintf(buffer,
                    "bge x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        case 0x6:
            sprintf(buffer,
                    "bltu x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        case 0x7:
            sprintf(buffer,
                    "bgeu x%u, x%u, %d",
                    decoded->rs1,
                    decoded->rs2,
                    decoded->imm);
            break;

        default:
            strcpy(buffer,"UNKNOWN");
    }
}

static void decode_u_type(const decoded_instr_t *decoded,
                          char *buffer)
{
    switch(decoded->opcode)
    {
        case OP_LUI:

            sprintf(buffer,
                    "lui x%u, %d",
                    decoded->rd,
                    decoded->imm >> 12);
            break;

        case OP_AUIPC:

            sprintf(buffer,
                    "auipc x%u, %d",
                    decoded->rd,
                    decoded->imm >> 12);
            break;

        default:

            strcpy(buffer, "UNKNOWN");
            break;
    }
}

static void decode_jump(const decoded_instr_t *decoded,
                        char *buffer)
{
    switch(decoded->opcode)
    {
        case OP_JAL:

            sprintf(buffer,
                    "jal x%u, %d",
                    decoded->rd,
                    decoded->imm);
            break;

        case OP_JALR:

            sprintf(buffer,
                    "jalr x%u, %d(x%u)",
                    decoded->rd,
                    decoded->imm,
                    decoded->rs1);
            break;

        default:

            strcpy(buffer, "UNKNOWN");
            break;
    }
}
