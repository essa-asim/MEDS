#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

/* Load instructions from a hex file */
int load_hex_file(const char *filename,
                  uint32_t memory[],
                  int max_instructions);

#endif
