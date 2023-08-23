#include "cnifti.h"
#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    char *filename = argv[1];

    cnifti_header_t buf;

    FILE *ptr;
    ptr = fopen(filename, "rb");

    if (fread(&buf, sizeof(cnifti_n1_header_t), 1, ptr) != 1) {
        printf("Error: Could not read nifti1 header\n");
        return 0;
    }

    uint32_t peek = cnifti_peek(*((uint32_t *) &buf));


    if (peek == -1) {
        printf("Error: Not a valid nifti file\n");
        return 0;
    }
    if (peek & CNIFTI_PEEK_NIFTI2) {

        // Read the rest of the header
        if (fread(((uint8_t *) &buf) + sizeof(cnifti_n1_header_t), sizeof(cnifti_n2_header_t) - sizeof(cnifti_n1_header_t), 1, ptr) != 1) {
            printf("Error: Could not read nifti2 header\n");
            return 0;
        } 

        cnifti_n2_header_t *header = &buf.n2_header;

        if (peek & CNIFTI_PEEK_SWAP) {
            printf("Byte swapping header\n");
            cnifti_n2_header_swap(header);
        }

        printf("Nifti2 header:\n");
        cnifti_n2_header_print(header);
        printf("Data array size: %f MB\n", (float)cnifti_n2_header_array_size(header) / 1024 / 1024);

    } else {
        cnifti_n1_header_t *header = &buf.n1_header;

        if (peek & CNIFTI_PEEK_SWAP) {
            printf("Byte swapping header\n");
            cnifti_n1_header_swap(header);
        }
        
        printf("Nifti1 header:\n");
        cnifti_n1_header_print(header);
        printf("Data array size: %f MB\n", (float)cnifti_n1_header_array_size(header) / 1024 / 1024);
    }

    return 1;
}
