/** @file unifti.h */
               
#ifndef UNIFTI_unifti_HEADER_H
#define UNIFTI_unifti_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define UNIFTI_STATIC_ASSERT(COND,MSG) static_assert(COND,MSG)
#else
#define UNIFTI_STATIC_ASSERT(COND,MSG)
#endif

#ifndef UNIFTI_PRINTF
#include <stdio.h>
#define UNIFTI_PRINTF printf
#endif

#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool
#include <stddef.h>  // NULL, size_t
#include <stdint.h>  // int32_t, uint32_t, int64_t, uint64_t
#include <string.h>  // memcpy, strcmp
/** @brief version */
#define UNIFTI_VERSION 1
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
    UNIFTI_STATIC_ASSERT(sizeof(float) == sizeof(uint32_t), "Unexpected float format");
    // union approach is guaranteed to work in C99 and later (but not in C++, though in practice it normally will):
    union { uint32_t asInt; float asFloat; } conversion_union;
    conversion_union.asFloat = f;
    conversion_union.asInt = bswap32(conversion_union.asInt);
    return conversion_union.asFloat;
}

//! Byte-swap 64-bit double
static inline double bswapd(double d) {
    UNIFTI_STATIC_ASSERT(sizeof(double) == sizeof(uint64_t), "Unexpected double format");
    union { uint64_t asInt; double asDouble; } conversion_union;
    conversion_union.asDouble = d;
    conversion_union.asInt = bswap64(conversion_union.asInt);
    return conversion_union.asDouble;
}
typedef struct unifti_n1_header_t {
  /** Must be 348. */
  int32_t sizeof_hdr;
  /** Unused placeholder for ANALYZE(TM) 7.5 backwards compatibility. (Removed in NIfTI-2). */
  char data_type[10];
  /** Unused placeholder for ANALYZE(TM) 7.5 backwards compatibility. (Removed in NIfTI-2). */
  char db_name[18];
  /** Unused placeholder for ANALYZE(TM) 7.5 backwards compatibility. (Removed in NIfTI-2). */
  int32_t extents;
  /** Unused placeholder for ANALYZE(TM) 7.5 backwards compatibility. (Removed in NIfTI-2). */
  int16_t session_error;
  /** Unused placeholder for ANALYZE(TM) 7.5 backwards compatibility. (Removed in NIfTI-2). */
  int8_t regular;
  /** MRI slice ordering. Stores frequency_dim, phase_dim and slice_dim in 2 bit each. */
  int8_t dim_info;
  /** Data array dimensions. dim[0] contains the number of dimensions, dim[1..7] describe the sizes of the dimensions. */
  int16_t dim[8];
  /** 1st intent parameter. Contains additionaly parameters depending on the intent code. */
  float intent_p1;
  /** 2nd intent parameter. Contains additionaly parameters depending on the intent code. */
  float intent_p2;
  /** 3rd intent parameter. Contains additionaly parameters depending on the intent code. */
  float intent_p3;
  /** NIFTI_INTENT_* code. (enum: UNIFTI_INTENT_*) */
  int16_t intent_code;
  /** Defines data type. (enum: UNIFTI_DT_*) */
  int16_t datatype;
  /** Number bits/voxel. */
  int16_t bitpix;
  /** First slice index. */
  int16_t slice_start;
  /** Grid spacings. */
  float pixdim[8];
  /** Offset into .nii file */
  float vox_offset;
  /** Data scaling: slope. */
  float scl_slope;
  /** Data scaling: offset. */
  float scl_inter;
  /** Last slice index. */
  int16_t slice_end;
  /** Slice timing order. (enum: UNIFTI_SLICE_*) */
  int8_t slice_code;
  /** Units of pixdim[1..4] */
  int8_t xyzt_units;
  /** Max display intensity. */
  float cal_max;
  /** Min display intensity. */
  float cal_min;
  /** Time for 1 slice. */
  float slice_duration;
  /** Time axis shift. */
  float toffset;
  /** Unused. */
  int32_t glmax;
  /** Unused. */
  int32_t glmin;
  /** Any text you like. */
  char descrip[80];
  /** Auxiliary filename. */
  char aux_file[24];
  /** NIFTI_XFORM_* code. (enum: UNIFTI_XFORM_*) */
  int16_t qform_code;
  /** NIFTI_XFORM_* code. (enum: UNIFTI_XFORM_*) */
  int16_t sform_code;
  /** Quaternion b param. */
  float quatern_b;
  /** Quaternion c param. */
  float quatern_c;
  /** Quaternion d param. */
  float quatern_d;
  /** Quaternion x param. */
  float qoffset_x;
  /** Quaternion y param. */
  float qoffset_y;
  /** Quaternion z param. */
  float qoffset_z;
  /** 1st row affine transform. */
  float srow_x[4];
  /** 2nd row affine transform. */
  float srow_y[4];
  /** 3rd row affine transform. */
  float srow_z[4];
  /** 'name' or meaning of data. */
  char intent_name[16];
  /** MUST be "ni1\\0" or "n+1\\0". */
  char magic[4];
} unifti_n1_header_t;
#pragma pack(push, 1)
typedef struct unifti_n2_header_t {
  /** Must be 540. */
  int32_t sizeof_hdr;
  /** MUST be 'ni2\0' or 'n+2\0'. */
  char magic[4];
  /** MUST be 0D 0A 1A 0A. */
  int8_t magic2[4];
  /** Defines data type. (enum: UNIFTI_DT_*) */
  int16_t datatype;
  /** Number bits/voxel. */
  int16_t bitpix;
  /** Data array dimensions. */
  int64_t dim[8];
  /** 1st intent parameter. */
  double intent_p1;
  /** 2nd intent parameter. */
  double intent_p2;
  /** 3rd intent parameter. */
  double intent_p3;
  /** Grid spacings. */
  double pixdim[8];
  /** Offset into .nii file */
  int64_t vox_offset;
  /** Data scaling: slope. */
  double scl_slope;
  /** Data scaling: offset. */
  double scl_inter;
  /** Max display intensity. */
  double cal_max;
  /** Min display intensity. */
  double cal_min;
  /** Time for 1 slice. */
  double slice_duration;
  /** Time axis shift. */
  double toffset;
  /** First slice index. */
  int64_t slice_start;
  /** Last slice index. */
  int64_t slice_end;
  /** Any text you like. */
  char descrip[80];
  /** Auxiliary filename. */
  char aux_file[24];
  /** NIFTI_XFORM_* code. (enum: UNIFTI_XFORM_*) */
  int32_t qform_code;
  /** NIFTI_XFORM_* code. (enum: UNIFTI_XFORM_*) */
  int32_t sform_code;
  /** Quaternion b param. */
  double quatern_b;
  /** Quaternion c param. */
  double quatern_c;
  /** Quaternion d param. */
  double quatern_d;
  /** Quaternion x param. */
  double qoffset_x;
  /** Quaternion y param. */
  double qoffset_y;
  /** Quaternion z param. */
  double qoffset_z;
  /** 1st row affine transform. */
  double srow_x[4];
  /** 2nd row affine transform. */
  double srow_y[4];
  /** 3rd row affine transform. */
  double srow_z[4];
  /** Slice timing order. (enum: UNIFTI_SLICE_*) */
  int32_t slice_code;
  /** Units of pixdim[1..4] */
  int32_t xyzt_units;
  /** NIFTI_INTENT_* code. (enum: UNIFTI_INTENT_*) */
  int32_t intent_code;
  /** 'name' or meaning of data. */
  char intent_name[16];
  /** MRI slice ordering. */
  int8_t dim_info;
  /** unused, filled with \0 */
  char unused_str[15];
} unifti_n2_header_t;
#pragma pack(pop)
typedef struct unifti_extension_indicator_t {
  /**  */
  int8_t has_extension;
  /**  */
  uint8_t padding[3];
} unifti_extension_indicator_t;
typedef struct unifti_extension_header_t {
  /**  */
  int32_t esize;
  /**  */
  int32_t ecode;
} unifti_extension_header_t;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Enum dt ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief dt::unknown */
#define UNIFTI_DT_UNKNOWN 0
/** @brief dt::binary */
#define UNIFTI_DT_BINARY 1
/** @brief dt::uint8 */
#define UNIFTI_DT_UINT8 2
/** @brief dt::int16 */
#define UNIFTI_DT_INT16 4
/** @brief dt::int32 */
#define UNIFTI_DT_INT32 8
/** @brief dt::float32 */
#define UNIFTI_DT_FLOAT32 16
/** @brief dt::complex64 */
#define UNIFTI_DT_COMPLEX64 32
/** @brief dt::float64 */
#define UNIFTI_DT_FLOAT64 64
/** @brief dt::rgb24 */
#define UNIFTI_DT_RGB24 128
/** @brief dt::int8 */
#define UNIFTI_DT_INT8 256
/** @brief dt::uint16 */
#define UNIFTI_DT_UINT16 512
/** @brief dt::uint32 */
#define UNIFTI_DT_UINT32 768
/** @brief dt::int64 */
#define UNIFTI_DT_INT64 1024
/** @brief dt::uint64 */
#define UNIFTI_DT_UINT64 1280
/** @brief dt::float128 */
#define UNIFTI_DT_FLOAT128 1536
/** @brief dt::complex128 */
#define UNIFTI_DT_COMPLEX128 1792
/** @brief dt::complex256 */
#define UNIFTI_DT_COMPLEX256 2048
/** @brief dt::rgba32 */
#define UNIFTI_DT_RGBA32 2304
/** @brief dt::unknown name string */
#define UNIFTI_DT_UNKNOWN_STR "unknown"
/** @brief dt::binary name string */
#define UNIFTI_DT_BINARY_STR "binary"
/** @brief dt::uint8 name string */
#define UNIFTI_DT_UINT8_STR "uint8"
/** @brief dt::int16 name string */
#define UNIFTI_DT_INT16_STR "int16"
/** @brief dt::int32 name string */
#define UNIFTI_DT_INT32_STR "int32"
/** @brief dt::float32 name string */
#define UNIFTI_DT_FLOAT32_STR "float32"
/** @brief dt::complex64 name string */
#define UNIFTI_DT_COMPLEX64_STR "complex64"
/** @brief dt::float64 name string */
#define UNIFTI_DT_FLOAT64_STR "float64"
/** @brief dt::rgb24 name string */
#define UNIFTI_DT_RGB24_STR "rgb24"
/** @brief dt::int8 name string */
#define UNIFTI_DT_INT8_STR "int8"
/** @brief dt::uint16 name string */
#define UNIFTI_DT_UINT16_STR "uint16"
/** @brief dt::uint32 name string */
#define UNIFTI_DT_UINT32_STR "uint32"
/** @brief dt::int64 name string */
#define UNIFTI_DT_INT64_STR "int64"
/** @brief dt::uint64 name string */
#define UNIFTI_DT_UINT64_STR "uint64"
/** @brief dt::float128 name string */
#define UNIFTI_DT_FLOAT128_STR "float128"
/** @brief dt::complex128 name string */
#define UNIFTI_DT_COMPLEX128_STR "complex128"
/** @brief dt::complex256 name string */
#define UNIFTI_DT_COMPLEX256_STR "complex256"
/** @brief dt::rgba32 name string */
#define UNIFTI_DT_RGBA32_STR "rgba32"

/* Returns the name of the dt value. */
static inline const char *unifti_dt_name(const int32_t value) {
  switch (value) {
    case UNIFTI_DT_UNKNOWN: return UNIFTI_DT_UNKNOWN_STR;
    case UNIFTI_DT_BINARY: return UNIFTI_DT_BINARY_STR;
    case UNIFTI_DT_UINT8: return UNIFTI_DT_UINT8_STR;
    case UNIFTI_DT_INT16: return UNIFTI_DT_INT16_STR;
    case UNIFTI_DT_INT32: return UNIFTI_DT_INT32_STR;
    case UNIFTI_DT_FLOAT32: return UNIFTI_DT_FLOAT32_STR;
    case UNIFTI_DT_COMPLEX64: return UNIFTI_DT_COMPLEX64_STR;
    case UNIFTI_DT_FLOAT64: return UNIFTI_DT_FLOAT64_STR;
    case UNIFTI_DT_RGB24: return UNIFTI_DT_RGB24_STR;
    case UNIFTI_DT_INT8: return UNIFTI_DT_INT8_STR;
    case UNIFTI_DT_UINT16: return UNIFTI_DT_UINT16_STR;
    case UNIFTI_DT_UINT32: return UNIFTI_DT_UINT32_STR;
    case UNIFTI_DT_INT64: return UNIFTI_DT_INT64_STR;
    case UNIFTI_DT_UINT64: return UNIFTI_DT_UINT64_STR;
    case UNIFTI_DT_FLOAT128: return UNIFTI_DT_FLOAT128_STR;
    case UNIFTI_DT_COMPLEX128: return UNIFTI_DT_COMPLEX128_STR;
    case UNIFTI_DT_COMPLEX256: return UNIFTI_DT_COMPLEX256_STR;
    case UNIFTI_DT_RGBA32: return UNIFTI_DT_RGBA32_STR;
  default: return NULL;
  }
}
/* Returns the dt value from its name. */
static inline int32_t unifti_dt_from_name(const char *t_dt) {
  if (t_dt == NULL) return -1;
  if (strcmp(t_dt, UNIFTI_DT_UNKNOWN_STR) == 0) return UNIFTI_DT_UNKNOWN;
    else if (strcmp(t_dt, UNIFTI_DT_UNKNOWN_STR) == 0) return UNIFTI_DT_UNKNOWN;
    else if (strcmp(t_dt, UNIFTI_DT_BINARY_STR) == 0) return UNIFTI_DT_BINARY;
    else if (strcmp(t_dt, UNIFTI_DT_UINT8_STR) == 0) return UNIFTI_DT_UINT8;
    else if (strcmp(t_dt, UNIFTI_DT_INT16_STR) == 0) return UNIFTI_DT_INT16;
    else if (strcmp(t_dt, UNIFTI_DT_INT32_STR) == 0) return UNIFTI_DT_INT32;
    else if (strcmp(t_dt, UNIFTI_DT_FLOAT32_STR) == 0) return UNIFTI_DT_FLOAT32;
    else if (strcmp(t_dt, UNIFTI_DT_COMPLEX64_STR) == 0) return UNIFTI_DT_COMPLEX64;
    else if (strcmp(t_dt, UNIFTI_DT_FLOAT64_STR) == 0) return UNIFTI_DT_FLOAT64;
    else if (strcmp(t_dt, UNIFTI_DT_RGB24_STR) == 0) return UNIFTI_DT_RGB24;
    else if (strcmp(t_dt, UNIFTI_DT_INT8_STR) == 0) return UNIFTI_DT_INT8;
    else if (strcmp(t_dt, UNIFTI_DT_UINT16_STR) == 0) return UNIFTI_DT_UINT16;
    else if (strcmp(t_dt, UNIFTI_DT_UINT32_STR) == 0) return UNIFTI_DT_UINT32;
    else if (strcmp(t_dt, UNIFTI_DT_INT64_STR) == 0) return UNIFTI_DT_INT64;
    else if (strcmp(t_dt, UNIFTI_DT_UINT64_STR) == 0) return UNIFTI_DT_UINT64;
    else if (strcmp(t_dt, UNIFTI_DT_FLOAT128_STR) == 0) return UNIFTI_DT_FLOAT128;
    else if (strcmp(t_dt, UNIFTI_DT_COMPLEX128_STR) == 0) return UNIFTI_DT_COMPLEX128;
    else if (strcmp(t_dt, UNIFTI_DT_COMPLEX256_STR) == 0) return UNIFTI_DT_COMPLEX256;
    else if (strcmp(t_dt, UNIFTI_DT_RGBA32_STR) == 0) return UNIFTI_DT_RGBA32;
  return -1;
}////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Enum intent //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief intent::none */
#define UNIFTI_INTENT_NONE 0
/** @brief intent::correl */
#define UNIFTI_INTENT_CORREL 2
/** @brief intent::ttest */
#define UNIFTI_INTENT_TTEST 3
/** @brief intent::ftest */
#define UNIFTI_INTENT_FTEST 4
/** @brief intent::zscore */
#define UNIFTI_INTENT_ZSCORE 5
/** @brief intent::chisq */
#define UNIFTI_INTENT_CHISQ 6
/** @brief intent::beta */
#define UNIFTI_INTENT_BETA 7
/** @brief intent::binom */
#define UNIFTI_INTENT_BINOM 8
/** @brief intent::gamma */
#define UNIFTI_INTENT_GAMMA 9
/** @brief intent::poisson */
#define UNIFTI_INTENT_POISSON 10
/** @brief intent::normal */
#define UNIFTI_INTENT_NORMAL 11
/** @brief intent::ftest_nonc */
#define UNIFTI_INTENT_FTEST_NONC 12
/** @brief intent::chisq_nonc */
#define UNIFTI_INTENT_CHISQ_NONC 13
/** @brief intent::logistic */
#define UNIFTI_INTENT_LOGISTIC 14
/** @brief intent::laplace */
#define UNIFTI_INTENT_LAPLACE 15
/** @brief intent::uniform */
#define UNIFTI_INTENT_UNIFORM 16
/** @brief intent::ttest_nonc */
#define UNIFTI_INTENT_TTEST_NONC 17
/** @brief intent::weibull */
#define UNIFTI_INTENT_WEIBULL 18
/** @brief intent::chi */
#define UNIFTI_INTENT_CHI 19
/** @brief intent::invgauss */
#define UNIFTI_INTENT_INVGAUSS 20
/** @brief intent::extval */
#define UNIFTI_INTENT_EXTVAL 21
/** @brief intent::pval */
#define UNIFTI_INTENT_PVAL 22
/** @brief intent::logpval */
#define UNIFTI_INTENT_LOGPVAL 23
/** @brief intent::log10pval */
#define UNIFTI_INTENT_LOG10PVAL 24
/** @brief intent::estimate */
#define UNIFTI_INTENT_ESTIMATE 1001
/** @brief intent::label */
#define UNIFTI_INTENT_LABEL 1002
/** @brief intent::neuroname */
#define UNIFTI_INTENT_NEURONAME 1003
/** @brief intent::genmatrix */
#define UNIFTI_INTENT_GENMATRIX 1004
/** @brief intent::symmatrix */
#define UNIFTI_INTENT_SYMMATRIX 1005
/** @brief intent::dispvect */
#define UNIFTI_INTENT_DISPVECT 1006
/** @brief intent::vector */
#define UNIFTI_INTENT_VECTOR 1007
/** @brief intent::pointset */
#define UNIFTI_INTENT_POINTSET 1008
/** @brief intent::triangle */
#define UNIFTI_INTENT_TRIANGLE 1009
/** @brief intent::quaternion */
#define UNIFTI_INTENT_QUATERNION 1010
/** @brief intent::dimless */
#define UNIFTI_INTENT_DIMLESS 1011
/** @brief intent::time_series */
#define UNIFTI_INTENT_TIME_SERIES 2001
/** @brief intent::node_index */
#define UNIFTI_INTENT_NODE_INDEX 2002
/** @brief intent::rgb_vector */
#define UNIFTI_INTENT_RGB_VECTOR 2003
/** @brief intent::rgba_vector */
#define UNIFTI_INTENT_RGBA_VECTOR 2004
/** @brief intent::shape */
#define UNIFTI_INTENT_SHAPE 2005
/** @brief intent::fsl_fnirt_displacement_field */
#define UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD 2006
/** @brief intent::fsl_cubic_spline_coefficients */
#define UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS 2007
/** @brief intent::fsl_dct_coefficients */
#define UNIFTI_INTENT_FSL_DCT_COEFFICIENTS 2008
/** @brief intent::fsl_quadratic_spline_coefficients */
#define UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS 2009
/** @brief intent::fsl_topup_cubic_spline_coefficients */
#define UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS 2016
/** @brief intent::fsl_topup_quadratic_spline_coefficients */
#define UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS 2017
/** @brief intent::fsl_topup_field */
#define UNIFTI_INTENT_FSL_TOPUP_FIELD 2018
/** @brief intent::none name string */
#define UNIFTI_INTENT_NONE_STR "none"
/** @brief intent::correl name string */
#define UNIFTI_INTENT_CORREL_STR "correl"
/** @brief intent::ttest name string */
#define UNIFTI_INTENT_TTEST_STR "ttest"
/** @brief intent::ftest name string */
#define UNIFTI_INTENT_FTEST_STR "ftest"
/** @brief intent::zscore name string */
#define UNIFTI_INTENT_ZSCORE_STR "zscore"
/** @brief intent::chisq name string */
#define UNIFTI_INTENT_CHISQ_STR "chisq"
/** @brief intent::beta name string */
#define UNIFTI_INTENT_BETA_STR "beta"
/** @brief intent::binom name string */
#define UNIFTI_INTENT_BINOM_STR "binom"
/** @brief intent::gamma name string */
#define UNIFTI_INTENT_GAMMA_STR "gamma"
/** @brief intent::poisson name string */
#define UNIFTI_INTENT_POISSON_STR "poisson"
/** @brief intent::normal name string */
#define UNIFTI_INTENT_NORMAL_STR "normal"
/** @brief intent::ftest_nonc name string */
#define UNIFTI_INTENT_FTEST_NONC_STR "ftest_nonc"
/** @brief intent::chisq_nonc name string */
#define UNIFTI_INTENT_CHISQ_NONC_STR "chisq_nonc"
/** @brief intent::logistic name string */
#define UNIFTI_INTENT_LOGISTIC_STR "logistic"
/** @brief intent::laplace name string */
#define UNIFTI_INTENT_LAPLACE_STR "laplace"
/** @brief intent::uniform name string */
#define UNIFTI_INTENT_UNIFORM_STR "uniform"
/** @brief intent::ttest_nonc name string */
#define UNIFTI_INTENT_TTEST_NONC_STR "ttest_nonc"
/** @brief intent::weibull name string */
#define UNIFTI_INTENT_WEIBULL_STR "weibull"
/** @brief intent::chi name string */
#define UNIFTI_INTENT_CHI_STR "chi"
/** @brief intent::invgauss name string */
#define UNIFTI_INTENT_INVGAUSS_STR "invgauss"
/** @brief intent::extval name string */
#define UNIFTI_INTENT_EXTVAL_STR "extval"
/** @brief intent::pval name string */
#define UNIFTI_INTENT_PVAL_STR "pval"
/** @brief intent::logpval name string */
#define UNIFTI_INTENT_LOGPVAL_STR "logpval"
/** @brief intent::log10pval name string */
#define UNIFTI_INTENT_LOG10PVAL_STR "log10pval"
/** @brief intent::estimate name string */
#define UNIFTI_INTENT_ESTIMATE_STR "estimate"
/** @brief intent::label name string */
#define UNIFTI_INTENT_LABEL_STR "label"
/** @brief intent::neuroname name string */
#define UNIFTI_INTENT_NEURONAME_STR "neuroname"
/** @brief intent::genmatrix name string */
#define UNIFTI_INTENT_GENMATRIX_STR "genmatrix"
/** @brief intent::symmatrix name string */
#define UNIFTI_INTENT_SYMMATRIX_STR "symmatrix"
/** @brief intent::dispvect name string */
#define UNIFTI_INTENT_DISPVECT_STR "dispvect"
/** @brief intent::vector name string */
#define UNIFTI_INTENT_VECTOR_STR "vector"
/** @brief intent::pointset name string */
#define UNIFTI_INTENT_POINTSET_STR "pointset"
/** @brief intent::triangle name string */
#define UNIFTI_INTENT_TRIANGLE_STR "triangle"
/** @brief intent::quaternion name string */
#define UNIFTI_INTENT_QUATERNION_STR "quaternion"
/** @brief intent::dimless name string */
#define UNIFTI_INTENT_DIMLESS_STR "dimless"
/** @brief intent::time_series name string */
#define UNIFTI_INTENT_TIME_SERIES_STR "time_series"
/** @brief intent::node_index name string */
#define UNIFTI_INTENT_NODE_INDEX_STR "node_index"
/** @brief intent::rgb_vector name string */
#define UNIFTI_INTENT_RGB_VECTOR_STR "rgb_vector"
/** @brief intent::rgba_vector name string */
#define UNIFTI_INTENT_RGBA_VECTOR_STR "rgba_vector"
/** @brief intent::shape name string */
#define UNIFTI_INTENT_SHAPE_STR "shape"
/** @brief intent::fsl_fnirt_displacement_field name string */
#define UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_STR "fsl_fnirt_displacement_field"
/** @brief intent::fsl_cubic_spline_coefficients name string */
#define UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_STR "fsl_cubic_spline_coefficients"
/** @brief intent::fsl_dct_coefficients name string */
#define UNIFTI_INTENT_FSL_DCT_COEFFICIENTS_STR "fsl_dct_coefficients"
/** @brief intent::fsl_quadratic_spline_coefficients name string */
#define UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_STR "fsl_quadratic_spline_coefficients"
/** @brief intent::fsl_topup_cubic_spline_coefficients name string */
#define UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_STR "fsl_topup_cubic_spline_coefficients"
/** @brief intent::fsl_topup_quadratic_spline_coefficients name string */
#define UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_STR "fsl_topup_quadratic_spline_coefficients"
/** @brief intent::fsl_topup_field name string */
#define UNIFTI_INTENT_FSL_TOPUP_FIELD_STR "fsl_topup_field"

/* Returns the name of the intent value. */
static inline const char *unifti_intent_name(const int32_t value) {
  switch (value) {
    case UNIFTI_INTENT_NONE: return UNIFTI_INTENT_NONE_STR;
    case UNIFTI_INTENT_CORREL: return UNIFTI_INTENT_CORREL_STR;
    case UNIFTI_INTENT_TTEST: return UNIFTI_INTENT_TTEST_STR;
    case UNIFTI_INTENT_FTEST: return UNIFTI_INTENT_FTEST_STR;
    case UNIFTI_INTENT_ZSCORE: return UNIFTI_INTENT_ZSCORE_STR;
    case UNIFTI_INTENT_CHISQ: return UNIFTI_INTENT_CHISQ_STR;
    case UNIFTI_INTENT_BETA: return UNIFTI_INTENT_BETA_STR;
    case UNIFTI_INTENT_BINOM: return UNIFTI_INTENT_BINOM_STR;
    case UNIFTI_INTENT_GAMMA: return UNIFTI_INTENT_GAMMA_STR;
    case UNIFTI_INTENT_POISSON: return UNIFTI_INTENT_POISSON_STR;
    case UNIFTI_INTENT_NORMAL: return UNIFTI_INTENT_NORMAL_STR;
    case UNIFTI_INTENT_FTEST_NONC: return UNIFTI_INTENT_FTEST_NONC_STR;
    case UNIFTI_INTENT_CHISQ_NONC: return UNIFTI_INTENT_CHISQ_NONC_STR;
    case UNIFTI_INTENT_LOGISTIC: return UNIFTI_INTENT_LOGISTIC_STR;
    case UNIFTI_INTENT_LAPLACE: return UNIFTI_INTENT_LAPLACE_STR;
    case UNIFTI_INTENT_UNIFORM: return UNIFTI_INTENT_UNIFORM_STR;
    case UNIFTI_INTENT_TTEST_NONC: return UNIFTI_INTENT_TTEST_NONC_STR;
    case UNIFTI_INTENT_WEIBULL: return UNIFTI_INTENT_WEIBULL_STR;
    case UNIFTI_INTENT_CHI: return UNIFTI_INTENT_CHI_STR;
    case UNIFTI_INTENT_INVGAUSS: return UNIFTI_INTENT_INVGAUSS_STR;
    case UNIFTI_INTENT_EXTVAL: return UNIFTI_INTENT_EXTVAL_STR;
    case UNIFTI_INTENT_PVAL: return UNIFTI_INTENT_PVAL_STR;
    case UNIFTI_INTENT_LOGPVAL: return UNIFTI_INTENT_LOGPVAL_STR;
    case UNIFTI_INTENT_LOG10PVAL: return UNIFTI_INTENT_LOG10PVAL_STR;
    case UNIFTI_INTENT_ESTIMATE: return UNIFTI_INTENT_ESTIMATE_STR;
    case UNIFTI_INTENT_LABEL: return UNIFTI_INTENT_LABEL_STR;
    case UNIFTI_INTENT_NEURONAME: return UNIFTI_INTENT_NEURONAME_STR;
    case UNIFTI_INTENT_GENMATRIX: return UNIFTI_INTENT_GENMATRIX_STR;
    case UNIFTI_INTENT_SYMMATRIX: return UNIFTI_INTENT_SYMMATRIX_STR;
    case UNIFTI_INTENT_DISPVECT: return UNIFTI_INTENT_DISPVECT_STR;
    case UNIFTI_INTENT_VECTOR: return UNIFTI_INTENT_VECTOR_STR;
    case UNIFTI_INTENT_POINTSET: return UNIFTI_INTENT_POINTSET_STR;
    case UNIFTI_INTENT_TRIANGLE: return UNIFTI_INTENT_TRIANGLE_STR;
    case UNIFTI_INTENT_QUATERNION: return UNIFTI_INTENT_QUATERNION_STR;
    case UNIFTI_INTENT_DIMLESS: return UNIFTI_INTENT_DIMLESS_STR;
    case UNIFTI_INTENT_TIME_SERIES: return UNIFTI_INTENT_TIME_SERIES_STR;
    case UNIFTI_INTENT_NODE_INDEX: return UNIFTI_INTENT_NODE_INDEX_STR;
    case UNIFTI_INTENT_RGB_VECTOR: return UNIFTI_INTENT_RGB_VECTOR_STR;
    case UNIFTI_INTENT_RGBA_VECTOR: return UNIFTI_INTENT_RGBA_VECTOR_STR;
    case UNIFTI_INTENT_SHAPE: return UNIFTI_INTENT_SHAPE_STR;
    case UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD: return UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_STR;
    case UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS: return UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_STR;
    case UNIFTI_INTENT_FSL_DCT_COEFFICIENTS: return UNIFTI_INTENT_FSL_DCT_COEFFICIENTS_STR;
    case UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS: return UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_STR;
    case UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS: return UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_STR;
    case UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS: return UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_STR;
    case UNIFTI_INTENT_FSL_TOPUP_FIELD: return UNIFTI_INTENT_FSL_TOPUP_FIELD_STR;
  default: return NULL;
  }
}
/* Returns the intent value from its name. */
static inline int32_t unifti_intent_from_name(const char *t_intent) {
  if (t_intent == NULL) return -1;
  if (strcmp(t_intent, UNIFTI_INTENT_NONE_STR) == 0) return UNIFTI_INTENT_NONE;
    else if (strcmp(t_intent, UNIFTI_INTENT_NONE_STR) == 0) return UNIFTI_INTENT_NONE;
    else if (strcmp(t_intent, UNIFTI_INTENT_CORREL_STR) == 0) return UNIFTI_INTENT_CORREL;
    else if (strcmp(t_intent, UNIFTI_INTENT_TTEST_STR) == 0) return UNIFTI_INTENT_TTEST;
    else if (strcmp(t_intent, UNIFTI_INTENT_FTEST_STR) == 0) return UNIFTI_INTENT_FTEST;
    else if (strcmp(t_intent, UNIFTI_INTENT_ZSCORE_STR) == 0) return UNIFTI_INTENT_ZSCORE;
    else if (strcmp(t_intent, UNIFTI_INTENT_CHISQ_STR) == 0) return UNIFTI_INTENT_CHISQ;
    else if (strcmp(t_intent, UNIFTI_INTENT_BETA_STR) == 0) return UNIFTI_INTENT_BETA;
    else if (strcmp(t_intent, UNIFTI_INTENT_BINOM_STR) == 0) return UNIFTI_INTENT_BINOM;
    else if (strcmp(t_intent, UNIFTI_INTENT_GAMMA_STR) == 0) return UNIFTI_INTENT_GAMMA;
    else if (strcmp(t_intent, UNIFTI_INTENT_POISSON_STR) == 0) return UNIFTI_INTENT_POISSON;
    else if (strcmp(t_intent, UNIFTI_INTENT_NORMAL_STR) == 0) return UNIFTI_INTENT_NORMAL;
    else if (strcmp(t_intent, UNIFTI_INTENT_FTEST_NONC_STR) == 0) return UNIFTI_INTENT_FTEST_NONC;
    else if (strcmp(t_intent, UNIFTI_INTENT_CHISQ_NONC_STR) == 0) return UNIFTI_INTENT_CHISQ_NONC;
    else if (strcmp(t_intent, UNIFTI_INTENT_LOGISTIC_STR) == 0) return UNIFTI_INTENT_LOGISTIC;
    else if (strcmp(t_intent, UNIFTI_INTENT_LAPLACE_STR) == 0) return UNIFTI_INTENT_LAPLACE;
    else if (strcmp(t_intent, UNIFTI_INTENT_UNIFORM_STR) == 0) return UNIFTI_INTENT_UNIFORM;
    else if (strcmp(t_intent, UNIFTI_INTENT_TTEST_NONC_STR) == 0) return UNIFTI_INTENT_TTEST_NONC;
    else if (strcmp(t_intent, UNIFTI_INTENT_WEIBULL_STR) == 0) return UNIFTI_INTENT_WEIBULL;
    else if (strcmp(t_intent, UNIFTI_INTENT_CHI_STR) == 0) return UNIFTI_INTENT_CHI;
    else if (strcmp(t_intent, UNIFTI_INTENT_INVGAUSS_STR) == 0) return UNIFTI_INTENT_INVGAUSS;
    else if (strcmp(t_intent, UNIFTI_INTENT_EXTVAL_STR) == 0) return UNIFTI_INTENT_EXTVAL;
    else if (strcmp(t_intent, UNIFTI_INTENT_PVAL_STR) == 0) return UNIFTI_INTENT_PVAL;
    else if (strcmp(t_intent, UNIFTI_INTENT_LOGPVAL_STR) == 0) return UNIFTI_INTENT_LOGPVAL;
    else if (strcmp(t_intent, UNIFTI_INTENT_LOG10PVAL_STR) == 0) return UNIFTI_INTENT_LOG10PVAL;
    else if (strcmp(t_intent, UNIFTI_INTENT_ESTIMATE_STR) == 0) return UNIFTI_INTENT_ESTIMATE;
    else if (strcmp(t_intent, UNIFTI_INTENT_LABEL_STR) == 0) return UNIFTI_INTENT_LABEL;
    else if (strcmp(t_intent, UNIFTI_INTENT_NEURONAME_STR) == 0) return UNIFTI_INTENT_NEURONAME;
    else if (strcmp(t_intent, UNIFTI_INTENT_GENMATRIX_STR) == 0) return UNIFTI_INTENT_GENMATRIX;
    else if (strcmp(t_intent, UNIFTI_INTENT_SYMMATRIX_STR) == 0) return UNIFTI_INTENT_SYMMATRIX;
    else if (strcmp(t_intent, UNIFTI_INTENT_DISPVECT_STR) == 0) return UNIFTI_INTENT_DISPVECT;
    else if (strcmp(t_intent, UNIFTI_INTENT_VECTOR_STR) == 0) return UNIFTI_INTENT_VECTOR;
    else if (strcmp(t_intent, UNIFTI_INTENT_POINTSET_STR) == 0) return UNIFTI_INTENT_POINTSET;
    else if (strcmp(t_intent, UNIFTI_INTENT_TRIANGLE_STR) == 0) return UNIFTI_INTENT_TRIANGLE;
    else if (strcmp(t_intent, UNIFTI_INTENT_QUATERNION_STR) == 0) return UNIFTI_INTENT_QUATERNION;
    else if (strcmp(t_intent, UNIFTI_INTENT_DIMLESS_STR) == 0) return UNIFTI_INTENT_DIMLESS;
    else if (strcmp(t_intent, UNIFTI_INTENT_TIME_SERIES_STR) == 0) return UNIFTI_INTENT_TIME_SERIES;
    else if (strcmp(t_intent, UNIFTI_INTENT_NODE_INDEX_STR) == 0) return UNIFTI_INTENT_NODE_INDEX;
    else if (strcmp(t_intent, UNIFTI_INTENT_RGB_VECTOR_STR) == 0) return UNIFTI_INTENT_RGB_VECTOR;
    else if (strcmp(t_intent, UNIFTI_INTENT_RGBA_VECTOR_STR) == 0) return UNIFTI_INTENT_RGBA_VECTOR;
    else if (strcmp(t_intent, UNIFTI_INTENT_SHAPE_STR) == 0) return UNIFTI_INTENT_SHAPE;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_STR) == 0) return UNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_STR) == 0) return UNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_DCT_COEFFICIENTS_STR) == 0) return UNIFTI_INTENT_FSL_DCT_COEFFICIENTS;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_STR) == 0) return UNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_STR) == 0) return UNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_STR) == 0) return UNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS;
    else if (strcmp(t_intent, UNIFTI_INTENT_FSL_TOPUP_FIELD_STR) == 0) return UNIFTI_INTENT_FSL_TOPUP_FIELD;
  return -1;
}////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Enum xform //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief Arbitrary coordinates. (xform::unknown) */
#define UNIFTI_XFORM_UNKNOWN 0
/** @brief Scanner-based anatomical coordinates. (xform::scanner_anat) */
#define UNIFTI_XFORM_SCANNER_ANAT 1
/** @brief Coordinates aligned to another file's, or to the anatomical "truth" (with an arbitrary coordinate center). (xform::aligned_anat) */
#define UNIFTI_XFORM_ALIGNED_ANAT 2
/** @brief Coordinates aligned to the Talairach space. (xform::talairach) */
#define UNIFTI_XFORM_TALAIRACH 3
/** @brief Coordinates aligned to the MNI152 space. (xform::mni_152) */
#define UNIFTI_XFORM_MNI_152 4
/** @brief Coordinates aligned to some template that is not MNI152 or Talairach. (xform::template_other) */
#define UNIFTI_XFORM_TEMPLATE_OTHER 5
/** @brief xform::unknown name string */
#define UNIFTI_XFORM_UNKNOWN_STR "unknown"
/** @brief xform::scanner_anat name string */
#define UNIFTI_XFORM_SCANNER_ANAT_STR "scanner_anat"
/** @brief xform::aligned_anat name string */
#define UNIFTI_XFORM_ALIGNED_ANAT_STR "aligned_anat"
/** @brief xform::talairach name string */
#define UNIFTI_XFORM_TALAIRACH_STR "talairach"
/** @brief xform::mni_152 name string */
#define UNIFTI_XFORM_MNI_152_STR "mni_152"
/** @brief xform::template_other name string */
#define UNIFTI_XFORM_TEMPLATE_OTHER_STR "template_other"

/* Returns the name of the xform value. */
static inline const char *unifti_xform_name(const int32_t value) {
  switch (value) {
    case UNIFTI_XFORM_UNKNOWN: return UNIFTI_XFORM_UNKNOWN_STR;
    case UNIFTI_XFORM_SCANNER_ANAT: return UNIFTI_XFORM_SCANNER_ANAT_STR;
    case UNIFTI_XFORM_ALIGNED_ANAT: return UNIFTI_XFORM_ALIGNED_ANAT_STR;
    case UNIFTI_XFORM_TALAIRACH: return UNIFTI_XFORM_TALAIRACH_STR;
    case UNIFTI_XFORM_MNI_152: return UNIFTI_XFORM_MNI_152_STR;
    case UNIFTI_XFORM_TEMPLATE_OTHER: return UNIFTI_XFORM_TEMPLATE_OTHER_STR;
  default: return NULL;
  }
}
/* Returns the xform value from its name. */
static inline int32_t unifti_xform_from_name(const char *t_xform) {
  if (t_xform == NULL) return -1;
  if (strcmp(t_xform, UNIFTI_XFORM_UNKNOWN_STR) == 0) return UNIFTI_XFORM_UNKNOWN;
    else if (strcmp(t_xform, UNIFTI_XFORM_UNKNOWN_STR) == 0) return UNIFTI_XFORM_UNKNOWN;
    else if (strcmp(t_xform, UNIFTI_XFORM_SCANNER_ANAT_STR) == 0) return UNIFTI_XFORM_SCANNER_ANAT;
    else if (strcmp(t_xform, UNIFTI_XFORM_ALIGNED_ANAT_STR) == 0) return UNIFTI_XFORM_ALIGNED_ANAT;
    else if (strcmp(t_xform, UNIFTI_XFORM_TALAIRACH_STR) == 0) return UNIFTI_XFORM_TALAIRACH;
    else if (strcmp(t_xform, UNIFTI_XFORM_MNI_152_STR) == 0) return UNIFTI_XFORM_MNI_152;
    else if (strcmp(t_xform, UNIFTI_XFORM_TEMPLATE_OTHER_STR) == 0) return UNIFTI_XFORM_TEMPLATE_OTHER;
  return -1;
}////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Enum units //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief Unknown units (units::unknown) */
#define UNIFTI_UNITS_UNKNOWN 0
/** @brief Meter (m) (units::meter) */
#define UNIFTI_UNITS_METER 1
/** @brief Millimeter (mm) (units::mm) */
#define UNIFTI_UNITS_MM 2
/** @brief Micron (um) (units::micron) */
#define UNIFTI_UNITS_MICRON 3
/** @brief Seconds (s) (units::sec) */
#define UNIFTI_UNITS_SEC 8
/** @brief Miliseconds (ms) (units::msec) */
#define UNIFTI_UNITS_MSEC 16
/** @brief Microseconds (us) (units::usec) */
#define UNIFTI_UNITS_USEC 24
/** @brief Hertz (Hz) (units::hz) */
#define UNIFTI_UNITS_HZ 32
/** @brief Parts-per-million (ppm) (units::ppm) */
#define UNIFTI_UNITS_PPM 40
/** @brief Radians per second (rad/s) (units::rads) */
#define UNIFTI_UNITS_RADS 48
/** @brief units::unknown name string */
#define UNIFTI_UNITS_UNKNOWN_STR "unknown"
/** @brief units::meter name string */
#define UNIFTI_UNITS_METER_STR "meter"
/** @brief units::mm name string */
#define UNIFTI_UNITS_MM_STR "mm"
/** @brief units::micron name string */
#define UNIFTI_UNITS_MICRON_STR "micron"
/** @brief units::sec name string */
#define UNIFTI_UNITS_SEC_STR "sec"
/** @brief units::msec name string */
#define UNIFTI_UNITS_MSEC_STR "msec"
/** @brief units::usec name string */
#define UNIFTI_UNITS_USEC_STR "usec"
/** @brief units::hz name string */
#define UNIFTI_UNITS_HZ_STR "hz"
/** @brief units::ppm name string */
#define UNIFTI_UNITS_PPM_STR "ppm"
/** @brief units::rads name string */
#define UNIFTI_UNITS_RADS_STR "rads"

/* Returns the name of the units value. */
static inline const char *unifti_units_name(const int32_t value) {
  switch (value) {
    case UNIFTI_UNITS_UNKNOWN: return UNIFTI_UNITS_UNKNOWN_STR;
    case UNIFTI_UNITS_METER: return UNIFTI_UNITS_METER_STR;
    case UNIFTI_UNITS_MM: return UNIFTI_UNITS_MM_STR;
    case UNIFTI_UNITS_MICRON: return UNIFTI_UNITS_MICRON_STR;
    case UNIFTI_UNITS_SEC: return UNIFTI_UNITS_SEC_STR;
    case UNIFTI_UNITS_MSEC: return UNIFTI_UNITS_MSEC_STR;
    case UNIFTI_UNITS_USEC: return UNIFTI_UNITS_USEC_STR;
    case UNIFTI_UNITS_HZ: return UNIFTI_UNITS_HZ_STR;
    case UNIFTI_UNITS_PPM: return UNIFTI_UNITS_PPM_STR;
    case UNIFTI_UNITS_RADS: return UNIFTI_UNITS_RADS_STR;
  default: return NULL;
  }
}
/* Returns the units value from its name. */
static inline int32_t unifti_units_from_name(const char *t_units) {
  if (t_units == NULL) return -1;
  if (strcmp(t_units, UNIFTI_UNITS_UNKNOWN_STR) == 0) return UNIFTI_UNITS_UNKNOWN;
    else if (strcmp(t_units, UNIFTI_UNITS_UNKNOWN_STR) == 0) return UNIFTI_UNITS_UNKNOWN;
    else if (strcmp(t_units, UNIFTI_UNITS_METER_STR) == 0) return UNIFTI_UNITS_METER;
    else if (strcmp(t_units, UNIFTI_UNITS_MM_STR) == 0) return UNIFTI_UNITS_MM;
    else if (strcmp(t_units, UNIFTI_UNITS_MICRON_STR) == 0) return UNIFTI_UNITS_MICRON;
    else if (strcmp(t_units, UNIFTI_UNITS_SEC_STR) == 0) return UNIFTI_UNITS_SEC;
    else if (strcmp(t_units, UNIFTI_UNITS_MSEC_STR) == 0) return UNIFTI_UNITS_MSEC;
    else if (strcmp(t_units, UNIFTI_UNITS_USEC_STR) == 0) return UNIFTI_UNITS_USEC;
    else if (strcmp(t_units, UNIFTI_UNITS_HZ_STR) == 0) return UNIFTI_UNITS_HZ;
    else if (strcmp(t_units, UNIFTI_UNITS_PPM_STR) == 0) return UNIFTI_UNITS_PPM;
    else if (strcmp(t_units, UNIFTI_UNITS_RADS_STR) == 0) return UNIFTI_UNITS_RADS;
  return -1;
}////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Enum slice //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief Slice order: Unknown (slice::unknown) */
#define UNIFTI_SLICE_UNKNOWN 0
/** @brief Slice order: Sequential, increasing (slice::seq_inc) */
#define UNIFTI_SLICE_SEQ_INC 1
/** @brief Slice order: Sequential, decreasing (slice::seq_dec) */
#define UNIFTI_SLICE_SEQ_DEC 2
/** @brief Slice order: Interleaved, increasing, starting at the first slice (slice::alt_inc) */
#define UNIFTI_SLICE_ALT_INC 3
/** @brief Slice order: Interleaved, decreasing, starting at the last slice (slice::alt_dec) */
#define UNIFTI_SLICE_ALT_DEC 4
/** @brief Slice order: Interleaved, increasing, starting at the second slice (slice::alt_inc2) */
#define UNIFTI_SLICE_ALT_INC2 5
/** @brief Slice order: Interleaved, decreasing, starting at the second to last slice (slice::alt_dec2) */
#define UNIFTI_SLICE_ALT_DEC2 6
/** @brief slice::unknown name string */
#define UNIFTI_SLICE_UNKNOWN_STR "unknown"
/** @brief slice::seq_inc name string */
#define UNIFTI_SLICE_SEQ_INC_STR "seq_inc"
/** @brief slice::seq_dec name string */
#define UNIFTI_SLICE_SEQ_DEC_STR "seq_dec"
/** @brief slice::alt_inc name string */
#define UNIFTI_SLICE_ALT_INC_STR "alt_inc"
/** @brief slice::alt_dec name string */
#define UNIFTI_SLICE_ALT_DEC_STR "alt_dec"
/** @brief slice::alt_inc2 name string */
#define UNIFTI_SLICE_ALT_INC2_STR "alt_inc2"
/** @brief slice::alt_dec2 name string */
#define UNIFTI_SLICE_ALT_DEC2_STR "alt_dec2"

/* Returns the name of the slice value. */
static inline const char *unifti_slice_name(const int32_t value) {
  switch (value) {
    case UNIFTI_SLICE_UNKNOWN: return UNIFTI_SLICE_UNKNOWN_STR;
    case UNIFTI_SLICE_SEQ_INC: return UNIFTI_SLICE_SEQ_INC_STR;
    case UNIFTI_SLICE_SEQ_DEC: return UNIFTI_SLICE_SEQ_DEC_STR;
    case UNIFTI_SLICE_ALT_INC: return UNIFTI_SLICE_ALT_INC_STR;
    case UNIFTI_SLICE_ALT_DEC: return UNIFTI_SLICE_ALT_DEC_STR;
    case UNIFTI_SLICE_ALT_INC2: return UNIFTI_SLICE_ALT_INC2_STR;
    case UNIFTI_SLICE_ALT_DEC2: return UNIFTI_SLICE_ALT_DEC2_STR;
  default: return NULL;
  }
}
/* Returns the slice value from its name. */
static inline int32_t unifti_slice_from_name(const char *t_slice) {
  if (t_slice == NULL) return -1;
  if (strcmp(t_slice, UNIFTI_SLICE_UNKNOWN_STR) == 0) return UNIFTI_SLICE_UNKNOWN;
    else if (strcmp(t_slice, UNIFTI_SLICE_UNKNOWN_STR) == 0) return UNIFTI_SLICE_UNKNOWN;
    else if (strcmp(t_slice, UNIFTI_SLICE_SEQ_INC_STR) == 0) return UNIFTI_SLICE_SEQ_INC;
    else if (strcmp(t_slice, UNIFTI_SLICE_SEQ_DEC_STR) == 0) return UNIFTI_SLICE_SEQ_DEC;
    else if (strcmp(t_slice, UNIFTI_SLICE_ALT_INC_STR) == 0) return UNIFTI_SLICE_ALT_INC;
    else if (strcmp(t_slice, UNIFTI_SLICE_ALT_DEC_STR) == 0) return UNIFTI_SLICE_ALT_DEC;
    else if (strcmp(t_slice, UNIFTI_SLICE_ALT_INC2_STR) == 0) return UNIFTI_SLICE_ALT_INC2;
    else if (strcmp(t_slice, UNIFTI_SLICE_ALT_DEC2_STR) == 0) return UNIFTI_SLICE_ALT_DEC2;
  return -1;
}////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Enum ecode //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** @brief ecode::ignore */
#define UNIFTI_ECODE_IGNORE 0
/** @brief intended for raw DICOM attributes (ecode::dicom) */
#define UNIFTI_ECODE_DICOM 2
/**
 * @brief Robert W Cox: rwcox\@nih.gov
 * https://afni.nimh.nih.gov/afni
 *  (ecode::afni)
 */
#define UNIFTI_ECODE_AFNI 4
/** @brief plain ASCII text only (ecode::comment) */
#define UNIFTI_ECODE_COMMENT 6
/**
 * @brief David B Keator: dbkeator\@uci.edu
 * http://www.nbirn.net/Resources/Users/Applications/xcede/index.htm
 *  (ecode::xcede)
 */
#define UNIFTI_ECODE_XCEDE 8
/**
 * @brief Mark A Horsfield
 * mah5\@leicester.ac.uk
 *  (ecode::jimdiminfo)
 */
#define UNIFTI_ECODE_JIMDIMINFO 10
/**
 * @brief Kate Fissell: fissell\@pitt.edu
 * http://kraepelin.wpic.pitt.edu/~fissell/NIFTI_ECODE_WORKFLOW_FWDS/NIFTI_ECODE_WORKFLOW_FWDS.html
 *  (ecode::workflow_fwds)
 */
#define UNIFTI_ECODE_WORKFLOW_FWDS 12
/** @brief http://surfer.nmr.mgh.harvard.edu/ (ecode::freesurfer) */
#define UNIFTI_ECODE_FREESURFER 14
/** @brief embedded Python objects (ecode::pypickle) */
#define UNIFTI_ECODE_PYPICKLE 16
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::mind_ident)
 */
#define UNIFTI_ECODE_MIND_IDENT 18
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::b_value)
 */
#define UNIFTI_ECODE_B_VALUE 20
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::spherical_direction)
 */
#define UNIFTI_ECODE_SPHERICAL_DIRECTION 22
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::dt_component)
 */
#define UNIFTI_ECODE_DT_COMPONENT 24
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::shc_degreeorder)
 */
#define UNIFTI_ECODE_SHC_DEGREEORDER 26
/** @brief Dan Kimberg: www.voxbo.org (ecode::voxbo) */
#define UNIFTI_ECODE_VOXBO 28
/**
 * @brief John Harwell: john\@brainvis.wustl.edu
 * http://brainvis.wustl.edu/wiki/index.php/Caret:Documentation:CaretNiftiExtension
 *  (ecode::caret)
 */
#define UNIFTI_ECODE_CARET 30
/** @brief CIFTI-2_Main_FINAL_1March2014.pdf (ecode::cifti) */
#define UNIFTI_ECODE_CIFTI 32
/** @brief ecode::variable_frame_timing */
#define UNIFTI_ECODE_VARIABLE_FRAME_TIMING 34
/** @brief Munster University Hospital (ecode::eval) */
#define UNIFTI_ECODE_EVAL 38
/**
 * @brief MATLAB extension
 * http://www.mathworks.com/matlabcentral/fileexchange/42997-dicom-to-nifti-converter
 *  (ecode::matlab)
 */
#define UNIFTI_ECODE_MATLAB 40
/**
 * @brief Quantiphyse extension
 * https://quantiphyse.readthedocs.io/en/latest/advanced/nifti_extension.html
 *  (ecode::quantiphyse)
 */
#define UNIFTI_ECODE_QUANTIPHYSE 42
/**
 * @brief Magnetic Resonance Spectroscopy (MRS)
 *  (ecode::mrs)
 */
#define UNIFTI_ECODE_MRS 44
/** @brief ecode::ignore name string */
#define UNIFTI_ECODE_IGNORE_STR "ignore"
/** @brief ecode::dicom name string */
#define UNIFTI_ECODE_DICOM_STR "dicom"
/** @brief ecode::afni name string */
#define UNIFTI_ECODE_AFNI_STR "afni"
/** @brief ecode::comment name string */
#define UNIFTI_ECODE_COMMENT_STR "comment"
/** @brief ecode::xcede name string */
#define UNIFTI_ECODE_XCEDE_STR "xcede"
/** @brief ecode::jimdiminfo name string */
#define UNIFTI_ECODE_JIMDIMINFO_STR "jimdiminfo"
/** @brief ecode::workflow_fwds name string */
#define UNIFTI_ECODE_WORKFLOW_FWDS_STR "workflow_fwds"
/** @brief ecode::freesurfer name string */
#define UNIFTI_ECODE_FREESURFER_STR "freesurfer"
/** @brief ecode::pypickle name string */
#define UNIFTI_ECODE_PYPICKLE_STR "pypickle"
/** @brief ecode::mind_ident name string */
#define UNIFTI_ECODE_MIND_IDENT_STR "mind_ident"
/** @brief ecode::b_value name string */
#define UNIFTI_ECODE_B_VALUE_STR "b_value"
/** @brief ecode::spherical_direction name string */
#define UNIFTI_ECODE_SPHERICAL_DIRECTION_STR "spherical_direction"
/** @brief ecode::dt_component name string */
#define UNIFTI_ECODE_DT_COMPONENT_STR "dt_component"
/** @brief ecode::shc_degreeorder name string */
#define UNIFTI_ECODE_SHC_DEGREEORDER_STR "shc_degreeorder"
/** @brief ecode::voxbo name string */
#define UNIFTI_ECODE_VOXBO_STR "voxbo"
/** @brief ecode::caret name string */
#define UNIFTI_ECODE_CARET_STR "caret"
/** @brief ecode::cifti name string */
#define UNIFTI_ECODE_CIFTI_STR "cifti"
/** @brief ecode::variable_frame_timing name string */
#define UNIFTI_ECODE_VARIABLE_FRAME_TIMING_STR "variable_frame_timing"
/** @brief ecode::eval name string */
#define UNIFTI_ECODE_EVAL_STR "eval"
/** @brief ecode::matlab name string */
#define UNIFTI_ECODE_MATLAB_STR "matlab"
/** @brief ecode::quantiphyse name string */
#define UNIFTI_ECODE_QUANTIPHYSE_STR "quantiphyse"
/** @brief ecode::mrs name string */
#define UNIFTI_ECODE_MRS_STR "mrs"

/* Returns the name of the ecode value. */
static inline const char *unifti_ecode_name(const int32_t value) {
  switch (value) {
    case UNIFTI_ECODE_IGNORE: return UNIFTI_ECODE_IGNORE_STR;
    case UNIFTI_ECODE_DICOM: return UNIFTI_ECODE_DICOM_STR;
    case UNIFTI_ECODE_AFNI: return UNIFTI_ECODE_AFNI_STR;
    case UNIFTI_ECODE_COMMENT: return UNIFTI_ECODE_COMMENT_STR;
    case UNIFTI_ECODE_XCEDE: return UNIFTI_ECODE_XCEDE_STR;
    case UNIFTI_ECODE_JIMDIMINFO: return UNIFTI_ECODE_JIMDIMINFO_STR;
    case UNIFTI_ECODE_WORKFLOW_FWDS: return UNIFTI_ECODE_WORKFLOW_FWDS_STR;
    case UNIFTI_ECODE_FREESURFER: return UNIFTI_ECODE_FREESURFER_STR;
    case UNIFTI_ECODE_PYPICKLE: return UNIFTI_ECODE_PYPICKLE_STR;
    case UNIFTI_ECODE_MIND_IDENT: return UNIFTI_ECODE_MIND_IDENT_STR;
    case UNIFTI_ECODE_B_VALUE: return UNIFTI_ECODE_B_VALUE_STR;
    case UNIFTI_ECODE_SPHERICAL_DIRECTION: return UNIFTI_ECODE_SPHERICAL_DIRECTION_STR;
    case UNIFTI_ECODE_DT_COMPONENT: return UNIFTI_ECODE_DT_COMPONENT_STR;
    case UNIFTI_ECODE_SHC_DEGREEORDER: return UNIFTI_ECODE_SHC_DEGREEORDER_STR;
    case UNIFTI_ECODE_VOXBO: return UNIFTI_ECODE_VOXBO_STR;
    case UNIFTI_ECODE_CARET: return UNIFTI_ECODE_CARET_STR;
    case UNIFTI_ECODE_CIFTI: return UNIFTI_ECODE_CIFTI_STR;
    case UNIFTI_ECODE_VARIABLE_FRAME_TIMING: return UNIFTI_ECODE_VARIABLE_FRAME_TIMING_STR;
    case UNIFTI_ECODE_EVAL: return UNIFTI_ECODE_EVAL_STR;
    case UNIFTI_ECODE_MATLAB: return UNIFTI_ECODE_MATLAB_STR;
    case UNIFTI_ECODE_QUANTIPHYSE: return UNIFTI_ECODE_QUANTIPHYSE_STR;
    case UNIFTI_ECODE_MRS: return UNIFTI_ECODE_MRS_STR;
  default: return NULL;
  }
}
/* Returns the ecode value from its name. */
static inline int32_t unifti_ecode_from_name(const char *t_ecode) {
  if (t_ecode == NULL) return -1;
  if (strcmp(t_ecode, UNIFTI_ECODE_IGNORE_STR) == 0) return UNIFTI_ECODE_IGNORE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_IGNORE_STR) == 0) return UNIFTI_ECODE_IGNORE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_DICOM_STR) == 0) return UNIFTI_ECODE_DICOM;
    else if (strcmp(t_ecode, UNIFTI_ECODE_AFNI_STR) == 0) return UNIFTI_ECODE_AFNI;
    else if (strcmp(t_ecode, UNIFTI_ECODE_COMMENT_STR) == 0) return UNIFTI_ECODE_COMMENT;
    else if (strcmp(t_ecode, UNIFTI_ECODE_XCEDE_STR) == 0) return UNIFTI_ECODE_XCEDE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_JIMDIMINFO_STR) == 0) return UNIFTI_ECODE_JIMDIMINFO;
    else if (strcmp(t_ecode, UNIFTI_ECODE_WORKFLOW_FWDS_STR) == 0) return UNIFTI_ECODE_WORKFLOW_FWDS;
    else if (strcmp(t_ecode, UNIFTI_ECODE_FREESURFER_STR) == 0) return UNIFTI_ECODE_FREESURFER;
    else if (strcmp(t_ecode, UNIFTI_ECODE_PYPICKLE_STR) == 0) return UNIFTI_ECODE_PYPICKLE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_MIND_IDENT_STR) == 0) return UNIFTI_ECODE_MIND_IDENT;
    else if (strcmp(t_ecode, UNIFTI_ECODE_B_VALUE_STR) == 0) return UNIFTI_ECODE_B_VALUE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_SPHERICAL_DIRECTION_STR) == 0) return UNIFTI_ECODE_SPHERICAL_DIRECTION;
    else if (strcmp(t_ecode, UNIFTI_ECODE_DT_COMPONENT_STR) == 0) return UNIFTI_ECODE_DT_COMPONENT;
    else if (strcmp(t_ecode, UNIFTI_ECODE_SHC_DEGREEORDER_STR) == 0) return UNIFTI_ECODE_SHC_DEGREEORDER;
    else if (strcmp(t_ecode, UNIFTI_ECODE_VOXBO_STR) == 0) return UNIFTI_ECODE_VOXBO;
    else if (strcmp(t_ecode, UNIFTI_ECODE_CARET_STR) == 0) return UNIFTI_ECODE_CARET;
    else if (strcmp(t_ecode, UNIFTI_ECODE_CIFTI_STR) == 0) return UNIFTI_ECODE_CIFTI;
    else if (strcmp(t_ecode, UNIFTI_ECODE_VARIABLE_FRAME_TIMING_STR) == 0) return UNIFTI_ECODE_VARIABLE_FRAME_TIMING;
    else if (strcmp(t_ecode, UNIFTI_ECODE_EVAL_STR) == 0) return UNIFTI_ECODE_EVAL;
    else if (strcmp(t_ecode, UNIFTI_ECODE_MATLAB_STR) == 0) return UNIFTI_ECODE_MATLAB;
    else if (strcmp(t_ecode, UNIFTI_ECODE_QUANTIPHYSE_STR) == 0) return UNIFTI_ECODE_QUANTIPHYSE;
    else if (strcmp(t_ecode, UNIFTI_ECODE_MRS_STR) == 0) return UNIFTI_ECODE_MRS;
  return -1;
}/* Datatype size */

/** @brief dt unknown size (bytes) */
#define UNIFTI_DT_UNKNOWN_SIZE 0
/** @brief dt binary size (bytes) */
#define UNIFTI_DT_BINARY_SIZE 0
/** @brief dt uint8 size (bytes) */
#define UNIFTI_DT_UINT8_SIZE 1
/** @brief dt int16 size (bytes) */
#define UNIFTI_DT_INT16_SIZE 2
/** @brief dt int32 size (bytes) */
#define UNIFTI_DT_INT32_SIZE 4
/** @brief dt float32 size (bytes) */
#define UNIFTI_DT_FLOAT32_SIZE 4
/** @brief dt complex64 size (bytes) */
#define UNIFTI_DT_COMPLEX64_SIZE 8
/** @brief dt float64 size (bytes) */
#define UNIFTI_DT_FLOAT64_SIZE 8
/** @brief dt rgb24 size (bytes) */
#define UNIFTI_DT_RGB24_SIZE 3
/** @brief dt int8 size (bytes) */
#define UNIFTI_DT_INT8_SIZE 1
/** @brief dt uint16 size (bytes) */
#define UNIFTI_DT_UINT16_SIZE 2
/** @brief dt uint32 size (bytes) */
#define UNIFTI_DT_UINT32_SIZE 4
/** @brief dt int64 size (bytes) */
#define UNIFTI_DT_INT64_SIZE 8
/** @brief dt uint64 size (bytes) */
#define UNIFTI_DT_UINT64_SIZE 8
/** @brief dt float128 size (bytes) */
#define UNIFTI_DT_FLOAT128_SIZE 16
/** @brief dt complex128 size (bytes) */
#define UNIFTI_DT_COMPLEX128_SIZE 16
/** @brief dt complex256 size (bytes) */
#define UNIFTI_DT_COMPLEX256_SIZE 32
/** @brief dt rgba32 size (bytes) */
#define UNIFTI_DT_RGBA32_SIZE 4

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Nifti headers /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

UNIFTI_STATIC_ASSERT(sizeof(unifti_n1_header_t) == 348, "nifti1 header size is not 348 bytes");
UNIFTI_STATIC_ASSERT(sizeof(unifti_n2_header_t) == 540, "nifti2 header size is not 540 bytes");

/* Computed header field frequency_dim */
static inline int32_t unifti_n1_header_frequency_dim(const unifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info & 3;
}
/* Computed header field phase_dim */
static inline int32_t unifti_n1_header_phase_dim(const unifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info >> 2 & 3;
}
/* Computed header field slice_dim */
static inline int32_t unifti_n1_header_slice_dim(const unifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info >> 4 & 3;
}
/* Computed header field spatial_units */
static inline int32_t unifti_n1_header_spatial_units(const unifti_n1_header_t *t_n1_header) {
  return t_n1_header->xyzt_units & 7;
}
/* Computed header field temporal_units */
static inline int32_t unifti_n1_header_temporal_units(const unifti_n1_header_t *t_n1_header) {
  return t_n1_header->xyzt_units & 56;
}
/* Computed header field frequency_dim */
static inline int32_t unifti_n2_header_frequency_dim(const unifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info & 3;
}
/* Computed header field phase_dim */
static inline int32_t unifti_n2_header_phase_dim(const unifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info >> 2 & 3;
}
/* Computed header field slice_dim */
static inline int32_t unifti_n2_header_slice_dim(const unifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info >> 4 & 3;
}
/* Computed header field spatial_units */
static inline int32_t unifti_n2_header_spatial_units(const unifti_n2_header_t *t_n2_header) {
  return t_n2_header->xyzt_units & 7;
}
/* Computed header field temporal_units */
static inline int32_t unifti_n2_header_temporal_units(const unifti_n2_header_t *t_n2_header) {
  return t_n2_header->xyzt_units & 56;
}
UNIFTI_STATIC_ASSERT(sizeof(unifti_extension_indicator_t) == 4, "extension header size is not 4 bytes");
UNIFTI_STATIC_ASSERT(sizeof(unifti_extension_header_t) == 8, "extension header size is not 8 bytes");
/** @brief Nifti header union */
typedef union unifti_header_t {
  unifti_n1_header_t n1_header;
    unifti_n2_header_t n2_header;
  } unifti_header_t;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Implementation ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/** @brief Get datatype size in bytes */
static inline int32_t unifti_dt_size(int32_t t_dt) {
  switch (t_dt) {
    case UNIFTI_DT_UNKNOWN: return UNIFTI_DT_UNKNOWN_SIZE;
    case UNIFTI_DT_BINARY: return UNIFTI_DT_BINARY_SIZE;
    case UNIFTI_DT_UINT8: return UNIFTI_DT_UINT8_SIZE;
    case UNIFTI_DT_INT16: return UNIFTI_DT_INT16_SIZE;
    case UNIFTI_DT_INT32: return UNIFTI_DT_INT32_SIZE;
    case UNIFTI_DT_FLOAT32: return UNIFTI_DT_FLOAT32_SIZE;
    case UNIFTI_DT_COMPLEX64: return UNIFTI_DT_COMPLEX64_SIZE;
    case UNIFTI_DT_FLOAT64: return UNIFTI_DT_FLOAT64_SIZE;
    case UNIFTI_DT_RGB24: return UNIFTI_DT_RGB24_SIZE;
    case UNIFTI_DT_INT8: return UNIFTI_DT_INT8_SIZE;
    case UNIFTI_DT_UINT16: return UNIFTI_DT_UINT16_SIZE;
    case UNIFTI_DT_UINT32: return UNIFTI_DT_UINT32_SIZE;
    case UNIFTI_DT_INT64: return UNIFTI_DT_INT64_SIZE;
    case UNIFTI_DT_UINT64: return UNIFTI_DT_UINT64_SIZE;
    case UNIFTI_DT_FLOAT128: return UNIFTI_DT_FLOAT128_SIZE;
    case UNIFTI_DT_COMPLEX128: return UNIFTI_DT_COMPLEX128_SIZE;
    case UNIFTI_DT_COMPLEX256: return UNIFTI_DT_COMPLEX256_SIZE;
    case UNIFTI_DT_RGBA32: return UNIFTI_DT_RGBA32_SIZE;
  default: return 0;
  }
}
/* Utility function for printing n1_header. */
static inline void unifti_n1_header_print(const unifti_n1_header_t *t_n1_header) {
  const char *intent_intent_code = unifti_intent_name(t_n1_header->intent_code);
  const char *dt_datatype = unifti_dt_name(t_n1_header->datatype);
  const char *slice_slice_code = unifti_slice_name(t_n1_header->slice_code);
  const char *xform_qform_code = unifti_xform_name(t_n1_header->qform_code);
  const char *xform_sform_code = unifti_xform_name(t_n1_header->sform_code);
  const char *units_spatial_units = unifti_units_name(unifti_n1_header_spatial_units(t_n1_header));
  const char *units_temporal_units = unifti_units_name(unifti_n1_header_temporal_units(t_n1_header));
    UNIFTI_PRINTF(
      "sizeof_hdr      : %i\n"
      "data_type       : '%.10s'\n"
      "db_name         : '%.18s'\n"
      "extents         : %i\n"
      "session_error   : %i\n"
      "regular         : %i\n"
      "dim_info        : %i\n"
      "dim             : [ %i, %i, %i, %i, %i, %i, %i, %i ]\n"
      "intent_p1       : %f\n"
      "intent_p2       : %f\n"
      "intent_p3       : %f\n"
      "intent_code     : %s (%i)\n"
      "datatype        : %s (%i)\n"
      "bitpix          : %i\n"
      "slice_start     : %i\n"
      "pixdim          : [ %f, %f, %f, %f, %f, %f, %f, %f ]\n"
      "vox_offset      : %f\n"
      "scl_slope       : %f\n"
      "scl_inter       : %f\n"
      "slice_end       : %i\n"
      "slice_code      : %s (%i)\n"
      "xyzt_units      : %i\n"
      "cal_max         : %f\n"
      "cal_min         : %f\n"
      "slice_duration  : %f\n"
      "toffset         : %f\n"
      "glmax           : %i\n"
      "glmin           : %i\n"
      "descrip         : '%.80s'\n"
      "aux_file        : '%.24s'\n"
      "qform_code      : %s (%i)\n"
      "sform_code      : %s (%i)\n"
      "quatern_b       : %f\n"
      "quatern_c       : %f\n"
      "quatern_d       : %f\n"
      "qoffset_x       : %f\n"
      "qoffset_y       : %f\n"
      "qoffset_z       : %f\n"
      "srow_x          : [ %f, %f, %f, %f ]\n"
      "srow_y          : [ %f, %f, %f, %f ]\n"
      "srow_z          : [ %f, %f, %f, %f ]\n"
      "intent_name     : '%.16s'\n"
      "magic           : '%.4s'\n"
      "*frequency_dim  : %i\n"
      "*phase_dim      : %i\n"
      "*slice_dim      : %i\n"
      "*spatial_units  : %s (%i)\n"
      "*temporal_units : %s (%i)\n"
      "",
      t_n1_header->sizeof_hdr,
      t_n1_header->data_type,
      t_n1_header->db_name,
      t_n1_header->extents,
      t_n1_header->session_error,
      t_n1_header->regular,
      t_n1_header->dim_info,
      t_n1_header->dim[0],
      t_n1_header->dim[1],
      t_n1_header->dim[2],
      t_n1_header->dim[3],
      t_n1_header->dim[4],
      t_n1_header->dim[5],
      t_n1_header->dim[6],
      t_n1_header->dim[7],
      t_n1_header->intent_p1,
      t_n1_header->intent_p2,
      t_n1_header->intent_p3,
      (intent_intent_code == NULL ? "<non standard>" : intent_intent_code),
      t_n1_header->intent_code,
      (dt_datatype == NULL ? "<non standard>" : dt_datatype),
      t_n1_header->datatype,
      t_n1_header->bitpix,
      t_n1_header->slice_start,
      t_n1_header->pixdim[0],
      t_n1_header->pixdim[1],
      t_n1_header->pixdim[2],
      t_n1_header->pixdim[3],
      t_n1_header->pixdim[4],
      t_n1_header->pixdim[5],
      t_n1_header->pixdim[6],
      t_n1_header->pixdim[7],
      t_n1_header->vox_offset,
      t_n1_header->scl_slope,
      t_n1_header->scl_inter,
      t_n1_header->slice_end,
      (slice_slice_code == NULL ? "<non standard>" : slice_slice_code),
      t_n1_header->slice_code,
      t_n1_header->xyzt_units,
      t_n1_header->cal_max,
      t_n1_header->cal_min,
      t_n1_header->slice_duration,
      t_n1_header->toffset,
      t_n1_header->glmax,
      t_n1_header->glmin,
      t_n1_header->descrip,
      t_n1_header->aux_file,
      (xform_qform_code == NULL ? "<non standard>" : xform_qform_code),
      t_n1_header->qform_code,
      (xform_sform_code == NULL ? "<non standard>" : xform_sform_code),
      t_n1_header->sform_code,
      t_n1_header->quatern_b,
      t_n1_header->quatern_c,
      t_n1_header->quatern_d,
      t_n1_header->qoffset_x,
      t_n1_header->qoffset_y,
      t_n1_header->qoffset_z,
      t_n1_header->srow_x[0],
      t_n1_header->srow_x[1],
      t_n1_header->srow_x[2],
      t_n1_header->srow_x[3],
      t_n1_header->srow_y[0],
      t_n1_header->srow_y[1],
      t_n1_header->srow_y[2],
      t_n1_header->srow_y[3],
      t_n1_header->srow_z[0],
      t_n1_header->srow_z[1],
      t_n1_header->srow_z[2],
      t_n1_header->srow_z[3],
      t_n1_header->intent_name,
      t_n1_header->magic,
      unifti_n1_header_frequency_dim(t_n1_header),
      unifti_n1_header_phase_dim(t_n1_header),
      unifti_n1_header_slice_dim(t_n1_header),
      (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
      unifti_n1_header_spatial_units(t_n1_header),
      (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
      unifti_n1_header_temporal_units(t_n1_header)
    );
}
/* Utility function for printing n2_header. */
static inline void unifti_n2_header_print(const unifti_n2_header_t *t_n2_header) {
  const char *dt_datatype = unifti_dt_name(t_n2_header->datatype);
  const char *xform_qform_code = unifti_xform_name(t_n2_header->qform_code);
  const char *xform_sform_code = unifti_xform_name(t_n2_header->sform_code);
  const char *slice_slice_code = unifti_slice_name(t_n2_header->slice_code);
  const char *intent_intent_code = unifti_intent_name(t_n2_header->intent_code);
  const char *units_spatial_units = unifti_units_name(unifti_n2_header_spatial_units(t_n2_header));
  const char *units_temporal_units = unifti_units_name(unifti_n2_header_temporal_units(t_n2_header));
    UNIFTI_PRINTF(
      "sizeof_hdr      : %i\n"
      "magic           : '%.4s'\n"
      "magic2          : [ %i, %i, %i, %i ]\n"
      "datatype        : %s (%i)\n"
      "bitpix          : %i\n"
      "dim             : [ %li, %li, %li, %li, %li, %li, %li, %li ]\n"
      "intent_p1       : %f\n"
      "intent_p2       : %f\n"
      "intent_p3       : %f\n"
      "pixdim          : [ %f, %f, %f, %f, %f, %f, %f, %f ]\n"
      "vox_offset      : %li\n"
      "scl_slope       : %f\n"
      "scl_inter       : %f\n"
      "cal_max         : %f\n"
      "cal_min         : %f\n"
      "slice_duration  : %f\n"
      "toffset         : %f\n"
      "slice_start     : %li\n"
      "slice_end       : %li\n"
      "descrip         : '%.80s'\n"
      "aux_file        : '%.24s'\n"
      "qform_code      : %s (%i)\n"
      "sform_code      : %s (%i)\n"
      "quatern_b       : %f\n"
      "quatern_c       : %f\n"
      "quatern_d       : %f\n"
      "qoffset_x       : %f\n"
      "qoffset_y       : %f\n"
      "qoffset_z       : %f\n"
      "srow_x          : [ %f, %f, %f, %f ]\n"
      "srow_y          : [ %f, %f, %f, %f ]\n"
      "srow_z          : [ %f, %f, %f, %f ]\n"
      "slice_code      : %s (%i)\n"
      "xyzt_units      : %i\n"
      "intent_code     : %s (%i)\n"
      "intent_name     : '%.16s'\n"
      "dim_info        : %i\n"
      "unused_str      : '%.15s'\n"
      "*frequency_dim  : %i\n"
      "*phase_dim      : %i\n"
      "*slice_dim      : %i\n"
      "*spatial_units  : %s (%i)\n"
      "*temporal_units : %s (%i)\n"
      "",
      t_n2_header->sizeof_hdr,
      t_n2_header->magic,
      t_n2_header->magic2[0],
      t_n2_header->magic2[1],
      t_n2_header->magic2[2],
      t_n2_header->magic2[3],
      (dt_datatype == NULL ? "<non standard>" : dt_datatype),
      t_n2_header->datatype,
      t_n2_header->bitpix,
      t_n2_header->dim[0],
      t_n2_header->dim[1],
      t_n2_header->dim[2],
      t_n2_header->dim[3],
      t_n2_header->dim[4],
      t_n2_header->dim[5],
      t_n2_header->dim[6],
      t_n2_header->dim[7],
      t_n2_header->intent_p1,
      t_n2_header->intent_p2,
      t_n2_header->intent_p3,
      t_n2_header->pixdim[0],
      t_n2_header->pixdim[1],
      t_n2_header->pixdim[2],
      t_n2_header->pixdim[3],
      t_n2_header->pixdim[4],
      t_n2_header->pixdim[5],
      t_n2_header->pixdim[6],
      t_n2_header->pixdim[7],
      t_n2_header->vox_offset,
      t_n2_header->scl_slope,
      t_n2_header->scl_inter,
      t_n2_header->cal_max,
      t_n2_header->cal_min,
      t_n2_header->slice_duration,
      t_n2_header->toffset,
      t_n2_header->slice_start,
      t_n2_header->slice_end,
      t_n2_header->descrip,
      t_n2_header->aux_file,
      (xform_qform_code == NULL ? "<non standard>" : xform_qform_code),
      t_n2_header->qform_code,
      (xform_sform_code == NULL ? "<non standard>" : xform_sform_code),
      t_n2_header->sform_code,
      t_n2_header->quatern_b,
      t_n2_header->quatern_c,
      t_n2_header->quatern_d,
      t_n2_header->qoffset_x,
      t_n2_header->qoffset_y,
      t_n2_header->qoffset_z,
      t_n2_header->srow_x[0],
      t_n2_header->srow_x[1],
      t_n2_header->srow_x[2],
      t_n2_header->srow_x[3],
      t_n2_header->srow_y[0],
      t_n2_header->srow_y[1],
      t_n2_header->srow_y[2],
      t_n2_header->srow_y[3],
      t_n2_header->srow_z[0],
      t_n2_header->srow_z[1],
      t_n2_header->srow_z[2],
      t_n2_header->srow_z[3],
      (slice_slice_code == NULL ? "<non standard>" : slice_slice_code),
      t_n2_header->slice_code,
      t_n2_header->xyzt_units,
      (intent_intent_code == NULL ? "<non standard>" : intent_intent_code),
      t_n2_header->intent_code,
      t_n2_header->intent_name,
      t_n2_header->dim_info,
      t_n2_header->unused_str,
      unifti_n2_header_frequency_dim(t_n2_header),
      unifti_n2_header_phase_dim(t_n2_header),
      unifti_n2_header_slice_dim(t_n2_header),
      (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
      unifti_n2_header_spatial_units(t_n2_header),
      (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
      unifti_n2_header_temporal_units(t_n2_header)
    );
}
#define UNIFTI_PEEK_NIFTI2 1
#define UNIFTI_PEEK_SWAP 2
/**
 * @brief Peek at first 4 bytes of header to determine nifti version and endianness.
 * Return value can be bit compared with UNIFTI_PEEK_* values.
 * If return value is -1 this is not a nifti header.
 */
static inline int32_t unifti_peek(const uint32_t t_header_start) {
  switch (t_header_start) {
  case 348: return 0;
  case 1543569408: return UNIFTI_PEEK_SWAP;
  case 540: return UNIFTI_PEEK_NIFTI2;
  case 469893120: return UNIFTI_PEEK_NIFTI2 & UNIFTI_PEEK_SWAP;
  default: return -1;
  }
}
/* Utility function for byte swapping n1_header. */
static inline void unifti_n1_header_swap(unifti_n1_header_t *t_n1_header) {
  t_n1_header->sizeof_hdr = bswap32(t_n1_header->sizeof_hdr);
  t_n1_header->extents = bswap32(t_n1_header->extents);
  t_n1_header->session_error = bswap16(t_n1_header->session_error);  
    for (int i = 0; i < 8; ++i) {
      t_n1_header->dim[i] = bswap16(t_n1_header->dim[i]);
    }
  t_n1_header->intent_p1 = bswap32(t_n1_header->intent_p1);
  t_n1_header->intent_p2 = bswap32(t_n1_header->intent_p2);
  t_n1_header->intent_p3 = bswap32(t_n1_header->intent_p3);
  t_n1_header->intent_code = bswap16(t_n1_header->intent_code);
  t_n1_header->datatype = bswap16(t_n1_header->datatype);
  t_n1_header->bitpix = bswap16(t_n1_header->bitpix);
  t_n1_header->slice_start = bswap16(t_n1_header->slice_start);  
    for (int i = 0; i < 8; ++i) {
      t_n1_header->pixdim[i] = bswap32(t_n1_header->pixdim[i]);
    }
  t_n1_header->vox_offset = bswap32(t_n1_header->vox_offset);
  t_n1_header->scl_slope = bswap32(t_n1_header->scl_slope);
  t_n1_header->scl_inter = bswap32(t_n1_header->scl_inter);
  t_n1_header->slice_end = bswap16(t_n1_header->slice_end);
  t_n1_header->cal_max = bswap32(t_n1_header->cal_max);
  t_n1_header->cal_min = bswap32(t_n1_header->cal_min);
  t_n1_header->slice_duration = bswap32(t_n1_header->slice_duration);
  t_n1_header->toffset = bswap32(t_n1_header->toffset);
  t_n1_header->glmax = bswap32(t_n1_header->glmax);
  t_n1_header->glmin = bswap32(t_n1_header->glmin);
  t_n1_header->qform_code = bswap16(t_n1_header->qform_code);
  t_n1_header->sform_code = bswap16(t_n1_header->sform_code);
  t_n1_header->quatern_b = bswap32(t_n1_header->quatern_b);
  t_n1_header->quatern_c = bswap32(t_n1_header->quatern_c);
  t_n1_header->quatern_d = bswap32(t_n1_header->quatern_d);
  t_n1_header->qoffset_x = bswap32(t_n1_header->qoffset_x);
  t_n1_header->qoffset_y = bswap32(t_n1_header->qoffset_y);
  t_n1_header->qoffset_z = bswap32(t_n1_header->qoffset_z);  
    for (int i = 0; i < 4; ++i) {
      t_n1_header->srow_x[i] = bswap32(t_n1_header->srow_x[i]);
    }  
    for (int i = 0; i < 4; ++i) {
      t_n1_header->srow_y[i] = bswap32(t_n1_header->srow_y[i]);
    }  
    for (int i = 0; i < 4; ++i) {
      t_n1_header->srow_z[i] = bswap32(t_n1_header->srow_z[i]);
    }
}
/* Utility function for byte swapping n2_header. */
static inline void unifti_n2_header_swap(unifti_n2_header_t *t_n2_header) {
  t_n2_header->sizeof_hdr = bswap32(t_n2_header->sizeof_hdr);
  t_n2_header->datatype = bswap16(t_n2_header->datatype);
  t_n2_header->bitpix = bswap16(t_n2_header->bitpix);  
    for (int i = 0; i < 8; ++i) {
      t_n2_header->dim[i] = bswap64(t_n2_header->dim[i]);
    }
  t_n2_header->intent_p1 = bswap64(t_n2_header->intent_p1);
  t_n2_header->intent_p2 = bswap64(t_n2_header->intent_p2);
  t_n2_header->intent_p3 = bswap64(t_n2_header->intent_p3);  
    for (int i = 0; i < 8; ++i) {
      t_n2_header->pixdim[i] = bswap64(t_n2_header->pixdim[i]);
    }
  t_n2_header->vox_offset = bswap64(t_n2_header->vox_offset);
  t_n2_header->scl_slope = bswap64(t_n2_header->scl_slope);
  t_n2_header->scl_inter = bswap64(t_n2_header->scl_inter);
  t_n2_header->cal_max = bswap64(t_n2_header->cal_max);
  t_n2_header->cal_min = bswap64(t_n2_header->cal_min);
  t_n2_header->slice_duration = bswap64(t_n2_header->slice_duration);
  t_n2_header->toffset = bswap64(t_n2_header->toffset);
  t_n2_header->slice_start = bswap64(t_n2_header->slice_start);
  t_n2_header->slice_end = bswap64(t_n2_header->slice_end);
  t_n2_header->qform_code = bswap32(t_n2_header->qform_code);
  t_n2_header->sform_code = bswap32(t_n2_header->sform_code);
  t_n2_header->quatern_b = bswap64(t_n2_header->quatern_b);
  t_n2_header->quatern_c = bswap64(t_n2_header->quatern_c);
  t_n2_header->quatern_d = bswap64(t_n2_header->quatern_d);
  t_n2_header->qoffset_x = bswap64(t_n2_header->qoffset_x);
  t_n2_header->qoffset_y = bswap64(t_n2_header->qoffset_y);
  t_n2_header->qoffset_z = bswap64(t_n2_header->qoffset_z);  
    for (int i = 0; i < 4; ++i) {
      t_n2_header->srow_x[i] = bswap64(t_n2_header->srow_x[i]);
    }  
    for (int i = 0; i < 4; ++i) {
      t_n2_header->srow_y[i] = bswap64(t_n2_header->srow_y[i]);
    }  
    for (int i = 0; i < 4; ++i) {
      t_n2_header->srow_z[i] = bswap64(t_n2_header->srow_z[i]);
    }
  t_n2_header->slice_code = bswap32(t_n2_header->slice_code);
  t_n2_header->xyzt_units = bswap32(t_n2_header->xyzt_units);
  t_n2_header->intent_code = bswap32(t_n2_header->intent_code);
}
/** @brief Calculate n1_header data array size (in bytes). */
static inline int64_t unifti_n1_header_array_size(const unifti_n1_header_t *t_n1_header) {
  int64_t size = t_n1_header->bitpix / 8;
  for (int i = 0; i < t_n1_header->dim[0]; ++i) { size *= t_n1_header->dim[i+1]; }
  return size;
}
/** @brief Calculate n2_header data array size (in bytes). */
static inline int64_t unifti_n2_header_array_size(const unifti_n2_header_t *t_n2_header) {
  int64_t size = t_n2_header->bitpix / 8;
  for (int i = 0; i < t_n2_header->dim[0]; ++i) { size *= t_n2_header->dim[i+1]; }
  return size;
}
/** @brief Convert n1_header to n2_header. */
static inline int32_t unifti_n1_header_to_n2_header(const unifti_n1_header_t *t_n1_header, unifti_n2_header_t *t_n2_header) {
  t_n2_header->sizeof_hdr = 540;
  memcpy(&t_n2_header->magic, "n+2\0", 4);
  const int8_t magic2[4] = { 0x0D, 0x0A, 0x1A, 0x0A };
  memcpy(&t_n2_header->magic2, magic2, 4);
  for (int i = 0; i < 15; ++i) { t_n2_header->unused_str[i] = 0; }
  t_n2_header->dim_info = t_n1_header->dim_info;
  for (int i = 0; i < 8; ++i) { t_n2_header->dim[i] = (int64_t) t_n1_header->dim[i]; }
  t_n2_header->intent_p1 = (double) t_n1_header->intent_p1;
  t_n2_header->intent_p2 = (double) t_n1_header->intent_p2;
  t_n2_header->intent_p3 = (double) t_n1_header->intent_p3;
  t_n2_header->intent_code = (int32_t) t_n1_header->intent_code;
  t_n2_header->datatype = t_n1_header->datatype;
  t_n2_header->bitpix = t_n1_header->bitpix;
  t_n2_header->slice_start = (int64_t) t_n1_header->slice_start;
  for (int i = 0; i < 8; ++i) { t_n2_header->pixdim[i] = (double) t_n1_header->pixdim[i]; }
  t_n2_header->vox_offset = (int64_t) t_n1_header->vox_offset;
  t_n2_header->scl_slope = (double) t_n1_header->scl_slope;
  t_n2_header->scl_inter = (double) t_n1_header->scl_inter;
  t_n2_header->slice_end = (int64_t) t_n1_header->slice_end;
  t_n2_header->slice_code = (int32_t) t_n1_header->slice_code;
  t_n2_header->xyzt_units = (int32_t) t_n1_header->xyzt_units;
  t_n2_header->cal_max = (double) t_n1_header->cal_max;
  t_n2_header->cal_min = (double) t_n1_header->cal_min;
  t_n2_header->slice_duration = (double) t_n1_header->slice_duration;
  t_n2_header->toffset = (double) t_n1_header->toffset;
  memcpy(t_n2_header->descrip, t_n1_header->descrip, 80);
  memcpy(t_n2_header->aux_file, t_n1_header->aux_file, 24);
  t_n2_header->qform_code = (int32_t) t_n1_header->qform_code;
  t_n2_header->sform_code = (int32_t) t_n1_header->sform_code;
  t_n2_header->quatern_b = (double) t_n1_header->quatern_b;
  t_n2_header->quatern_c = (double) t_n1_header->quatern_c;
  t_n2_header->quatern_d = (double) t_n1_header->quatern_d;
  t_n2_header->qoffset_x = (double) t_n1_header->qoffset_x;
  t_n2_header->qoffset_y = (double) t_n1_header->qoffset_y;
  t_n2_header->qoffset_z = (double) t_n1_header->qoffset_z;
  for (int i = 0; i < 4; ++i) { t_n2_header->srow_x[i] = (double) t_n1_header->srow_x[i]; }
  for (int i = 0; i < 4; ++i) { t_n2_header->srow_y[i] = (double) t_n1_header->srow_y[i]; }
  for (int i = 0; i < 4; ++i) { t_n2_header->srow_z[i] = (double) t_n1_header->srow_z[i]; }
  memcpy(t_n2_header->intent_name, t_n1_header->intent_name, 16);
  return 1;
}
/** @brief Convert n2_header to n1_header. */
static inline int32_t unifti_n2_header_to_n1_header(const unifti_n2_header_t *t_n2_header, unifti_n1_header_t *t_n1_header) {
  for (int i = 1; i < 8; ++i) { if (t_n2_header->dim[i] > INT_MAX) return 0; }
  t_n1_header->sizeof_hdr = 348;
  memcpy(&t_n1_header->magic, "n+1\0", 4);
  for (int i = 0; i < 36; ++i) { ((char *) &t_n1_header->data_type)[i] = 0; }
  t_n1_header->datatype = t_n2_header->datatype;
  t_n1_header->bitpix = t_n2_header->bitpix;
  for (int i = 0; i < 8; ++i) { t_n1_header->dim[i] = (int16_t) t_n2_header->dim[i]; }
  t_n1_header->intent_p1 = (float) t_n2_header->intent_p1;
  t_n1_header->intent_p2 = (float) t_n2_header->intent_p2;
  t_n1_header->intent_p3 = (float) t_n2_header->intent_p3;
  for (int i = 0; i < 8; ++i) { t_n1_header->pixdim[i] = (float) t_n2_header->pixdim[i]; }
  t_n1_header->vox_offset = (float) t_n2_header->vox_offset;
  t_n1_header->scl_slope = (float) t_n2_header->scl_slope;
  t_n1_header->scl_inter = (float) t_n2_header->scl_inter;
  t_n1_header->cal_max = (float) t_n2_header->cal_max;
  t_n1_header->cal_min = (float) t_n2_header->cal_min;
  t_n1_header->slice_duration = (float) t_n2_header->slice_duration;
  t_n1_header->toffset = (float) t_n2_header->toffset;
  t_n1_header->slice_start = (int16_t) t_n2_header->slice_start;
  t_n1_header->slice_end = (int16_t) t_n2_header->slice_end;
  memcpy(t_n1_header->descrip, t_n2_header->descrip, 80);
  memcpy(t_n1_header->aux_file, t_n2_header->aux_file, 24);
  t_n1_header->qform_code = (int16_t) t_n2_header->qform_code;
  t_n1_header->sform_code = (int16_t) t_n2_header->sform_code;
  t_n1_header->quatern_b = (float) t_n2_header->quatern_b;
  t_n1_header->quatern_c = (float) t_n2_header->quatern_c;
  t_n1_header->quatern_d = (float) t_n2_header->quatern_d;
  t_n1_header->qoffset_x = (float) t_n2_header->qoffset_x;
  t_n1_header->qoffset_y = (float) t_n2_header->qoffset_y;
  t_n1_header->qoffset_z = (float) t_n2_header->qoffset_z;
  for (int i = 0; i < 4; ++i) { t_n1_header->srow_x[i] = (float) t_n2_header->srow_x[i]; }
  for (int i = 0; i < 4; ++i) { t_n1_header->srow_y[i] = (float) t_n2_header->srow_y[i]; }
  for (int i = 0; i < 4; ++i) { t_n1_header->srow_z[i] = (float) t_n2_header->srow_z[i]; }
  t_n1_header->slice_code = (int8_t) t_n2_header->slice_code;
  t_n1_header->xyzt_units = (int8_t) t_n2_header->xyzt_units;
  t_n1_header->intent_code = (int16_t) t_n2_header->intent_code;
  memcpy(t_n1_header->intent_name, t_n2_header->intent_name, 16);
  t_n1_header->dim_info = t_n2_header->dim_info;
  return 1;
}



#ifdef __cplusplus
}
#endif

#endif /* UNIFTI_unifti_HEADER_H */