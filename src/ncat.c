#include <stdio.h> 
#include <stdlib.h> 

#include "unifti.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    char *filename = argv[1];

    unifti_header_t buf;

    FILE *ptr;
    ptr = fopen(filename, "rb");

    if (fread(&buf, sizeof(unifti_n1_header_t), 1, ptr) != 1) {
        printf("Error: Could not read nifti1 header\n");
        return 0;
    }

    int32_t peek = unifti_peek(*((uint32_t *) &buf));

    if (peek == -1) {
        printf("Error: Not a valid nifti file\n");
        return 0;
    }
    if (peek & UNIFTI_PEEK_NIFTI2) {

        // Read the rest of the header
        if (fread(((uint8_t *) &buf) + sizeof(unifti_n1_header_t), sizeof(unifti_n2_header_t) - sizeof(unifti_n1_header_t), 1, ptr) != 1) {
            printf("Error: Could not read nifti2 header\n");
            return 0;
        } 

        unifti_n2_header_t *header = &buf.n2_header;

        if (peek & UNIFTI_PEEK_SWAP) {
            printf("Byte swapping header\n");
            unifti_n2_header_swap(header);
        }

        printf("Nifti2 header:\n");
        unifti_n2_header_print(header);
        printf("Data array size: %f MB\n", (float)unifti_n2_header_array_size(header) / 1024 / 1024);

    } else {
        unifti_n1_header_t *header = &buf.n1_header;

        if (peek & UNIFTI_PEEK_SWAP) {
            printf("Byte swapping header\n");
            unifti_n1_header_swap(header);
        }
        
        printf("Nifti1 header:\n");
        unifti_n1_header_print(header);
        printf("Data array size: %f MB\n", (float)unifti_n1_header_array_size(header) / 1024 / 1024);
    }
    
    unifti_extension_indicator_t ext_indicator;
    if (fread(&ext_indicator, sizeof(unifti_extension_indicator_t), 1, ptr) != 1) {
        printf("Error: Could not read header extension\n");
        return 0;
    }

    if (ext_indicator.has_extension) {
        unifti_extension_header_t ext_header;
        if (fread(&ext_header, sizeof(unifti_extension_header_t), 1, ptr) != 1) {
            printf("Error: Could not read header extension\n");
            return 0;
        }

        printf("Extension: %s\n", unifti_ecode_name(ext_header.ecode));
        printf("Extension size: %f MB\n", (float) (ext_header.esize - 8)  / 1024 / 1024);


        printf("Extension data:\n");
        printf("--------------\n");
        int32_t ext_data_size = MIN(ext_header.esize - 8, 400);
        uint8_t *ext_data = malloc(ext_data_size + 1);
        if (fread(ext_data, ext_data_size, 1, ptr) != 1) {
            printf("Error: Could not read header extension\n");
            return 0;
        }
        ext_data[ext_data_size] = '\0';

        printf("%s\n", ext_data);
        if (ext_data_size < ext_header.esize - 8) printf("...[truncated]\n");
        printf("--------------\n");
    } else {
        printf("File has no extension data.\n");
    }

    return 1;
}
