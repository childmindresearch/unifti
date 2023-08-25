import struct
import re


def is_int_literal(s: str) -> bool:
    """Returns True if s is a valid integer literal, False otherwise."""
    if s.startswith("0b"):
        return all(c in "01" for c in s[2:])
    elif s.startswith("0x"):
        return all(c in "0123456789abcdefABCDEF" for c in s[2:])
    return all(c in "0123456789" for c in s)


def int_literal(s: str) -> int:
    """Returns the integer value of s, which must be a valid integer literal."""
    if s.startswith("0b"):
        return int(s[2:], 2)
    elif s.startswith("0x"):
        return int(s[2:], 16)
    return int(s)


def swap32(i: int) -> int:
    """Swaps the endianness of i, which must be a 32-bit integer."""
    return struct.unpack("<I", struct.pack(">I", i))[0]


def trailing_int(s: str) -> int:
    """Return the trailing integer of a string, or None if no trailing integer is found."""
    m = re.search(r"\d+$", s)
    return int(m.group()) if m else None
