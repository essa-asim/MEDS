#include <stdio.h>
#include "decoder.h"

int main(void)
{
    uint32_t tests[] =
    {
        0x003100B3,
        0x40310133,
        0x00500113,
        0x00012083
    };

    decoded_instr_t decoded;
    char assembly[100];

    for (int i = 0; i < 4; i++)
    {
        decode_instruction(tests[i], &decoded);
        instruction_to_string(&decoded, assembly);

        printf("%08X -> %s\n", tests[i], assembly);
    }

    return 0;
}