# &#956;nifti.h

Minimal header only NIfTI definitions and utilities.

## Features

- Captures entire NifTI 1.1 and 2 standard and extension codes (e.g. CIFTI)
- Portable & (single) header only
- Zero (heap) allocations
- Comprehensive documentation for all definitions
- Utility functions for
  - Determining endianness & file standard
  - Byte-swapping
  - Computed header fields
  - Converting between NIfTI 1.1 and 2 file header definitions
  - Resolving header codes to human readable strings
  - Debug printing


## Background, Goals & Non-Goals

The hardest part about working with NIfTI files is handling the large number of fields and enum codes both standards describe.
This project makes heavy use of code generation to provide a single C/C++ header that captures everything described in the standard.

**Goals**

- Complete & comprehensive definitions and documentation for NIfTI 1.1 & 2
- Maximal performance
- Portablility

**Non-Goals**

- Handle I/O (Platform dependent)
- Handle GZIP compression (There are many optimized libraries out there, pick one)


**Over all:** Make it easy to implement NIfTI parsing and writing without making any assumptions about platforms.

## Minimal example

1. Copy `include/unifti.h` to your C/C++ project.
2. `main.c`:

```C
#include <stdio.h>
#include <unifti.h>

int main() {
  unifti_n1_header_t header;
  FILE *fp = fopen ("file.nii", "rb");
  if (fread(&header, sizeof(unifti_n1_header_t), 1, fp) != 1) {
    return 1;
  }
  fclose(fp);
  unifti_n1_header_print(&header);
  return 0;
}
```

3. More complex examples can be found under `src/`.