#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ENDIAN_CONVERT_16(x)        ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))
#define ENDIAN_CONVERT_32(x)        ((ENDIAN_CONVERT_16((x) & 0xFFFF) << 16) | (ENDIAN_CONVERT_16(((x) >> 16) & 0xFFFF)))


static void usage(void)
{
    printf("Usage:\n");
    printf("fdump FILE\n");
}

int main(int argc, char **argv)
{
    FILE *in = stdin;

    uint8_t buf[16];
    size_t r;
    uint32_t size_r = 0;

    int i = 0;


    if (!*(argv + 1)) {
        usage();
        exit(1);
    }

    printf("Dump %s\n", *(argv + 1));

    in = fopen(*(argv + 1), "rb");
    if (!in) {
        printf("Fail to open %s\n", *(argv + 1));
        return 1;
    }

    while (1) {
        if (feof(in) || ferror(in)) {
            break;
        }
        r = fread(buf, 1, sizeof(buf), in);
        size_r += r;

        for (i = 0; i < r; i++) {
            printf("%02X ", buf[i]);
        }
        printf("\n");
    }

    fclose(in);

    printf("Read : %d\n", size_r);
    printf("Done!\n\n");

    return 0;
}

/* vim: set ts=4 sw=4 tw=0 list : */
