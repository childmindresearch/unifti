/** 
* Modified from https://gist.github.com/jtbr/7a43e6281e6cca353b33ee501421860c
*/

#ifndef ENDIANNESS_H_
#define ENDIANNESS_H_

#if !defined(CNIFTI_STATIC_ASSERT)
#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define CNIFTI_STATIC_ASSERT(COND,MSG) _Static_assert(COND,MSG)
#else
#define CNIFTI_STATIC_ASSERT(COND,MSG)
#endif
#endif

#include <stdlib.h>
#include <stdint.h>
#ifdef __cplusplus
#include <cstring> // for memcpy
#endif


#if defined(bswap16) || defined(bswap32) || defined(bswap64) || defined(bswapf) || defined(bswapd)
#  error "unexpected define!" // freebsd may define these; probably just need to undefine them
#endif

/* Define byte-swap functions, using fast processor-native built-ins where possible */
#if defined(_MSC_VER) // needs to be first because msvc doesn't short-circuit after failing defined(__has_builtin)
#  define bswap16(x)     _byteswap_ushort((x))
#  define bswap32(x)     _byteswap_ulong((x))
#  define bswap64(x)     _byteswap_uint64((x))
#elif (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
#  define bswap16(x)     __builtin_bswap16((x))
#  define bswap32(x)     __builtin_bswap32((x))
#  define bswap64(x)     __builtin_bswap64((x))
#elif defined(__has_builtin) && __has_builtin(__builtin_bswap64)  /* for clang; gcc 5 fails on this and && shortcircuit fails; must be after GCC check */
#  define bswap16(x)     __builtin_bswap16((x))
#  define bswap32(x)     __builtin_bswap32((x))
#  define bswap64(x)     __builtin_bswap64((x))
#else
    /* even in this case, compilers often optimize by using native instructions */
    static inline uint16_t bswap16(uint16_t x) {
		return ((( x  >> 8 ) & 0xffu ) | (( x  & 0xffu ) << 8 ));
	}
    static inline uint32_t bswap32(uint32_t x) {
        return ((( x & 0xff000000u ) >> 24 ) |
                (( x & 0x00ff0000u ) >> 8  ) |
                (( x & 0x0000ff00u ) << 8  ) |
                (( x & 0x000000ffu ) << 24 ));
    }
    static inline uint64_t bswap64(uint64_t x) {
        return ((( x & 0xff00000000000000ull ) >> 56 ) |
                (( x & 0x00ff000000000000ull ) >> 40 ) |
                (( x & 0x0000ff0000000000ull ) >> 24 ) |
                (( x & 0x000000ff00000000ull ) >> 8  ) |
                (( x & 0x00000000ff000000ull ) << 8  ) |
                (( x & 0x0000000000ff0000ull ) << 24 ) |
                (( x & 0x000000000000ff00ull ) << 40 ) |
                (( x & 0x00000000000000ffull ) << 56 ));
    }
#endif

//! Byte-swap 32-bit float
static inline float bswapf(float f) {
#ifdef __cplusplus
    static_assert(sizeof(float) == sizeof(uint32_t), "Unexpected float format");
    /* Problem: de-referencing float pointer as uint32_t breaks strict-aliasing rules for C++ and C, even if it normally works
     *   uint32_t val = bswap32(*(reinterpret_cast<const uint32_t *>(&f)));
     *   return *(reinterpret_cast<float *>(&val));
     */
    // memcpy approach is guaranteed to work in C & C++ and fn calls should be optimized out:
    uint32_t asInt;
    std::memcpy(&asInt, reinterpret_cast<const void *>(&f), sizeof(uint32_t));
    asInt = bswap32(asInt);
    std::memcpy(&f, reinterpret_cast<void *>(&asInt), sizeof(float));
    return f;
#else
    CNIFTI_STATIC_ASSERT(sizeof(float) == sizeof(uint32_t), "Unexpected float format");
    // union approach is guaranteed to work in C99 and later (but not in C++, though in practice it normally will):
    union { uint32_t asInt; float asFloat; } conversion_union;
    conversion_union.asFloat = f;
    conversion_union.asInt = bswap32(conversion_union.asInt);
    return conversion_union.asFloat;
#endif
}

//! Byte-swap 64-bit double
static inline double bswapd(double d) {
#ifdef __cplusplus
    static_assert(sizeof(double) == sizeof(uint64_t), "Unexpected double format");
    uint64_t asInt;
    std::memcpy(&asInt, reinterpret_cast<const void *>(&d), sizeof(uint64_t));
    asInt = bswap64(asInt);
    std::memcpy(&d, reinterpret_cast<void *>(&asInt), sizeof(double));
    return d;
#else
    CNIFTI_STATIC_ASSERT(sizeof(double) == sizeof(uint64_t), "Unexpected double format");
    union { uint64_t asInt; double asDouble; } conversion_union;
    conversion_union.asDouble = d;
    conversion_union.asInt = bswap64(conversion_union.asInt);
    return conversion_union.asDouble;
#endif
}

#endif //ENDIANNESS_H_