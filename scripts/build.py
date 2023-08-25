from dataclasses import dataclass
import pathlib as pl
from . import utils, cg, ksy

PATH_ROOT = pl.Path(__file__).parent.parent
PATH_DIST = PATH_ROOT / "src"
PATH_NIFTI_KSY = PATH_ROOT / 'BrainParsers' / 'formats' / 'nifti.ksy'


PROJECT_NAME = 'cnifti'
C_VERSION = 1



def main():

    cbuild = build_n1header()

    with open(PATH_DIST / f'{cbuild.header_name}.h', 'w', encoding='utf8') as f:
        f.write(cbuild.build_header())


def build_n1header():
    buf = cg.CHeaderBuilder(
        header_name=PROJECT_NAME
    )


    # static assert
    static_assert_alias = cg.cn_define('static_assert')
    buf.header += cg.section(f"""
#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define {static_assert_alias}(COND,MSG) static_assert(COND,MSG)
#else
#define {static_assert_alias}(COND,MSG)
#endif
""")
    
    # printf
    printf_alias = cg.cn_define("printf")
    buf.header += f"\n\n#ifndef {printf_alias}\n#include <stdio.h>\n#define {printf_alias} printf\n#endif\n\n"

    # struct packing

    #buf.header += '\n'.join([
    #    f"#ifndef {cg.cn_define('struct_packed')}",
    #    cg.cdefine("struct_packed", "__attribute__((packed, aligned(1)))"),
    #    f"#endif"
    #])

    # standard types
    buf.header += '\n'.join([
        '#include <stddef.h> // NULL, size_t',
        '#include <stdint.h> // int32_t, uint32_t, int64_t, uint64_t',
        '#include <stdbool.h> // bool',
        '#include <string.h> // memcpy, strcmp'
    ])

    
    # version
    buf.body += f'\n/** @brief version */'
    buf.body += f"\n#define {cg.cn_define('version')} {C_VERSION}"


    ks = ksy.KsyGrammar(PATH_NIFTI_KSY)

    # enums

    for enum in ks.iter_enums():
        buf.body += enum.cdefine_all()
        buf.body += '\n'

        enum.cdynamic_name().write(buf)
        enum.cdynamic_from_name().write(buf)

    
    # enum utilities

    buf.body += cg.comment(f'Datatype size') + '\n\n'


    ksy_enum_dt = ksy.KsyEnum('dt', ks.ksy)
    for enum in ksy_enum_dt.values:
        buf.body += cg.docstring(brief=f'{ksy_enum_dt.name} {enum.name} size (bytes)') + '\n'
        bitsize = utils.trailing_int(enum.name)
        if bitsize is None:
            if enum.name == 'unknown':
                bitsize = 0
            elif enum.name == 'binary':
                bitsize = 1  # annoying edge case
            else:
                assert False
        bytesize = bitsize // 8
        buf.body += f"#define {enum.cn()}_SIZE {bytesize}\n"

    buf.body += f'\n'
        
    # Nifti headers
    
    n1_header_struct = ksy.KsyStruct('n1_header', ks.n1()['types']['header'])
    n2_header_struct = ksy.KsyStruct('n2_header', ks.n2()['types']['header'])
    extension_indicator_struct = ksy.KsyStruct('extension_indicator', ks.n1()['types']['extension_indicator'])
    extension_header_struct = ksy.KsyStruct('extension_header', ks.n1()['types']['extension']['types']['extension_header'])

    buf.body += cg.big_comment(f'Nifti headers') + '\n\n'

    # nifti 1 header definition
    ksy.build_struct(n1_header_struct).write(buf, memory_packing=False)

    buf.body += f'{static_assert_alias}(sizeof({cg.cn_struct_type(n1_header_struct.name)}) == 348, "nifti1 header size is not 348 bytes");\n'
    
    # nifti 2 header definition
    ksy.build_struct(n2_header_struct).write(buf, memory_packing=True)
    buf.body += f'{static_assert_alias}(sizeof({cg.cn_struct_type(n2_header_struct.name)}) == 540, "nifti2 header size is not 540 bytes");\n'

    for ksy_struct in [n1_header_struct, n2_header_struct]:
        for cfunc in ksy.build_comp_field_funcs(ksy_struct):
            cfunc.write(buf)

    # header extension definition
    ksy.build_struct(extension_indicator_struct).write(buf, memory_packing=False)
    buf.body += f'{static_assert_alias}(sizeof({cg.cn_struct_type(extension_indicator_struct.name)}) == 4, "extension header size is not 4 bytes");\n'

    # header extension definition   
    ksy.build_struct(extension_header_struct).write(buf, memory_packing=False)
    buf.body += f'{static_assert_alias}(sizeof({cg.cn_struct_type(extension_header_struct.name)}) == 8, "extension header size is not 8 bytes");\n'

    # header union

    buf.body += f'\n'

    buf.body += cg.docstring(brief=f'Nifti header union') + '\n'
    buf.body += f'typedef union {cg.cn_struct_type("header")} {{\n'
    buf.body += cg.cindent(f'{cg.cn_struct_type(n1_header_struct.name)} n1_header;\n')
    buf.body += cg.cindent(f'{cg.cn_struct_type(n2_header_struct.name)} n2_header;\n')
    buf.body += f'}} {cg.cn_struct_type("header")};\n\n'


    # Implementation
    
    buf.body += cg.big_comment(f'Implementation') + '\n'

    # enum dt -> size

    func_cases = '\n'.join([f'case {enum.cn()}: return {enum.cn()}_SIZE;' for enum in ksy_enum_dt.values])

    cg.CFunc(
        signature=f'int32_t {cg.cn_func_name("dt_size")}(int32_t {cg.cn_arg("dt")})',
        body=f"""
switch ({cg.cn_arg("dt")}) {{
{cg.cindent(func_cases)}
default: return 0;
}}""",
        prefix=cg.docstring(brief=f'Get datatype size in bytes') + '\n'
    ).write(buf, header_only=True)

    # print header



    for ksy_struct in [n1_header_struct, n2_header_struct]:
        ksy.build_print_struct(
            ksy_struct=ksy_struct,
            printf_alias=printf_alias,
            enum_unknown='<non standard>'
        ).write(buf)

    # peek

    cg.CFunc(
        signature=f'int32_t {cg.cn_func_name("peek")}(const uint32_t {cg.cn_arg("header_start")})',
        body=f"""
switch ({cg.cn_arg("header_start")}) {{
case 348: return 0;
case {utils.swap32(348)}: return {cg.cn_define("peek_swap")};
case 540: return {cg.cn_define("peek_nifti2")};
case {utils.swap32(540)}: return {cg.cn_define("peek_nifti2")} & {cg.cn_define("peek_swap")};
default: return -1;
}}""",
        prefix='\n'.join([
            cg.cdefine('peek_nifti2', 0b01),
            cg.cdefine('peek_swap', 0b10),
            cg.docstring(brief=f'Peek at first 4 bytes of header to determine nifti version and endianness.\n'
                            f'Return value can be bit compared with {cg.cn_define("peek_*")} values.\n'
                            f'If return value is -1 this is not a nifti header.')
        ])
    ).write(buf, header_only=True)

    """
    Untested potentially faster version with perfect hashing (but less file validity guarantees):
    
static inline int32_t cnifti_peek_fast(const uint32_t t_header_start) {
  static int32_t lookup[7] = { -1, CNIFTI_PEEK_NIFTI2, -1, CNIFTI_PEEK_SWAP, CNIFTI_PEEK_NIFTI2 & CNIFTI_PEEK_SWAP, 0, -1};
  return lookup[t_header_start % 7];
}

    """

    # Byte-swap

    for ksy_struct in [n1_header_struct, n2_header_struct]:
        ksy.build_byteswap_struct(
            ksy_struct=ksy_struct,
        ).write(buf)

    
    # Data access

    for ksy_struct in [n1_header_struct, n2_header_struct]:


        cg.CFunc(
            signature=f'int64_t {cg.cn_func_name(f"{ksy_struct.name}_array_size")}(const {cg.cn_struct_type(ksy_struct.name)} *{cg.cn_arg(ksy_struct.name)})',
            body=f"""
int64_t size = {cg.cn_arg(ksy_struct.name)}->bitpix / 8;
for (int i = 0; i < {cg.cn_arg(ksy_struct.name)}->dim[0]; ++i) {{ size *= {cg.cn_arg(ksy_struct.name)}->dim[i+1]; }}
return size;""",
            prefix=cg.docstring(brief=f'Calculate {ksy_struct.name} data array size (in bytes).'),
        ).write(buf, header_only=True)


    return buf


if __name__ == '__main__':
    main()
    