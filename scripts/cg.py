from typing import Optional


C_INDENT = "  "

def cindent(s: str, indent: int = 1) -> str:
    """Indents s by indent levels."""
    ind = C_INDENT * indent
    return ind + s.replace("\n", "\n" + ind)


def ensure_linebreak(s: str) -> str:
    """Ensures that s ends with exactly one newline."""
    if s.endswith("\n"):
        return s
    return s + "\n"

def ensure_double_linebreak(s: str) -> str:
    """Ensures that s ends with exactly two newlines."""
    if s.endswith("\n\n"):
        return s
    return s + "\n\n"

def ensure_linebreak_before(s: str) -> str:
    """Ensures that s starts with exactly one newline."""
    if s.startswith("\n"):
        return s
    return "\n" + s

def ensure_double_linebreak_before(s: str) -> str:
    """Ensures that s starts with exactly two newlines."""
    if s.startswith("\n\n"):
        return s
    return "\n\n" + s

def section(s: str) -> str:
    """Returns s as a section."""
    return ensure_linebreak_before(s.strip())


def docstring_escape(s: str):
    return s.replace("@", "\\@")


def docstring(*args, **kwargs):
    s = "\n".join([docstring_escape(a) for a in args]) + "\n".join(
        [f"@{k} {docstring_escape(v)}" for k, v in kwargs.items() if v is not None]
    )

    if "\n" in s:
        s = s.replace("\n", "\n * ")
        return f"/**\n * {s}\n */"
    return f"/** {s} */"


def comment(*args, **kwargs):
    s = "\n".join([docstring_escape(a) for a in args]) + "\n".join(
        [f"{k}: {docstring_escape(v)}" for k, v in kwargs.items() if v is not None]
    )

    if "\n" in s:
        s = s.replace("\n", "\n * ")
        return f"/*\n * {s}\n */"
    return f"/* {s} */"


def dostring_quote_code(s: str):
    return f"`{s}`"


class CPrintfBuilder:
    def __init__(self, printf: str = "printf"):
        self.printf = printf
        self.args: List[str] = []
        self.fbuf: str = ""

    def build(self) -> str:
        args_formatted = f",\n{C_INDENT*2}".join(self.args)
        fbuf_formatted = f'\\n"\n{C_INDENT*2}"'.join(self.fbuf.split("\\n"))
        return f'{C_INDENT}{self.printf}(\n{C_INDENT*2}"{fbuf_formatted}",\n{C_INDENT*2}{args_formatted}\n{C_INDENT})'


class CHeaderBuilder:
    def __init__(self, header_guard_name: str, header_name: str):
        self.header_guard_name = header_guard_name
        self.header_name = header_name
        self.header = ""
        self.footer = ""
        self.body = ""
        self.impl_header = ""
        self.impl = ""

    def build_header(self) -> str:
        return f"""
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
""".strip()

    def build_impl(self) -> str:
        return f"""
/** @file {self.header_name}.c */

#include "{self.header_name}.h"

{self.impl_header}

{self.impl}
""".strip()


class CFunc:
    def __init__(
        self,
        signature: str,
        body: str,
        prefix: Optional[str] = None,
        postfix: Optional[str] = None,
    ) -> None:
        self.signature = signature.strip()
        self.body = body.strip()
        self.prefix = prefix.strip() if prefix is not None else ""
        self.postfix = postfix.strip() if postfix is not None else ""

    def write(self, buf: CHeaderBuilder, header_only=False) -> str:
        if header_only:
            buf.body += section(f"""
{self.prefix}
static inline {self.signature} {{
{cindent(self.body)}
}}
{self.postfix}
""")
        else:
            buf.body += section(f"""
{self.prefix}
static inline {self.signature};
{self.postfix}
""")
            buf.impl += section(f"""
{self.prefix}
{self.signature} {{
{cindent(self.body)}
}}
{self.postfix}
""")
        return buf
