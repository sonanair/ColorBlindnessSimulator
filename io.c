#include "io.h"

#include <stdlib.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);
    if (result == EOF) {
        fprintf(stderr, "Fatal Error: Unexpected end of file\n");
        exit(EXIT_FAILURE);
    }
    *px = (uint8_t) result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    uint8_t byte1, byte2;
    uint16_t result = 0;
    read_uint8(fin, &byte1);
    read_uint8(fin, &byte2);
    result |= byte2;
    result <<= 8;
    result |= byte1;
    *px = result;
}

void read_uint32(FILE *fin, uint32_t *px) {
    uint16_t word1, word2;
    uint32_t result = 0;
    read_uint16(fin, &word1);
    read_uint16(fin, &word2);
    result |= word2;
    result <<= 16;
    result |= word1;
    *px = result;
}

void write_uint8(FILE *fout, uint8_t x) {
    int result = fputc(x, fout);
    if (result == EOF) {
        fprintf(stderr, "Unable to write file\n");
        exit(EXIT_FAILURE);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    write_uint8(fout, x & 0xFF);
    write_uint8(fout, (x >> 8) & 0xFF);
}

void write_uint32(FILE *fout, uint32_t x) {
    write_uint16(fout, x & 0xFFFF);
    write_uint16(fout, (x >> 16) & 0xFFFF);
}
