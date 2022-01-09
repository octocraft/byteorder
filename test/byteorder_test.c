
#if defined(_MSC_VER)
#pragma warning (disable : 4464)
#pragma warning (disable : 4668)
#pragma warning (disable : 4710)
#pragma warning (disable : 4820)
#pragma warning (disable : 5045)
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../byteorder.h"

typedef struct cp_t {
    union {
        uint32_t u;
        unsigned char c[4];
    } cp;
    unsigned char t;
} cp_t;

int ctutf8_test(unsigned int j)
{
    unsigned int i;
    cp_t cp;
    unsigned char str[][5] = { "*", "®", "⚧", "👭" };
    cp.t = '\0';

    printf("Test %d: codepoint to utf8\n", j);

    for(i = 0; i < sizeof(str)/sizeof(str[0]); i += 1)
    {
        cp.cp.u = *((uint32_t*) (str[i]));
        printf(" %d: %8x - %s\n", i, cp.cp.u, cp.cp.c);

        switch(cp.cp.u)
        {
            case BO_CTUTF8(0x2A): 
            case BO_CTUTF8(0xAE): 
            case BO_CTUTF8(0x26A7): 
            case BO_CTUTF8(0x1F46D): break;
            default: 
            fprintf(stderr, "Unexpected %x\n", cp.cp.u);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


int main(void)
{
    unsigned int i;
    int (*tests[])(unsigned int) = { ctutf8_test };

    for(i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++)
    {
        if(tests[i](i)) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
