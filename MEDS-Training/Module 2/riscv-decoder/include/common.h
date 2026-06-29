#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ---------------- Constants ---------------- */

#define MEMORY_SIZE     65536
#define INSTRUCTION_SIZE 4

/* Bit Masks */
#define OPCODE_MASK 0x7F
#define RD_MASK     0x1F
#define RS_MASK     0x1F
#define FUNCT3_MASK 0x07
#define FUNCT7_MASK 0x7F

/* ---------------- Function-like Macro ---------------- */

#define EXTRACT_BITS(value, high, low) \
    (((value) >> (low)) & ((1U << ((high) - (low) + 1)) - 1))

/* ---------------- Opcodes ---------------- */

typedef enum
{
    OP_LOAD    = 0x03,
    OP_I_TYPE  = 0x13,
    OP_AUIPC   = 0x17,
    OP_STORE   = 0x23,
    OP_R_TYPE  = 0x33,
    OP_LUI     = 0x37,
    OP_BRANCH  = 0x63,
    OP_JALR    = 0x67,
    OP_JAL     = 0x6F,
    OP_SYSTEM  = 0x73

} opcode_t;

/* ---------------- Decoded Instruction ---------------- */

typedef struct
{
    uint32_t raw;

    uint32_t opcode;

    uint32_t rd;

    uint32_t rs1;

    uint32_t rs2;

    uint32_t funct3;

    uint32_t funct7;

    int32_t imm;

} decoded_instr_t;

#endif
