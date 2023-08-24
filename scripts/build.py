from dataclasses import dataclass
import struct
from typing import List, Optional
import yaml
import pathlib as pl
import argparse
import re
from . import utils

PATH_ROOT = pl.Path(__file__).parent.parent
PATH_DIST = PATH_ROOT / "src"
PATH_NIFTI_KSY = PATH_ROOT / 'BrainParsers' / 'formats' / 'nifti.ksy'


C_VERSION = 1
C_PREFIX = 'cnifti'
C_PREFIX_UP = C_PREFIX.upper()

C_INDENT = '  '

CTYPES = {
    's1': 'int8_t',
    'u1': 'uint8_t',
    's2': 'int16_t',
    'u2': 'uint16_t',
    's4': 'int32_t',
    'u4': 'uint32_t',
    's8': 'int64_t',
    'u8': 'uint64_t',
    'f4': 'float',
    'f8': 'double',
}

CTYPES_PRINTF = {
    's1': '%i',
    'u1': '%u',
    's2': '%i',
    'u2': '%u',
    's4': '%i',
    'u4': '%u',
    's8': '%li',
    'u8': '%lu',
    'f4': '%f',
    'f8': '%f',
}


def main():

    cbuild = build_n1header()

    with open(PATH_DIST / f'{cbuild.header_name}.h', 'w', encoding='utf8') as f:
        f.write(cbuild.build_header())
    with open(PATH_DIST / f'{cbuild.header_name}.c', 'w', encoding='utf8') as f:
        f.write(cbuild.build_impl())


class CHeaderBuilder:
    def __init__(self, header_guard_name: str, header_name: str):
        self.header_guard_name = header_guard_name
        self.header_name = header_name
        self.header = ''
        self.footer = ''
        self.body = ''
        self.impl_header = ''
        self.impl = ''

    def build_header(self) -> str:
        return(f"""
/** @file {self.header_name}.h */
               
#ifndef {self.header_guard_name}
#define {self.header_guard_name}

#ifdef __cplusplus
extern "C" {{
#endif

{self.header}

{self.body}

{self.footer}

#ifdef __cplusplus
}}
#endif

#endif /* {self.header_guard_name} */
""".strip())
    
    def build_impl(self) -> str:
        return(f"""
/** @file {self.header_name}.c */

#include "{self.header_name}.h"

{self.impl_header}

{self.impl}
""".strip())
    


def load_ksy(path_ksy: pl.Path):
    with open(path_ksy) as f:
        ksy = yaml.load(f, Loader=yaml.FullLoader)
    return ksy


def docstring_escape(s: str):
    return s.replace('@', '\\@')


def docstring(*args, **kwargs):
    s = '\n'.join([docstring_escape(a) for a in args]) + '\n'.join([f'@{k} {docstring_escape(v)}' for k, v in kwargs.items() if v is not None])

    if '\n' in s:
        s = s.replace("\n", "\n * ")
        return f'/**\n * {s}\n */'
    return f'/** {s} */'


def comment(*args, **kwargs):
    s = '\n'.join([docstring_escape(a) for a in args]) + '\n'.join([f'{k}: {docstring_escape(v)}' for k, v in kwargs.items() if v is not None])

    if '\n' in s:
        s = s.replace("\n", "\n * ")
        return f'/*\n * {s}\n */'
    return f'/* {s} */'


def dostring_quote_code(s: str):
    return f'`{s}`'



@dataclass
class KsyEnumValue:
    name: str
    value: int
    doc: Optional[str] = None


@dataclass
class KsyEnum:
    name: str
    values: List[KsyEnumValue]
    
    def __init__(self, name: str, ksy: dict):
        self.name = name
        ksy = ksy['enums'][name]
        self.values = []
        for var_value, var_name in ksy.items():
            if isinstance(var_name, dict):
                self.values.append(KsyEnumValue(
                    name=var_name['id'],
                    value=var_value,
                    doc=var_name['doc'] if 'doc' in var_name else None
                ))
            else:
                self.values.append(KsyEnumValue(
                    name=var_name,
                    value=var_value,
                    doc=None
                ))

def iter_enums(ksy: dict):
    for enum_name in ksy['enums'].keys():
        yield KsyEnum(enum_name, ksy)


def build_enum_name_impls(buf: CHeaderBuilder, enum: KsyEnum) -> None:

    # Enum -> Name

    buf.impl += comment(f'Get the {enum.name} name') + '\n'
    function_signature = f'const char *{C_PREFIX}_{enum.name}_name(int32_t {enum.name})'
    buf.impl += f'{function_signature} {{\n'
    buf.impl += f'{C_INDENT}switch ({enum.name}) {{\n'
    for enum_var in enum.values:
        ename = f'{C_PREFIX}_{enum.name}_{enum_var.name}'.upper()
        buf.impl += f'{C_INDENT}{C_INDENT}case {ename}: return {ename}_NAME;\n'
    buf.impl += f'{C_INDENT}{C_INDENT}default: return NULL;\n'
    buf.impl += f'{C_INDENT}}}\n'
    buf.impl += f'}}\n\n'
    
    buf.body += docstring(brief=f'Get the {enum.name} name') + '\n'
    buf.body += f'{function_signature};\n\n'

    # Name -> Enum
    
    if '#include <string.h>' not in buf.impl_header:
        buf.impl_header += '#include <string.h>\n'

    buf.impl += comment(f'Get the {enum.name} code from the {enum.name} name') + '\n'

    function_signature = f'int32_t {C_PREFIX}_{enum.name}_from_name(const char *{enum.name}_name)'

    buf.impl += f'{function_signature} {{\n'
    buf.impl += f'{C_INDENT}if ({enum.name}_name == NULL) return -1;\n'
    for enum_var in enum.values:
        ename = f'{C_PREFIX}_{enum.name}_{enum_var.name}'.upper()
        buf.impl += f'{C_INDENT}if (strcmp({enum.name}_name, {ename}_NAME) == 0) return {ename};\n'
    buf.impl += f'{C_INDENT}return -1;\n'
    buf.impl += f'}}\n\n'

    buf.body += docstring(brief=f'Get the {enum.name} code from the {enum.name} name') + '\n'
    buf.body += f'{function_signature};\n\n'


class CPrintfBuilder:
    def __init__(self, printf: str = 'printf'):
        self.printf = printf
        self.args: List[str] = []
        self.fbuf: str = ''

    def build(self) -> str:
        args_formatted = f",\n{C_INDENT*2}".join(self.args)
        fbuf_formatted = f"\\n\"\n{C_INDENT*2}\"".join(self.fbuf.split('\\n'))
        return f'{C_INDENT}{self.printf}(\n{C_INDENT*2}"{fbuf_formatted}",\n{C_INDENT*2}{args_formatted}\n{C_INDENT})'


def build_struct(buf: CHeaderBuilder, ksy: dict, name: str, enum_backref: dict, memory_packing=False) -> str:
    cheader_structname = f"{C_PREFIX}_{name}_t"

    if memory_packing:
        buf.body += f'// Disable alignment for this struct\n#pragma pack(push, 1)\n'

    buf.body += f'typedef struct {{\n'

    for header_field in ksy['seq']:
        cname = header_field['id']

        if header_field['type'] in CTYPES:
            ctype = CTYPES[header_field['type']]
        elif header_field['type'] == 'str':
            ctype = CTYPES['u1']
            cname += f'[{header_field["size"]}]'
        else:
            ctype = header_field['type']
        
        if 'repeat' in header_field and header_field['repeat'] == 'expr':
            cname += f'[{header_field["repeat-expr"]}]'
        
        if 'doc' in header_field:
            cdoc = header_field['doc']
            if 'enum' in header_field:
                cdoc += f' (enum: {dostring_quote_code(enum_backref[header_field["enum"]])})'
        
            buf.body += C_INDENT + docstring(brief=f'{cdoc}')+'\n'
        buf.body += f'{C_INDENT}{ctype} {cname};\n'
    
    buf.body += f'}} {cheader_structname};\n'

    if memory_packing:
        buf.body += f'#pragma pack(pop)\n'

    buf.body += f'\n'

    # computed header fields

    buf.body += comment(f'Computed {name} fields') + '\n\n'

    for comp_name, comp_instance in ksy['instances'].items():
        
        comp_expr = comp_instance['value']
        comp_expr_tokens = comp_expr.split(' ')
        cexpr = ''
        for tok in comp_expr_tokens:
            if tok in [f['id'] for f in ksy['seq']]:
                cexpr += f't_{name}->{tok}'
            elif utils.is_int_literal(tok):
                cexpr += str(utils.int_literal(tok))
            else:
                cexpr += tok
            cexpr += ' '

        cexpr = f'inline int32_t {C_PREFIX}_{name}_{comp_name}(const {cheader_structname} *t_{name}) {{ return {cexpr.strip()}; }}'
        buf.body += docstring(brief=f'{comp_name} computed header field') + '\n'
        buf.body += f'{cexpr}\n\n'

    return cheader_structname


def build_print_struct(buf: CHeaderBuilder, ksy: dict, name: str, enum_unknown = "<unknown>"):
    cstruct_name = f"{C_PREFIX}_{name}_t"

    buf.impl += comment(f'Print {name}') + '\n'

    cfunc_signature = f'void {C_PREFIX}_{name}_print(const {cstruct_name}* t_{name})'
    
    buf.impl += f'{cfunc_signature} {{\n'

    printf_alias = f'{C_PREFIX}_printf'.upper()
    if printf_alias not in buf.header:
        buf.header += f'\n\n#ifndef {printf_alias}\n#include <stdio.h>\n#define {printf_alias} printf\n#endif\n\n'

    printn1 = CPrintfBuilder(printf=printf_alias)
    print_dict = {}

    for header_field in ksy['seq']:
        cname = header_field['id']
        ctype = header_field['type']
        if ctype == 'str':
            print_dict[cname] = f'\\"%.{header_field["size"]}s\\"'
            printn1.args.append(f't_{name}->{cname}')
        elif 'repeat' in header_field:

            arr_str = f'[ '
            for i in range(header_field['repeat-expr']):
                arr_str += f'{CTYPES_PRINTF[ctype]}'
                printn1.args.append(f't_{name}->{cname}[{i}]')
                if i < header_field['repeat-expr'] - 1:
                    arr_str += ', '
            arr_str += f' ]'

            print_dict[cname] = arr_str
            
        elif ctype in CTYPES_PRINTF.keys():
            if 'enum' in header_field:
                cenum = header_field['enum']
                buf.impl += f'{C_INDENT}const char *{cenum}_{cname} = {C_PREFIX}_{cenum}_name(t_{name}->{cname});\n'
                print_dict[cname] = f'%s ({CTYPES_PRINTF[ctype]})'
                printn1.args.append(f'({cenum}_{cname} == NULL ? "{enum_unknown}" : {cenum}_{cname})')
                printn1.args.append(f't_{name}->{cname}')
                
            else:
                print_dict[cname] = f'{CTYPES_PRINTF[ctype]}'
                printn1.args.append(f't_{name}->{cname}')
        else:
            assert False

    for comp_name, comp_dict in ksy['instances'].items():
        if 'enum' in comp_dict:
            cenum = comp_dict['enum']
            buf.impl += f'{C_INDENT}const char *{cenum}_{comp_name} = {C_PREFIX}_{cenum}_name({C_PREFIX}_{name}_{comp_name}(t_{name}));\n'
            print_dict[f'*{comp_name}'] = f'%s (%i)'
            printn1.args.append(f'({cenum}_{comp_name} == NULL ? "{enum_unknown}" : {cenum}_{comp_name})')
            printn1.args.append(f'{C_PREFIX}_{name}_{comp_name}(t_{name})')
        else:
            print_dict[f'*{comp_name}'] = f'%i'
            printn1.args.append(f'{C_PREFIX}_{name}_{comp_name}(t_{name})')

    max_key_len = max([len(k) for k in print_dict.keys()])
    for k, v in print_dict.items():
        printn1.fbuf += f'{k.ljust(max_key_len)} : {v}\\n'

    buf.impl += f'{printn1.build()};\n'
    
    buf.impl += f'\n}}\n\n'

    buf.body += docstring(brief=f'Print {name}') + '\n'
    buf.body += f'{cfunc_signature};\n\n'


def build_byteswap_struct(buf: CHeaderBuilder, ksy: dict, name: str):
    cstruct_name = f"{C_PREFIX}_{name}_t"

    buf.impl_header += f'\n\n#include "endianness.h"\n\n'
    
    buf.impl += comment(f'Byte-swap {name}') + '\n'
    cfun_signature = f'void {C_PREFIX}_{name}_swap({cstruct_name}* t_{name})'
    buf.impl += f'{cfun_signature} {{\n'
    for header_field in ksy['seq']:
        cname = header_field['id']
        ctype = header_field['type']
        if ctype in CTYPES.keys():
            nbytes = int(ctype[1:])
            if nbytes == 1:
                continue
            if 'repeat' in header_field:
                buf.impl += f'{C_INDENT}for (int i = 0; i < {header_field["repeat-expr"]}; ++i) {{\n'
                buf.impl += f'{C_INDENT*2}t_{name}->{cname}[i] = bswap{nbytes*8}(t_{name}->{cname}[i]);\n'
                buf.impl += f'{C_INDENT}}}\n'
            else:
                buf.impl += f'{C_INDENT}t_{name}->{cname} = bswap{nbytes*8}(t_{name}->{cname});\n'
    
    buf.impl += f'}}\n\n'

    buf.body += docstring(brief=f'Byte-swap {name}') + '\n'
    buf.body += f'{cfun_signature};\n\n'


def build_n1header():
    buf = CHeaderBuilder(
        header_guard_name=f'{C_PREFIX_UP}_HEADER_H', 
        header_name=f'{C_PREFIX}'
    )

    buf.header += f"""\n\n
#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define {C_PREFIX_UP}_STATIC_ASSERT(COND,MSG) static_assert(COND,MSG)
#else
#define {C_PREFIX_UP}_STATIC_ASSERT(COND,MSG)
#endif""".strip()
    
    buf.header += "\n\n#include <stddef.h>\n#include <stdint.h>\n#include <stdbool.h>"

    

    # code generation

    buf.body += f'/** @brief {C_PREFIX} version */\n'
    buf.body += f'#define {C_PREFIX_UP}_VERSION {C_VERSION}\n\n'


    ksy = load_ksy(PATH_NIFTI_KSY)
    ksy_n1 = ksy['types']['n1_file']
    ksy_n2 = ksy['types']['n2_file']

    # enums

    enum_backref = {}

    for enum in iter_enums(ksy):
        enum_backref[enum.name] = f'{C_PREFIX}_{enum.name}_*'.upper()
        cname = enum.name
        buf.body += comment(f'Begin: {cname}') + '\n\n'
        for enum_var in enum.values:
            if enum_var.doc is not None:
                buf.body += docstring(brief=f'{enum.name}: "{enum_var.name}"\n\n{enum_var.doc}') + '\n'
            else:
                buf.body += docstring(brief=f'{enum.name}: {enum_var.name}') + '\n'
            
            ckey_name = f'{C_PREFIX}_{enum.name}_{enum_var.name}'.upper()
            buf.body += f'#define {ckey_name} {enum_var.value}\n'

        for enum_var in enum.values:
            buf.body += docstring(brief=f'{enum.name} {enum_var.name} name') + '\n'
            ckey_name = f'{C_PREFIX}_{enum.name}_{enum_var.name}'.upper()
            buf.body += f'#define {ckey_name}_NAME "{enum_var.name}"\n'

        buf.body += '\n' + comment(f'End: {cname}') + '\n\n'

    
    # enum utilities

    buf.body += comment(f'Datatype size') + '\n\n'

    for enum_name in ksy['enums']['dt'].values():
        buf.body += docstring(brief=f'dt {enum_name} size') + '\n'
        bitsize = trailing_number(enum_name)
        if bitsize is None:
            if enum_name == 'unknown':
                bitsize = 0
            elif enum_name == 'binary':
                bitsize = 1
            else:
                assert False
        
        bytesize = bitsize // 8

        buf.body += f'#define {C_PREFIX_UP}_DT_{enum_name.upper()}_SIZE {bytesize}\n'

    buf.body += f'\n'
        
    # Nifti headers

    buf.body += comment(f'Nifti headers') + '\n\n'

    # nifti 1 header definition
    cstruct_header_n1 = build_struct(
        buf=buf,
        ksy=ksy_n1['types']['header'],
        name='n1_header',
        enum_backref=enum_backref
    )
    buf.body += f'{C_PREFIX_UP}_STATIC_ASSERT(sizeof({cstruct_header_n1}) == 348, "nifti1 header size is not 348 bytes");\n'
    
    # nifti 2 header definition
    cstruct_header_n2 = build_struct(
        buf=buf,
        ksy=ksy_n2['types']['header'],
        name='n2_header',
        enum_backref=enum_backref,
        memory_packing=True
    )
    buf.body += f'{C_PREFIX_UP}_STATIC_ASSERT(sizeof({cstruct_header_n2}) == 540, "nifti2 header size is not 540 bytes");\n'

    buf.body += f'\n'

    buf.body += docstring(brief=f'Nifti header union') + '\n'
    buf.body += f'typedef union {C_PREFIX}_header_t {{\n'
    buf.body += f'{C_INDENT}{cstruct_header_n1} n1_header;\n'
    buf.body += f'{C_INDENT}{cstruct_header_n2} n2_header;\n'
    buf.body += f'}} {C_PREFIX}_header_t;\n\n'


    # Implementation
    
    buf.body += f'\n'
    buf.body += comment(f'Implementation') + '\n'
    buf.body += f'#ifndef {C_PREFIX_UP}_HEADER_ONLY\n\n'

    buf.impl += comment(f'Implementation') + '\n\n'

    # enum dt -> size

    buf.impl += comment(f'Get the datatype size in bytes') + '\n'
    buf.impl += f'int32_t {C_PREFIX}_dt_size(int32_t dt) {{\n'
    buf.impl += f'{C_INDENT}switch (dt) {{\n'
    for enum_name in ksy['enums']['dt'].values():
        buf.impl += f'{C_INDENT}{C_INDENT}case {C_PREFIX_UP}_DT_{enum_name.upper()}: return {C_PREFIX_UP}_DT_{enum_name.upper()}_SIZE;\n'
    buf.impl += f'{C_INDENT}{C_INDENT}default: return 0;\n'
    buf.impl += f'{C_INDENT}}}\n'
    buf.impl += f'}}\n\n'

    buf.body += docstring(brief=f'Get the datatype size in bytes') + '\n'
    buf.body += f'int32_t {C_PREFIX}_dt_size(int32_t dt);\n\n'

    # Enum name lookups

    for enum_name in ksy['enums'].keys():
        build_enum_name_impls(buf, KsyEnum(enum_name, ksy))

    # print header

    build_print_struct(
        buf=buf,
        ksy=ksy_n1['types']['header'],
        name='n1_header',
        enum_unknown='<non standard>'
    )
    build_print_struct(
        buf=buf,
        ksy=ksy_n2['types']['header'],
        name='n2_header',
        enum_unknown='<non standard>'
    )


    # peek

    def swap32(i: int) -> int:
        return struct.unpack("<I", struct.pack(">I", i))[0]

    buf.body += f'#define {C_PREFIX_UP}_PEEK_NIFTI2 {0b01}\n'
    buf.body += f'#define {C_PREFIX_UP}_PEEK_SWAP {0b10}\n'
    buf.body += docstring(brief=f'Peek at first 4 bytes of header to determine nifti version and endianness.\n'
                          f'Return value can be bit compared with {C_PREFIX_UP}_PEEK_* values.\n'
                          f'If return value is -1 this is not a nifti header.') + '\n'
    buf.body += f'static inline int32_t {C_PREFIX}_peek(const uint32_t t_header_start) {{\n'
    buf.body += f'{C_INDENT}switch (t_header_start) {{\n'
    buf.body += f'{C_INDENT}{C_INDENT}case 348: return 0;\n'
    buf.body += f'{C_INDENT}{C_INDENT}case {swap32(348)}: return {C_PREFIX_UP}_PEEK_SWAP;\n'
    buf.body += f'{C_INDENT}{C_INDENT}case 540: return {C_PREFIX_UP}_PEEK_NIFTI2;\n'
    buf.body += f'{C_INDENT}{C_INDENT}case {swap32(540)}: return {C_PREFIX_UP}_PEEK_NIFTI2 & {C_PREFIX_UP}_PEEK_SWAP;\n'
    buf.body += f'{C_INDENT}{C_INDENT}default: return -1;\n'
    buf.body += f'{C_INDENT}}}\n'
    buf.body += f'}}\n\n'

    """
    Untested potentially faster version with perfect hashing (but less file validity guarantees):
    
static inline int32_t cnifti_peek_fast(const uint32_t t_header_start) {
  static int32_t lookup[7] = { -1, CNIFTI_PEEK_NIFTI2, -1, CNIFTI_PEEK_SWAP, CNIFTI_PEEK_NIFTI2 & CNIFTI_PEEK_SWAP, 0, -1};
  return lookup[t_header_start % 7];
}

    """

    # Byte-swap

    build_byteswap_struct(
        buf=buf,
        ksy=ksy_n1['types']['header'],
        name='n1_header'
    )
    build_byteswap_struct(
        buf=buf,
        ksy=ksy_n2['types']['header'],
        name='n2_header'
    )
    

    # Data access

    for cname, name in [(cstruct_header_n1, 'n1_header'), (cstruct_header_n2, 'n2_header')]:

        buf.body += docstring(brief=f'Calculate {name} data array size (in bytes).') + '\n'
        buf.body += f'static inline int64_t {C_PREFIX}_{name}_array_size(const {cname}* t_{name}) {{\n'
        buf.body += f'{C_INDENT}int64_t size = t_{name}->bitpix / 8;\n'
        buf.body += f'{C_INDENT}for (int i = 0; i < t_{name}->dim[0]; ++i) {{ size *= t_{name}->dim[i+1]; }}\n'
        buf.body += f'{C_INDENT}return size;\n'
        buf.body += f'}}\n\n'

    
    buf.body += f'#endif /* {C_PREFIX_UP}_HEADER_ONLY */\n'

    return buf


def trailing_number(s: str) -> int:
    """Return the trailing number of a string, or None if no trailing number is found."""
    m = re.search(r'\d+$', s)
    return int(m.group()) if m else None


if __name__ == '__main__':
    main()
    