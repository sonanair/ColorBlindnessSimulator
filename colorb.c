#include "bmp.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *inputFile = NULL;
    char *outputFile = NULL;

    // Handle command-line options
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
        } else if (strcmp(argv[i], "-h") == 0) {
            fprintf(stdout, "Usage: color -i infile -o outfile\n");
            fprintf(stdout, "       color -h\n");
            return EXIT_SUCCESS;
        } else {
            printf("Invalid option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    // Check if both input and output files are provided
    if (inputFile == NULL || outputFile == NULL) {
        printf("Input and/or output file not specified.\n");
        return EXIT_FAILURE;
    }

    // Process the BMP files
    FILE *fin = fopen(inputFile, "rb");
    if (!fin) {
        printf("Error opening input file.\n");
        return EXIT_FAILURE;
    }

    BMP *bmp = bmp_create(fin);

    if (!bmp) {
        printf("Error creating BMP structure.\n");
        fclose(fin);
        return EXIT_FAILURE;
    }

    fclose(fin); // Close the input file after reading

    bmp_reduce_palette(bmp);

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) {
        printf("Error opening output file.\n");
        bmp_free(&bmp);
        return EXIT_FAILURE;
    }

    bmp_write(bmp, fout);

    fclose(fout); // Close the output file after writing

    bmp_free(&bmp);

    printf("Successfully processed BMP file.\n");

    return EXIT_SUCCESS;
}
