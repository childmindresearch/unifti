from dataclasses import dataclass
from typing import List, Optional
import yaml
from . import cg, utils


KSY2C_TYPE = {
    "s1": "int8_t",
    "u1": "uint8_t",
    "s2": "int16_t",
    "u2": "uint16_t",
    "s4": "int32_t",
    "u4": "uint32_t",
    "s8": "int64_t",
    "u8": "uint64_t",
    "f4": "float",
    "f8": "double",
}

KSY2C_FPRINT = {
    "s1": "%i",
    "u1": "%u",
    "s2": "%i",
    "u2": "%u",
    "s4": "%i",
    "u4": "%u",
    "s8": "%li",
    "u8": "%lu",
    "f4": "%f",
    "f8": "%f",
}

KSY_BYTESWAPPABLE = ["s1", "u1", "s2", "u2", "s4", "u4", "s8", "u8", "f4", "f8"]


@dataclass
class KsyEnumValue:
    name: str
    value: int
    doc: Optional[str] = None

    def cn(self):
        return cg.cn_enum_value(self.name, self.value)

    def cn_str(self):
        return f"{self.cn()}_STR"

    def cdefine(self):
        s = ""
        if self.doc is not None:
            s += cg.docstring(brief=f"{self.doc} ({self.name}::{self.name})")
        else:
            s += cg.docstring(brief=f"{self.name}::{self.name}")
        return f"{s}\n#define {self.cn()} {self.value}"

    def cdefine_str(self):
        return (
            cg.docstring(brief=f"{self.name}::{self.name} name string")
            + "\n"
            + f'#define {self.cn_str()} "{self.name}"'
        )


@dataclass
class KsyEnum:
    name: str
    values: List[KsyEnumValue]

    def __init__(self, name: str, ksy: dict):
        self.name = name
        ksy = ksy["enums"][name]
        self.values = []
        for var_value, var_name in ksy.items():
            if isinstance(var_name, dict):
                self.values.append(
                    KsyEnumValue(
                        name=var_name["id"],
                        value=var_value,
                        doc=var_name["doc"] if "doc" in var_name else None,
                    )
                )
            else:
                self.values.append(
                    KsyEnumValue(name=var_name, value=var_value, doc=None)
                )

    def cdefine_all(self, include_str=True):
        return "\n".join(
            [
                cg.big_comment(f"Enum {self.name}"),
                "\n".join([v.cdefine() for v in self.values]),
                "\n".join([v.cdefine_str() for v in self.values])
                if include_str
                else "",
            ]
        )

    def cdynamic_name(self) -> cg.CFunc:
        return cg.CFunc(
            prefix=cg.comment(f"Returns the name of the {self.name} value."),
            signature=f"const char *{cg.cn_func_name(f'{self.name}_name')}(const int32_t value)",
            body="\n".join(
                [
                    f"switch (value) {{",
                    "\n".join(
                        [
                            cg.cindent(f"case {v.cn()}: return {v.cn_str()};")
                            for v in self.values
                        ]
                    ),
                    f"default: return NULL;",
                    f"}}",
                ]
            ),
        )

    def cdynamic_from_name(self) -> cg.CFunc:
        return cg.CFunc(
            prefix=cg.comment(f"Returns the {self.name} value from its name."),
            signature=f"int32_t {cg.cn_func_name(f'{self.name}_from_name')}(const char *{cg.cn_arg(self.name)})",
            body="\n".join(
                [
                    f"if ({cg.cn_arg(self.name)} == NULL) return -1;",
                    f"if (strcmp({cg.cn_arg(self.name)}, {self.values[0].cn_str()}) == 0) return {self.values[0].cn()};",
                    "\n".join(
                        [
                            cg.cindent(
                                f"else if (strcmp({cg.cn_arg(self.name)}, {v.cn_str()}) == 0) return {v.cn()};"
                            )
                            for v in self.values
                        ]
                    ),
                    f"return -1;",
                ]
            ),
        )


class KsyGrammar:
    def __init__(self, filename) -> None:
        with open(filename) as f:
            ksy = yaml.load(f, Loader=yaml.FullLoader)

        self.ksy = ksy

    def iter_enums(self):
        for enum_name in self.ksy["enums"].keys():
            yield KsyEnum(enum_name, self.ksy)

    def n1(self) -> dict:
        return self.ksy["types"]["n1_file"]

    def n2(self) -> dict:
        return self.ksy["types"]["n2_file"]


@dataclass
class KsyStructField:
    name: str
    type: str
    str_len: Optional[int] = None
    arr_len: Optional[int] = None
    enum: Optional[str] = None
    doc: Optional[str] = None

    def __init__(self, ksy_field: dict):
        self.name = ksy_field["id"]
        self.type = 'u1' if 'type' not in ksy_field else ksy_field["type"]

        if self.type == "str":
            self.str_len = ksy_field["size"]
        elif "repeat" in ksy_field:
            self.arr_len = ksy_field["repeat-expr"]
        if "enum" in ksy_field:
            self.enum = ksy_field["enum"]
        if "doc" in ksy_field:
            self.doc = ksy_field["doc"]

    def cdef(self):
        if self.type == "str":
            return f"char {self.name}[{self.str_len}]"
        elif self.arr_len is not None:
            return f"{KSY2C_TYPE[self.type]} {self.name}[{self.arr_len}]"
        else:
            return f"{KSY2C_TYPE[self.type]} {self.name}"

    def ctype(self):
        if self.type == "str":
            return f"char *"
        elif self.arr_len is not None:
            return f"{KSY2C_TYPE[self.type]} *"
        else:
            return f"{KSY2C_TYPE[self.type]}"

    def ctype_fprint(self):
        if self.type == "str":
            return f"'%.{self.str_len}s'"
        elif self.arr_len is not None:
            arr_strs = [f"{KSY2C_FPRINT[self.type]}" for _ in range(self.arr_len)]
            return f"[ {', '.join(arr_strs)} ]"
        else:
            return f"{KSY2C_FPRINT[self.type]}"

    def needs_byteswap(self):
        return self.type in KSY_BYTESWAPPABLE

    def nbytes(self):
        return int(self.type[1:])


@dataclass
class KsyStructCompField:
    name: str
    enum: Optional[str] = None
    expr: Optional[str] = None

    def __init__(self, name, ksy_comp: dict):
        self.name = name
        if "enum" in ksy_comp:
            self.enum = ksy_comp["enum"]
        if "value" in ksy_comp:
            self.expr = ksy_comp["value"]

    def ctype_fprint(self):
        if self.enum is not None:
            return f"%s (%i)"
        else:
            return f"%i"
        
    def cexpr(self, ksy_struct: 'KsyStruct'):
        comp_expr_tokens = self.expr.split(' ')
        cexpr = ''
        for tok in comp_expr_tokens:
            if tok in [f.name for f in ksy_struct.iter_fields()]:
                cexpr += f'{cg.cn_arg(ksy_struct.name)}->{tok}'
            elif utils.is_int_literal(tok):
                cexpr += str(utils.int_literal(tok))
            else:
                cexpr += tok
            cexpr += ' '
        return cexpr.strip()


@dataclass
class KsyStruct:
    def __init__(self, name: str, ksy_struct: dict):
        self.name = name
        self.ksy_struct = ksy_struct

    def iter_fields(self):
        for field in self.ksy_struct["seq"]:
            yield KsyStructField(field)

    def iter_comp_fields(self):
        for comp_name, comp_dict in self.ksy_struct["instances"].items():
            yield KsyStructCompField(comp_name, comp_dict)


def build_print_struct(
    ksy_struct: KsyStruct,
    printf_alias: str,
    enum_unknown="<unknown>",
) -> cg.CFunc:
    func_body_prefix = ""

    printn1 = cg.CPrintfBuilder(printf=printf_alias)
    print_dict = {}

    for field in ksy_struct.iter_fields():
        field_access = f"{cg.cn_arg(ksy_struct.name)}->{field.name}"
        print_dict[field.name] = field.ctype_fprint()

        if field.arr_len is not None:
            for i in range(field.arr_len):
                printn1.args.append(f"{field_access}[{i}]")
        elif field.enum is not None:
            enum_lookup_var = f"{field.enum}_{field.name}"
            func_body_prefix += f"const char *{enum_lookup_var} = {cg.cn_func_name(field.enum)}_name({field_access});\n"
            printn1.args.append(
                f'({enum_lookup_var} == NULL ? "{enum_unknown}" : {enum_lookup_var})'
            )
        else:
            printn1.args.append(field_access)

    for field in ksy_struct.iter_comp_fields():
        print_dict[f"*{field.name}"] = field.ctype_fprint()
        if field.enum is not None:
            field_access = f"{cg.cn_func_name(f'{ksy_struct.name}_{field.name}')}({cg.cn_arg(ksy_struct.name)})"
            enum_lookup_var = f"{field.enum}_{field.name}"
            func_body_prefix += f"const char *{enum_lookup_var} = {cg.cn_func_name(field.enum)}_name({field_access});\n"
            printn1.args.append(
                f'({enum_lookup_var} == NULL ? "{enum_unknown}" : {enum_lookup_var})'
            )
        printn1.args.append(field_access)

    max_key_len = max([len(k) for k in print_dict.keys()])
    for k, v in print_dict.items():
        printn1.fbuf += f"{k.ljust(max_key_len)} : {v}\\n"

    return cg.CFunc(
        prefix=cg.comment(f"Utility function for printing {ksy_struct.name}."),
        signature=f"void {cg.cn_func_name(f'{ksy_struct.name}_print')}(const {cg.cn_struct_type(ksy_struct.name)} *{cg.cn_arg(ksy_struct.name)})",
        body=f"{cg.ensure_linebreak(func_body_prefix)}{printn1.build()};",
    )


def build_byteswap_struct(
    ksy_struct: KsyStruct,
) -> cg.CFunc:
    func_body = ""

    # buf.impl_header += f'\n\n#include "endianness.h"\n\n'

    for field in ksy_struct.iter_fields():
        if not field.needs_byteswap():
            continue
        nbytes = field.nbytes()
        if nbytes == 1:
            continue
        field_access = f"{cg.cn_arg(ksy_struct.name)}->{field.name}"
        if field.arr_len is not None:
            func_body += "\n".join(
                [
                    cg.cindent(f"\nfor (int i = 0; i < {field.arr_len}; ++i) {{"),
                    cg.cindent(
                        f"{field_access}[i] = bswap{nbytes*8}({field_access}[i]);", 2
                    ),
                    cg.cindent("}"),
                ]
            )

        else:
            func_body += f"\n{field_access} = bswap{nbytes*8}({field_access});"

    return cg.CFunc(
        prefix=cg.comment(f"Utility function for byte swapping {ksy_struct.name}."),
        signature=f"void {cg.cn_func_name(f'{ksy_struct.name}_swap')}({cg.cn_struct_type(ksy_struct.name)} *{cg.cn_arg(ksy_struct.name)})",
        body=func_body,
    )


def build_struct(ksy_struct: KsyStruct) -> cg.CStruct:

    re = cg.CStruct(
        name=ksy_struct.name,
        fields=[],
    )


    for field in ksy_struct.iter_fields():
        cdoc = ''
        if field.doc is not None:
            cdoc = field.doc
            if field.enum is not None:
                cdoc += f' (enum: {cg.cn_enum_value(field.enum, "*")})'

        re.fields.append(f'{cg.docstring(cdoc)}\n{field.cdef()}')

    return re

def build_comp_field_funcs(ksy_struct: KsyStruct) -> List[cg.CFunc]:

    funcs: List[cg.CFunc] = []

    for field in ksy_struct.iter_comp_fields():

        comp_expr = field.cexpr(ksy_struct)

        funcs.append(
            cg.CFunc(
                prefix=cg.comment(f'Computed header field {field.name}'),
                signature=f'int32_t {cg.cn_func_name(f"{ksy_struct.name}_{field.name}")}(const {cg.cn_struct_type(ksy_struct.name)} *{cg.cn_arg(ksy_struct.name)})',
                body=f'return {comp_expr};'
            )
        )

    return funcs