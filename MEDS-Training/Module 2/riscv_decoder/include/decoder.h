#ifndef DECODER_H
#define DECODER_H

#include "common.h"

/* Decode all instruction fields */
void decode_instruction(uint32_t instruction,
                        decoded_instr_t *decoded);

/* Convert decoded instruction into assembly string */
void instruction_to_string(const decoded_instr_t *decoded,
                           char *buffer);

#endif