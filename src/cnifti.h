/** @file cnifti.h */
               
#ifndef CNIFTI_cnifti_HEADER_H
#define CNIFTI_cnifti_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define CNIFTI_STATIC_ASSERT(COND,MSG) static_assert(COND,MSG)
#else
#define CNIFTI_STATIC_ASSERT(COND,MSG)
#endif

#ifndef CNIFTI_PRINTF
#include <stdio.h>
#define CNIFTI_PRINTF printf
#endif

#include <stddef.h> // NULL, size_t
#include <stdint.h> // int32_t, uint32_t, int64_t, uint64_t
#include <stdbool.h> // bool
#include <string.h> // memcpy, strcmp
typedef struct {
  /** Must be 348. */
  int32_t sizeof_hdr;
  /** Unused. */
  char data_type[10];
  /** Unused. */
  char db_name[18];
  /** Unused. */
  int32_t extents;
  /** Unused. */
  int16_t session_error;
  /** Unused. */
  int8_t regular;
  /** MRI slice ordering. */
  int8_t dim_info;
  /** Data array dimensions. */
  int16_t dim[8];
  /** 1st intent parameter. */
  float intent_p1;
  /** 2nd intent parameter. */
  float intent_p2;
  /** 3rd intent parameter. */
  float intent_p3;
  /** NIFTI_INTENT_* code. (enum: CNIFTI_INTENT_*) */
  int16_t intent_code;
  /** Defines data type. (enum: CNIFTI_DT_*) */
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
  /** Slice timing order. (enum: CNIFTI_SLICE_*) */
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
  /** NIFTI_XFORM_* code. (enum: CNIFTI_XFORM_*) */
  int16_t qform_code;
  /** NIFTI_XFORM_* code. (enum: CNIFTI_XFORM_*) */
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
  char magic[4]
} cnifti_n1_header_t;
#pragma pack(push, 1)
typedef struct {
  /** Must be 540. */
  int32_t sizeof_hdr;
  /** MUST be 'ni2\0' or 'n+2\0'. */
  char magic[4];
  /** MUST be 0D 0A 1A 0A. */
  int8_t magic2[4];
  /** Defines data type. (enum: CNIFTI_DT_*) */
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
  /** NIFTI_XFORM_* code. (enum: CNIFTI_XFORM_*) */
  int32_t qform_code;
  /** NIFTI_XFORM_* code. (enum: CNIFTI_XFORM_*) */
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
  /** Slice timing order. (enum: CNIFTI_SLICE_*) */
  int32_t slice_code;
  /** Units of pixdim[1..4] */
  int32_t xyzt_units;
  /** NIFTI_INTENT_* code. (enum: CNIFTI_INTENT_*) */
  int32_t intent_code;
  /** 'name' or meaning of data. */
  char intent_name[16];
  /** MRI slice ordering. */
  int8_t dim_info;
  /** unused, filled with \0 */
  char unused_str[15]
} cnifti_n2_header_t;
#pragma pack(pop)
typedef struct {
  /**  */
  int8_t has_extension;
  /**  */
  uint8_t padding
} cnifti_extension_indicator_t;
typedef struct {
  /**  */
  int32_t esize;
  /**  */
  int32_t ecode
} cnifti_extension_header_t;


/** @brief version */
#define CNIFTI_VERSION 1//// Enum dt ////
/** @brief unknown::unknown */
#define CNIFTI_UNKNOWN_0 0
/** @brief binary::binary */
#define CNIFTI_BINARY_1 1
/** @brief uint8::uint8 */
#define CNIFTI_UINT8_2 2
/** @brief int16::int16 */
#define CNIFTI_INT16_4 4
/** @brief int32::int32 */
#define CNIFTI_INT32_8 8
/** @brief float32::float32 */
#define CNIFTI_FLOAT32_16 16
/** @brief complex64::complex64 */
#define CNIFTI_COMPLEX64_32 32
/** @brief float64::float64 */
#define CNIFTI_FLOAT64_64 64
/** @brief rgb24::rgb24 */
#define CNIFTI_RGB24_128 128
/** @brief int8::int8 */
#define CNIFTI_INT8_256 256
/** @brief unit16::unit16 */
#define CNIFTI_UNIT16_512 512
/** @brief uint32::uint32 */
#define CNIFTI_UINT32_768 768
/** @brief int64::int64 */
#define CNIFTI_INT64_1024 1024
/** @brief uint64::uint64 */
#define CNIFTI_UINT64_1280 1280
/** @brief float128::float128 */
#define CNIFTI_FLOAT128_1536 1536
/** @brief complex128::complex128 */
#define CNIFTI_COMPLEX128_1792 1792
/** @brief complex256::complex256 */
#define CNIFTI_COMPLEX256_2048 2048
/** @brief rgba32::rgba32 */
#define CNIFTI_RGBA32_2304 2304
/** @brief unknown::unknown name string */
#define CNIFTI_UNKNOWN_0_STR "unknown"
/** @brief binary::binary name string */
#define CNIFTI_BINARY_1_STR "binary"
/** @brief uint8::uint8 name string */
#define CNIFTI_UINT8_2_STR "uint8"
/** @brief int16::int16 name string */
#define CNIFTI_INT16_4_STR "int16"
/** @brief int32::int32 name string */
#define CNIFTI_INT32_8_STR "int32"
/** @brief float32::float32 name string */
#define CNIFTI_FLOAT32_16_STR "float32"
/** @brief complex64::complex64 name string */
#define CNIFTI_COMPLEX64_32_STR "complex64"
/** @brief float64::float64 name string */
#define CNIFTI_FLOAT64_64_STR "float64"
/** @brief rgb24::rgb24 name string */
#define CNIFTI_RGB24_128_STR "rgb24"
/** @brief int8::int8 name string */
#define CNIFTI_INT8_256_STR "int8"
/** @brief unit16::unit16 name string */
#define CNIFTI_UNIT16_512_STR "unit16"
/** @brief uint32::uint32 name string */
#define CNIFTI_UINT32_768_STR "uint32"
/** @brief int64::int64 name string */
#define CNIFTI_INT64_1024_STR "int64"
/** @brief uint64::uint64 name string */
#define CNIFTI_UINT64_1280_STR "uint64"
/** @brief float128::float128 name string */
#define CNIFTI_FLOAT128_1536_STR "float128"
/** @brief complex128::complex128 name string */
#define CNIFTI_COMPLEX128_1792_STR "complex128"
/** @brief complex256::complex256 name string */
#define CNIFTI_COMPLEX256_2048_STR "complex256"
/** @brief rgba32::rgba32 name string */
#define CNIFTI_RGBA32_2304_STR "rgba32"

/* Returns the name of the dt value. */
static inline const char *cnifti_dt_name(const int32_t value) {
  switch (value) {
    case CNIFTI_UNKNOWN_0: return CNIFTI_UNKNOWN_0_STR;
    case CNIFTI_BINARY_1: return CNIFTI_BINARY_1_STR;
    case CNIFTI_UINT8_2: return CNIFTI_UINT8_2_STR;
    case CNIFTI_INT16_4: return CNIFTI_INT16_4_STR;
    case CNIFTI_INT32_8: return CNIFTI_INT32_8_STR;
    case CNIFTI_FLOAT32_16: return CNIFTI_FLOAT32_16_STR;
    case CNIFTI_COMPLEX64_32: return CNIFTI_COMPLEX64_32_STR;
    case CNIFTI_FLOAT64_64: return CNIFTI_FLOAT64_64_STR;
    case CNIFTI_RGB24_128: return CNIFTI_RGB24_128_STR;
    case CNIFTI_INT8_256: return CNIFTI_INT8_256_STR;
    case CNIFTI_UNIT16_512: return CNIFTI_UNIT16_512_STR;
    case CNIFTI_UINT32_768: return CNIFTI_UINT32_768_STR;
    case CNIFTI_INT64_1024: return CNIFTI_INT64_1024_STR;
    case CNIFTI_UINT64_1280: return CNIFTI_UINT64_1280_STR;
    case CNIFTI_FLOAT128_1536: return CNIFTI_FLOAT128_1536_STR;
    case CNIFTI_COMPLEX128_1792: return CNIFTI_COMPLEX128_1792_STR;
    case CNIFTI_COMPLEX256_2048: return CNIFTI_COMPLEX256_2048_STR;
    case CNIFTI_RGBA32_2304: return CNIFTI_RGBA32_2304_STR;
  default: return NULL;
  }
}
/* Returns the dt value from its name. */
static inline int32_t cnifti_dt_from_name(const char *t_dt) {
  if (t_dt == NULL) return -1;
  if (strcmp(t_dt, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_dt, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_dt, CNIFTI_BINARY_1_STR) == 0) return CNIFTI_BINARY_1;
    else if (strcmp(t_dt, CNIFTI_UINT8_2_STR) == 0) return CNIFTI_UINT8_2;
    else if (strcmp(t_dt, CNIFTI_INT16_4_STR) == 0) return CNIFTI_INT16_4;
    else if (strcmp(t_dt, CNIFTI_INT32_8_STR) == 0) return CNIFTI_INT32_8;
    else if (strcmp(t_dt, CNIFTI_FLOAT32_16_STR) == 0) return CNIFTI_FLOAT32_16;
    else if (strcmp(t_dt, CNIFTI_COMPLEX64_32_STR) == 0) return CNIFTI_COMPLEX64_32;
    else if (strcmp(t_dt, CNIFTI_FLOAT64_64_STR) == 0) return CNIFTI_FLOAT64_64;
    else if (strcmp(t_dt, CNIFTI_RGB24_128_STR) == 0) return CNIFTI_RGB24_128;
    else if (strcmp(t_dt, CNIFTI_INT8_256_STR) == 0) return CNIFTI_INT8_256;
    else if (strcmp(t_dt, CNIFTI_UNIT16_512_STR) == 0) return CNIFTI_UNIT16_512;
    else if (strcmp(t_dt, CNIFTI_UINT32_768_STR) == 0) return CNIFTI_UINT32_768;
    else if (strcmp(t_dt, CNIFTI_INT64_1024_STR) == 0) return CNIFTI_INT64_1024;
    else if (strcmp(t_dt, CNIFTI_UINT64_1280_STR) == 0) return CNIFTI_UINT64_1280;
    else if (strcmp(t_dt, CNIFTI_FLOAT128_1536_STR) == 0) return CNIFTI_FLOAT128_1536;
    else if (strcmp(t_dt, CNIFTI_COMPLEX128_1792_STR) == 0) return CNIFTI_COMPLEX128_1792;
    else if (strcmp(t_dt, CNIFTI_COMPLEX256_2048_STR) == 0) return CNIFTI_COMPLEX256_2048;
    else if (strcmp(t_dt, CNIFTI_RGBA32_2304_STR) == 0) return CNIFTI_RGBA32_2304;
  return -1;
}//// Enum intent ////
/** @brief none::none */
#define CNIFTI_NONE_0 0
/** @brief correl::correl */
#define CNIFTI_CORREL_2 2
/** @brief ttest::ttest */
#define CNIFTI_TTEST_3 3
/** @brief ftest::ftest */
#define CNIFTI_FTEST_4 4
/** @brief zscore::zscore */
#define CNIFTI_ZSCORE_5 5
/** @brief chisq::chisq */
#define CNIFTI_CHISQ_6 6
/** @brief beta::beta */
#define CNIFTI_BETA_7 7
/** @brief binom::binom */
#define CNIFTI_BINOM_8 8
/** @brief gamma::gamma */
#define CNIFTI_GAMMA_9 9
/** @brief poisson::poisson */
#define CNIFTI_POISSON_10 10
/** @brief normal::normal */
#define CNIFTI_NORMAL_11 11
/** @brief ftest_nonc::ftest_nonc */
#define CNIFTI_FTEST_NONC_12 12
/** @brief chisq_nonc::chisq_nonc */
#define CNIFTI_CHISQ_NONC_13 13
/** @brief logistic::logistic */
#define CNIFTI_LOGISTIC_14 14
/** @brief laplace::laplace */
#define CNIFTI_LAPLACE_15 15
/** @brief uniform::uniform */
#define CNIFTI_UNIFORM_16 16
/** @brief ttest_nonc::ttest_nonc */
#define CNIFTI_TTEST_NONC_17 17
/** @brief weibull::weibull */
#define CNIFTI_WEIBULL_18 18
/** @brief chi::chi */
#define CNIFTI_CHI_19 19
/** @brief invgauss::invgauss */
#define CNIFTI_INVGAUSS_20 20
/** @brief extval::extval */
#define CNIFTI_EXTVAL_21 21
/** @brief pval::pval */
#define CNIFTI_PVAL_22 22
/** @brief logpval::logpval */
#define CNIFTI_LOGPVAL_23 23
/** @brief log10pval::log10pval */
#define CNIFTI_LOG10PVAL_24 24
/** @brief estimate::estimate */
#define CNIFTI_ESTIMATE_1001 1001
/** @brief label::label */
#define CNIFTI_LABEL_1002 1002
/** @brief neuroname::neuroname */
#define CNIFTI_NEURONAME_1003 1003
/** @brief genmatrix::genmatrix */
#define CNIFTI_GENMATRIX_1004 1004
/** @brief symmatrix::symmatrix */
#define CNIFTI_SYMMATRIX_1005 1005
/** @brief dispvect::dispvect */
#define CNIFTI_DISPVECT_1006 1006
/** @brief vector::vector */
#define CNIFTI_VECTOR_1007 1007
/** @brief pointset::pointset */
#define CNIFTI_POINTSET_1008 1008
/** @brief triangle::triangle */
#define CNIFTI_TRIANGLE_1009 1009
/** @brief quaternion::quaternion */
#define CNIFTI_QUATERNION_1010 1010
/** @brief dimless::dimless */
#define CNIFTI_DIMLESS_1011 1011
/** @brief time_series::time_series */
#define CNIFTI_TIME_SERIES_2001 2001
/** @brief node_index::node_index */
#define CNIFTI_NODE_INDEX_2002 2002
/** @brief rgb_vector::rgb_vector */
#define CNIFTI_RGB_VECTOR_2003 2003
/** @brief rgba_vector::rgba_vector */
#define CNIFTI_RGBA_VECTOR_2004 2004
/** @brief shape::shape */
#define CNIFTI_SHAPE_2005 2005
/** @brief fsl_fnirt_displacement_field::fsl_fnirt_displacement_field */
#define CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006 2006
/** @brief fsl_cubic_spline_coefficients::fsl_cubic_spline_coefficients */
#define CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007 2007
/** @brief fsl_dct_coefficients::fsl_dct_coefficients */
#define CNIFTI_FSL_DCT_COEFFICIENTS_2008 2008
/** @brief fsl_quadratic_spline_coefficients::fsl_quadratic_spline_coefficients */
#define CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009 2009
/** @brief fsl_topup_cubic_spline_coefficients::fsl_topup_cubic_spline_coefficients */
#define CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016 2016
/** @brief fsl_topup_quadratic_spline_coefficients::fsl_topup_quadratic_spline_coefficients */
#define CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017 2017
/** @brief fsl_topup_field::fsl_topup_field */
#define CNIFTI_FSL_TOPUP_FIELD_2018 2018
/** @brief none::none name string */
#define CNIFTI_NONE_0_STR "none"
/** @brief correl::correl name string */
#define CNIFTI_CORREL_2_STR "correl"
/** @brief ttest::ttest name string */
#define CNIFTI_TTEST_3_STR "ttest"
/** @brief ftest::ftest name string */
#define CNIFTI_FTEST_4_STR "ftest"
/** @brief zscore::zscore name string */
#define CNIFTI_ZSCORE_5_STR "zscore"
/** @brief chisq::chisq name string */
#define CNIFTI_CHISQ_6_STR "chisq"
/** @brief beta::beta name string */
#define CNIFTI_BETA_7_STR "beta"
/** @brief binom::binom name string */
#define CNIFTI_BINOM_8_STR "binom"
/** @brief gamma::gamma name string */
#define CNIFTI_GAMMA_9_STR "gamma"
/** @brief poisson::poisson name string */
#define CNIFTI_POISSON_10_STR "poisson"
/** @brief normal::normal name string */
#define CNIFTI_NORMAL_11_STR "normal"
/** @brief ftest_nonc::ftest_nonc name string */
#define CNIFTI_FTEST_NONC_12_STR "ftest_nonc"
/** @brief chisq_nonc::chisq_nonc name string */
#define CNIFTI_CHISQ_NONC_13_STR "chisq_nonc"
/** @brief logistic::logistic name string */
#define CNIFTI_LOGISTIC_14_STR "logistic"
/** @brief laplace::laplace name string */
#define CNIFTI_LAPLACE_15_STR "laplace"
/** @brief uniform::uniform name string */
#define CNIFTI_UNIFORM_16_STR "uniform"
/** @brief ttest_nonc::ttest_nonc name string */
#define CNIFTI_TTEST_NONC_17_STR "ttest_nonc"
/** @brief weibull::weibull name string */
#define CNIFTI_WEIBULL_18_STR "weibull"
/** @brief chi::chi name string */
#define CNIFTI_CHI_19_STR "chi"
/** @brief invgauss::invgauss name string */
#define CNIFTI_INVGAUSS_20_STR "invgauss"
/** @brief extval::extval name string */
#define CNIFTI_EXTVAL_21_STR "extval"
/** @brief pval::pval name string */
#define CNIFTI_PVAL_22_STR "pval"
/** @brief logpval::logpval name string */
#define CNIFTI_LOGPVAL_23_STR "logpval"
/** @brief log10pval::log10pval name string */
#define CNIFTI_LOG10PVAL_24_STR "log10pval"
/** @brief estimate::estimate name string */
#define CNIFTI_ESTIMATE_1001_STR "estimate"
/** @brief label::label name string */
#define CNIFTI_LABEL_1002_STR "label"
/** @brief neuroname::neuroname name string */
#define CNIFTI_NEURONAME_1003_STR "neuroname"
/** @brief genmatrix::genmatrix name string */
#define CNIFTI_GENMATRIX_1004_STR "genmatrix"
/** @brief symmatrix::symmatrix name string */
#define CNIFTI_SYMMATRIX_1005_STR "symmatrix"
/** @brief dispvect::dispvect name string */
#define CNIFTI_DISPVECT_1006_STR "dispvect"
/** @brief vector::vector name string */
#define CNIFTI_VECTOR_1007_STR "vector"
/** @brief pointset::pointset name string */
#define CNIFTI_POINTSET_1008_STR "pointset"
/** @brief triangle::triangle name string */
#define CNIFTI_TRIANGLE_1009_STR "triangle"
/** @brief quaternion::quaternion name string */
#define CNIFTI_QUATERNION_1010_STR "quaternion"
/** @brief dimless::dimless name string */
#define CNIFTI_DIMLESS_1011_STR "dimless"
/** @brief time_series::time_series name string */
#define CNIFTI_TIME_SERIES_2001_STR "time_series"
/** @brief node_index::node_index name string */
#define CNIFTI_NODE_INDEX_2002_STR "node_index"
/** @brief rgb_vector::rgb_vector name string */
#define CNIFTI_RGB_VECTOR_2003_STR "rgb_vector"
/** @brief rgba_vector::rgba_vector name string */
#define CNIFTI_RGBA_VECTOR_2004_STR "rgba_vector"
/** @brief shape::shape name string */
#define CNIFTI_SHAPE_2005_STR "shape"
/** @brief fsl_fnirt_displacement_field::fsl_fnirt_displacement_field name string */
#define CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006_STR "fsl_fnirt_displacement_field"
/** @brief fsl_cubic_spline_coefficients::fsl_cubic_spline_coefficients name string */
#define CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007_STR "fsl_cubic_spline_coefficients"
/** @brief fsl_dct_coefficients::fsl_dct_coefficients name string */
#define CNIFTI_FSL_DCT_COEFFICIENTS_2008_STR "fsl_dct_coefficients"
/** @brief fsl_quadratic_spline_coefficients::fsl_quadratic_spline_coefficients name string */
#define CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009_STR "fsl_quadratic_spline_coefficients"
/** @brief fsl_topup_cubic_spline_coefficients::fsl_topup_cubic_spline_coefficients name string */
#define CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016_STR "fsl_topup_cubic_spline_coefficients"
/** @brief fsl_topup_quadratic_spline_coefficients::fsl_topup_quadratic_spline_coefficients name string */
#define CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017_STR "fsl_topup_quadratic_spline_coefficients"
/** @brief fsl_topup_field::fsl_topup_field name string */
#define CNIFTI_FSL_TOPUP_FIELD_2018_STR "fsl_topup_field"

/* Returns the name of the intent value. */
static inline const char *cnifti_intent_name(const int32_t value) {
  switch (value) {
    case CNIFTI_NONE_0: return CNIFTI_NONE_0_STR;
    case CNIFTI_CORREL_2: return CNIFTI_CORREL_2_STR;
    case CNIFTI_TTEST_3: return CNIFTI_TTEST_3_STR;
    case CNIFTI_FTEST_4: return CNIFTI_FTEST_4_STR;
    case CNIFTI_ZSCORE_5: return CNIFTI_ZSCORE_5_STR;
    case CNIFTI_CHISQ_6: return CNIFTI_CHISQ_6_STR;
    case CNIFTI_BETA_7: return CNIFTI_BETA_7_STR;
    case CNIFTI_BINOM_8: return CNIFTI_BINOM_8_STR;
    case CNIFTI_GAMMA_9: return CNIFTI_GAMMA_9_STR;
    case CNIFTI_POISSON_10: return CNIFTI_POISSON_10_STR;
    case CNIFTI_NORMAL_11: return CNIFTI_NORMAL_11_STR;
    case CNIFTI_FTEST_NONC_12: return CNIFTI_FTEST_NONC_12_STR;
    case CNIFTI_CHISQ_NONC_13: return CNIFTI_CHISQ_NONC_13_STR;
    case CNIFTI_LOGISTIC_14: return CNIFTI_LOGISTIC_14_STR;
    case CNIFTI_LAPLACE_15: return CNIFTI_LAPLACE_15_STR;
    case CNIFTI_UNIFORM_16: return CNIFTI_UNIFORM_16_STR;
    case CNIFTI_TTEST_NONC_17: return CNIFTI_TTEST_NONC_17_STR;
    case CNIFTI_WEIBULL_18: return CNIFTI_WEIBULL_18_STR;
    case CNIFTI_CHI_19: return CNIFTI_CHI_19_STR;
    case CNIFTI_INVGAUSS_20: return CNIFTI_INVGAUSS_20_STR;
    case CNIFTI_EXTVAL_21: return CNIFTI_EXTVAL_21_STR;
    case CNIFTI_PVAL_22: return CNIFTI_PVAL_22_STR;
    case CNIFTI_LOGPVAL_23: return CNIFTI_LOGPVAL_23_STR;
    case CNIFTI_LOG10PVAL_24: return CNIFTI_LOG10PVAL_24_STR;
    case CNIFTI_ESTIMATE_1001: return CNIFTI_ESTIMATE_1001_STR;
    case CNIFTI_LABEL_1002: return CNIFTI_LABEL_1002_STR;
    case CNIFTI_NEURONAME_1003: return CNIFTI_NEURONAME_1003_STR;
    case CNIFTI_GENMATRIX_1004: return CNIFTI_GENMATRIX_1004_STR;
    case CNIFTI_SYMMATRIX_1005: return CNIFTI_SYMMATRIX_1005_STR;
    case CNIFTI_DISPVECT_1006: return CNIFTI_DISPVECT_1006_STR;
    case CNIFTI_VECTOR_1007: return CNIFTI_VECTOR_1007_STR;
    case CNIFTI_POINTSET_1008: return CNIFTI_POINTSET_1008_STR;
    case CNIFTI_TRIANGLE_1009: return CNIFTI_TRIANGLE_1009_STR;
    case CNIFTI_QUATERNION_1010: return CNIFTI_QUATERNION_1010_STR;
    case CNIFTI_DIMLESS_1011: return CNIFTI_DIMLESS_1011_STR;
    case CNIFTI_TIME_SERIES_2001: return CNIFTI_TIME_SERIES_2001_STR;
    case CNIFTI_NODE_INDEX_2002: return CNIFTI_NODE_INDEX_2002_STR;
    case CNIFTI_RGB_VECTOR_2003: return CNIFTI_RGB_VECTOR_2003_STR;
    case CNIFTI_RGBA_VECTOR_2004: return CNIFTI_RGBA_VECTOR_2004_STR;
    case CNIFTI_SHAPE_2005: return CNIFTI_SHAPE_2005_STR;
    case CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006: return CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006_STR;
    case CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007: return CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007_STR;
    case CNIFTI_FSL_DCT_COEFFICIENTS_2008: return CNIFTI_FSL_DCT_COEFFICIENTS_2008_STR;
    case CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009: return CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009_STR;
    case CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016: return CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016_STR;
    case CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017: return CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017_STR;
    case CNIFTI_FSL_TOPUP_FIELD_2018: return CNIFTI_FSL_TOPUP_FIELD_2018_STR;
  default: return NULL;
  }
}
/* Returns the intent value from its name. */
static inline int32_t cnifti_intent_from_name(const char *t_intent) {
  if (t_intent == NULL) return -1;
  if (strcmp(t_intent, CNIFTI_NONE_0_STR) == 0) return CNIFTI_NONE_0;
    else if (strcmp(t_intent, CNIFTI_NONE_0_STR) == 0) return CNIFTI_NONE_0;
    else if (strcmp(t_intent, CNIFTI_CORREL_2_STR) == 0) return CNIFTI_CORREL_2;
    else if (strcmp(t_intent, CNIFTI_TTEST_3_STR) == 0) return CNIFTI_TTEST_3;
    else if (strcmp(t_intent, CNIFTI_FTEST_4_STR) == 0) return CNIFTI_FTEST_4;
    else if (strcmp(t_intent, CNIFTI_ZSCORE_5_STR) == 0) return CNIFTI_ZSCORE_5;
    else if (strcmp(t_intent, CNIFTI_CHISQ_6_STR) == 0) return CNIFTI_CHISQ_6;
    else if (strcmp(t_intent, CNIFTI_BETA_7_STR) == 0) return CNIFTI_BETA_7;
    else if (strcmp(t_intent, CNIFTI_BINOM_8_STR) == 0) return CNIFTI_BINOM_8;
    else if (strcmp(t_intent, CNIFTI_GAMMA_9_STR) == 0) return CNIFTI_GAMMA_9;
    else if (strcmp(t_intent, CNIFTI_POISSON_10_STR) == 0) return CNIFTI_POISSON_10;
    else if (strcmp(t_intent, CNIFTI_NORMAL_11_STR) == 0) return CNIFTI_NORMAL_11;
    else if (strcmp(t_intent, CNIFTI_FTEST_NONC_12_STR) == 0) return CNIFTI_FTEST_NONC_12;
    else if (strcmp(t_intent, CNIFTI_CHISQ_NONC_13_STR) == 0) return CNIFTI_CHISQ_NONC_13;
    else if (strcmp(t_intent, CNIFTI_LOGISTIC_14_STR) == 0) return CNIFTI_LOGISTIC_14;
    else if (strcmp(t_intent, CNIFTI_LAPLACE_15_STR) == 0) return CNIFTI_LAPLACE_15;
    else if (strcmp(t_intent, CNIFTI_UNIFORM_16_STR) == 0) return CNIFTI_UNIFORM_16;
    else if (strcmp(t_intent, CNIFTI_TTEST_NONC_17_STR) == 0) return CNIFTI_TTEST_NONC_17;
    else if (strcmp(t_intent, CNIFTI_WEIBULL_18_STR) == 0) return CNIFTI_WEIBULL_18;
    else if (strcmp(t_intent, CNIFTI_CHI_19_STR) == 0) return CNIFTI_CHI_19;
    else if (strcmp(t_intent, CNIFTI_INVGAUSS_20_STR) == 0) return CNIFTI_INVGAUSS_20;
    else if (strcmp(t_intent, CNIFTI_EXTVAL_21_STR) == 0) return CNIFTI_EXTVAL_21;
    else if (strcmp(t_intent, CNIFTI_PVAL_22_STR) == 0) return CNIFTI_PVAL_22;
    else if (strcmp(t_intent, CNIFTI_LOGPVAL_23_STR) == 0) return CNIFTI_LOGPVAL_23;
    else if (strcmp(t_intent, CNIFTI_LOG10PVAL_24_STR) == 0) return CNIFTI_LOG10PVAL_24;
    else if (strcmp(t_intent, CNIFTI_ESTIMATE_1001_STR) == 0) return CNIFTI_ESTIMATE_1001;
    else if (strcmp(t_intent, CNIFTI_LABEL_1002_STR) == 0) return CNIFTI_LABEL_1002;
    else if (strcmp(t_intent, CNIFTI_NEURONAME_1003_STR) == 0) return CNIFTI_NEURONAME_1003;
    else if (strcmp(t_intent, CNIFTI_GENMATRIX_1004_STR) == 0) return CNIFTI_GENMATRIX_1004;
    else if (strcmp(t_intent, CNIFTI_SYMMATRIX_1005_STR) == 0) return CNIFTI_SYMMATRIX_1005;
    else if (strcmp(t_intent, CNIFTI_DISPVECT_1006_STR) == 0) return CNIFTI_DISPVECT_1006;
    else if (strcmp(t_intent, CNIFTI_VECTOR_1007_STR) == 0) return CNIFTI_VECTOR_1007;
    else if (strcmp(t_intent, CNIFTI_POINTSET_1008_STR) == 0) return CNIFTI_POINTSET_1008;
    else if (strcmp(t_intent, CNIFTI_TRIANGLE_1009_STR) == 0) return CNIFTI_TRIANGLE_1009;
    else if (strcmp(t_intent, CNIFTI_QUATERNION_1010_STR) == 0) return CNIFTI_QUATERNION_1010;
    else if (strcmp(t_intent, CNIFTI_DIMLESS_1011_STR) == 0) return CNIFTI_DIMLESS_1011;
    else if (strcmp(t_intent, CNIFTI_TIME_SERIES_2001_STR) == 0) return CNIFTI_TIME_SERIES_2001;
    else if (strcmp(t_intent, CNIFTI_NODE_INDEX_2002_STR) == 0) return CNIFTI_NODE_INDEX_2002;
    else if (strcmp(t_intent, CNIFTI_RGB_VECTOR_2003_STR) == 0) return CNIFTI_RGB_VECTOR_2003;
    else if (strcmp(t_intent, CNIFTI_RGBA_VECTOR_2004_STR) == 0) return CNIFTI_RGBA_VECTOR_2004;
    else if (strcmp(t_intent, CNIFTI_SHAPE_2005_STR) == 0) return CNIFTI_SHAPE_2005;
    else if (strcmp(t_intent, CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006_STR) == 0) return CNIFTI_FSL_FNIRT_DISPLACEMENT_FIELD_2006;
    else if (strcmp(t_intent, CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007_STR) == 0) return CNIFTI_FSL_CUBIC_SPLINE_COEFFICIENTS_2007;
    else if (strcmp(t_intent, CNIFTI_FSL_DCT_COEFFICIENTS_2008_STR) == 0) return CNIFTI_FSL_DCT_COEFFICIENTS_2008;
    else if (strcmp(t_intent, CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009_STR) == 0) return CNIFTI_FSL_QUADRATIC_SPLINE_COEFFICIENTS_2009;
    else if (strcmp(t_intent, CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016_STR) == 0) return CNIFTI_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_2016;
    else if (strcmp(t_intent, CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017_STR) == 0) return CNIFTI_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_2017;
    else if (strcmp(t_intent, CNIFTI_FSL_TOPUP_FIELD_2018_STR) == 0) return CNIFTI_FSL_TOPUP_FIELD_2018;
  return -1;
}//// Enum xform ////
/** @brief Arbitrary coordinates. (unknown::unknown) */
#define CNIFTI_UNKNOWN_0 0
/** @brief Scanner-based anatomical coordinates. (scanner_anat::scanner_anat) */
#define CNIFTI_SCANNER_ANAT_1 1
/** @brief Coordinates aligned to another file's, or to the anatomical "truth" (with an arbitrary coordinate center). (aligned_anat::aligned_anat) */
#define CNIFTI_ALIGNED_ANAT_2 2
/** @brief Coordinates aligned to the Talairach space. (talairach::talairach) */
#define CNIFTI_TALAIRACH_3 3
/** @brief Coordinates aligned to the MNI152 space. (mni_152::mni_152) */
#define CNIFTI_MNI_152_4 4
/** @brief Coordinates aligned to some template that is not MNI152 or Talairach. (template_other::template_other) */
#define CNIFTI_TEMPLATE_OTHER_5 5
/** @brief unknown::unknown name string */
#define CNIFTI_UNKNOWN_0_STR "unknown"
/** @brief scanner_anat::scanner_anat name string */
#define CNIFTI_SCANNER_ANAT_1_STR "scanner_anat"
/** @brief aligned_anat::aligned_anat name string */
#define CNIFTI_ALIGNED_ANAT_2_STR "aligned_anat"
/** @brief talairach::talairach name string */
#define CNIFTI_TALAIRACH_3_STR "talairach"
/** @brief mni_152::mni_152 name string */
#define CNIFTI_MNI_152_4_STR "mni_152"
/** @brief template_other::template_other name string */
#define CNIFTI_TEMPLATE_OTHER_5_STR "template_other"

/* Returns the name of the xform value. */
static inline const char *cnifti_xform_name(const int32_t value) {
  switch (value) {
    case CNIFTI_UNKNOWN_0: return CNIFTI_UNKNOWN_0_STR;
    case CNIFTI_SCANNER_ANAT_1: return CNIFTI_SCANNER_ANAT_1_STR;
    case CNIFTI_ALIGNED_ANAT_2: return CNIFTI_ALIGNED_ANAT_2_STR;
    case CNIFTI_TALAIRACH_3: return CNIFTI_TALAIRACH_3_STR;
    case CNIFTI_MNI_152_4: return CNIFTI_MNI_152_4_STR;
    case CNIFTI_TEMPLATE_OTHER_5: return CNIFTI_TEMPLATE_OTHER_5_STR;
  default: return NULL;
  }
}
/* Returns the xform value from its name. */
static inline int32_t cnifti_xform_from_name(const char *t_xform) {
  if (t_xform == NULL) return -1;
  if (strcmp(t_xform, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_xform, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_xform, CNIFTI_SCANNER_ANAT_1_STR) == 0) return CNIFTI_SCANNER_ANAT_1;
    else if (strcmp(t_xform, CNIFTI_ALIGNED_ANAT_2_STR) == 0) return CNIFTI_ALIGNED_ANAT_2;
    else if (strcmp(t_xform, CNIFTI_TALAIRACH_3_STR) == 0) return CNIFTI_TALAIRACH_3;
    else if (strcmp(t_xform, CNIFTI_MNI_152_4_STR) == 0) return CNIFTI_MNI_152_4;
    else if (strcmp(t_xform, CNIFTI_TEMPLATE_OTHER_5_STR) == 0) return CNIFTI_TEMPLATE_OTHER_5;
  return -1;
}//// Enum units ////
/** @brief Unknown units (unknown::unknown) */
#define CNIFTI_UNKNOWN_0 0
/** @brief Meter (m) (meter::meter) */
#define CNIFTI_METER_1 1
/** @brief Millimeter (mm) (mm::mm) */
#define CNIFTI_MM_2 2
/** @brief Micron (um) (micron::micron) */
#define CNIFTI_MICRON_3 3
/** @brief Seconds (s) (sec::sec) */
#define CNIFTI_SEC_8 8
/** @brief Miliseconds (ms) (msec::msec) */
#define CNIFTI_MSEC_16 16
/** @brief Microseconds (us) (usec::usec) */
#define CNIFTI_USEC_24 24
/** @brief Hertz (Hz) (hz::hz) */
#define CNIFTI_HZ_32 32
/** @brief Parts-per-million (ppm) (ppm::ppm) */
#define CNIFTI_PPM_40 40
/** @brief Radians per second (rad/s) (rads::rads) */
#define CNIFTI_RADS_48 48
/** @brief unknown::unknown name string */
#define CNIFTI_UNKNOWN_0_STR "unknown"
/** @brief meter::meter name string */
#define CNIFTI_METER_1_STR "meter"
/** @brief mm::mm name string */
#define CNIFTI_MM_2_STR "mm"
/** @brief micron::micron name string */
#define CNIFTI_MICRON_3_STR "micron"
/** @brief sec::sec name string */
#define CNIFTI_SEC_8_STR "sec"
/** @brief msec::msec name string */
#define CNIFTI_MSEC_16_STR "msec"
/** @brief usec::usec name string */
#define CNIFTI_USEC_24_STR "usec"
/** @brief hz::hz name string */
#define CNIFTI_HZ_32_STR "hz"
/** @brief ppm::ppm name string */
#define CNIFTI_PPM_40_STR "ppm"
/** @brief rads::rads name string */
#define CNIFTI_RADS_48_STR "rads"

/* Returns the name of the units value. */
static inline const char *cnifti_units_name(const int32_t value) {
  switch (value) {
    case CNIFTI_UNKNOWN_0: return CNIFTI_UNKNOWN_0_STR;
    case CNIFTI_METER_1: return CNIFTI_METER_1_STR;
    case CNIFTI_MM_2: return CNIFTI_MM_2_STR;
    case CNIFTI_MICRON_3: return CNIFTI_MICRON_3_STR;
    case CNIFTI_SEC_8: return CNIFTI_SEC_8_STR;
    case CNIFTI_MSEC_16: return CNIFTI_MSEC_16_STR;
    case CNIFTI_USEC_24: return CNIFTI_USEC_24_STR;
    case CNIFTI_HZ_32: return CNIFTI_HZ_32_STR;
    case CNIFTI_PPM_40: return CNIFTI_PPM_40_STR;
    case CNIFTI_RADS_48: return CNIFTI_RADS_48_STR;
  default: return NULL;
  }
}
/* Returns the units value from its name. */
static inline int32_t cnifti_units_from_name(const char *t_units) {
  if (t_units == NULL) return -1;
  if (strcmp(t_units, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_units, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_units, CNIFTI_METER_1_STR) == 0) return CNIFTI_METER_1;
    else if (strcmp(t_units, CNIFTI_MM_2_STR) == 0) return CNIFTI_MM_2;
    else if (strcmp(t_units, CNIFTI_MICRON_3_STR) == 0) return CNIFTI_MICRON_3;
    else if (strcmp(t_units, CNIFTI_SEC_8_STR) == 0) return CNIFTI_SEC_8;
    else if (strcmp(t_units, CNIFTI_MSEC_16_STR) == 0) return CNIFTI_MSEC_16;
    else if (strcmp(t_units, CNIFTI_USEC_24_STR) == 0) return CNIFTI_USEC_24;
    else if (strcmp(t_units, CNIFTI_HZ_32_STR) == 0) return CNIFTI_HZ_32;
    else if (strcmp(t_units, CNIFTI_PPM_40_STR) == 0) return CNIFTI_PPM_40;
    else if (strcmp(t_units, CNIFTI_RADS_48_STR) == 0) return CNIFTI_RADS_48;
  return -1;
}//// Enum slice ////
/** @brief Slice order: Unknown (unknown::unknown) */
#define CNIFTI_UNKNOWN_0 0
/** @brief Slice order: Sequential, increasing (seq_inc::seq_inc) */
#define CNIFTI_SEQ_INC_1 1
/** @brief Slice order: Sequential, decreasing (seq_dec::seq_dec) */
#define CNIFTI_SEQ_DEC_2 2
/** @brief Slice order: Interleaved, increasing, starting at the first slice (alt_inc::alt_inc) */
#define CNIFTI_ALT_INC_3 3
/** @brief Slice order: Interleaved, decreasing, starting at the last slice (alt_dec::alt_dec) */
#define CNIFTI_ALT_DEC_4 4
/** @brief Slice order: Interleaved, increasing, starting at the second slice (alt_inc2::alt_inc2) */
#define CNIFTI_ALT_INC2_5 5
/** @brief Slice order: Interleaved, decreasing, starting at the second to last slice (alt_dec2::alt_dec2) */
#define CNIFTI_ALT_DEC2_6 6
/** @brief unknown::unknown name string */
#define CNIFTI_UNKNOWN_0_STR "unknown"
/** @brief seq_inc::seq_inc name string */
#define CNIFTI_SEQ_INC_1_STR "seq_inc"
/** @brief seq_dec::seq_dec name string */
#define CNIFTI_SEQ_DEC_2_STR "seq_dec"
/** @brief alt_inc::alt_inc name string */
#define CNIFTI_ALT_INC_3_STR "alt_inc"
/** @brief alt_dec::alt_dec name string */
#define CNIFTI_ALT_DEC_4_STR "alt_dec"
/** @brief alt_inc2::alt_inc2 name string */
#define CNIFTI_ALT_INC2_5_STR "alt_inc2"
/** @brief alt_dec2::alt_dec2 name string */
#define CNIFTI_ALT_DEC2_6_STR "alt_dec2"

/* Returns the name of the slice value. */
static inline const char *cnifti_slice_name(const int32_t value) {
  switch (value) {
    case CNIFTI_UNKNOWN_0: return CNIFTI_UNKNOWN_0_STR;
    case CNIFTI_SEQ_INC_1: return CNIFTI_SEQ_INC_1_STR;
    case CNIFTI_SEQ_DEC_2: return CNIFTI_SEQ_DEC_2_STR;
    case CNIFTI_ALT_INC_3: return CNIFTI_ALT_INC_3_STR;
    case CNIFTI_ALT_DEC_4: return CNIFTI_ALT_DEC_4_STR;
    case CNIFTI_ALT_INC2_5: return CNIFTI_ALT_INC2_5_STR;
    case CNIFTI_ALT_DEC2_6: return CNIFTI_ALT_DEC2_6_STR;
  default: return NULL;
  }
}
/* Returns the slice value from its name. */
static inline int32_t cnifti_slice_from_name(const char *t_slice) {
  if (t_slice == NULL) return -1;
  if (strcmp(t_slice, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_slice, CNIFTI_UNKNOWN_0_STR) == 0) return CNIFTI_UNKNOWN_0;
    else if (strcmp(t_slice, CNIFTI_SEQ_INC_1_STR) == 0) return CNIFTI_SEQ_INC_1;
    else if (strcmp(t_slice, CNIFTI_SEQ_DEC_2_STR) == 0) return CNIFTI_SEQ_DEC_2;
    else if (strcmp(t_slice, CNIFTI_ALT_INC_3_STR) == 0) return CNIFTI_ALT_INC_3;
    else if (strcmp(t_slice, CNIFTI_ALT_DEC_4_STR) == 0) return CNIFTI_ALT_DEC_4;
    else if (strcmp(t_slice, CNIFTI_ALT_INC2_5_STR) == 0) return CNIFTI_ALT_INC2_5;
    else if (strcmp(t_slice, CNIFTI_ALT_DEC2_6_STR) == 0) return CNIFTI_ALT_DEC2_6;
  return -1;
}//// Enum ecode ////
/** @brief ignore::ignore */
#define CNIFTI_IGNORE_0 0
/** @brief intended for raw DICOM attributes (dicom::dicom) */
#define CNIFTI_DICOM_2 2
/**
 * @brief Robert W Cox: rwcox\@nih.gov
 * https://afni.nimh.nih.gov/afni
 *  (afni::afni)
 */
#define CNIFTI_AFNI_4 4
/** @brief plain ASCII text only (comment::comment) */
#define CNIFTI_COMMENT_6 6
/**
 * @brief David B Keator: dbkeator\@uci.edu
 * http://www.nbirn.net/Resources/Users/Applications/xcede/index.htm
 *  (xcede::xcede)
 */
#define CNIFTI_XCEDE_8 8
/**
 * @brief Mark A Horsfield
 * mah5\@leicester.ac.uk
 *  (jimdiminfo::jimdiminfo)
 */
#define CNIFTI_JIMDIMINFO_10 10
/**
 * @brief Kate Fissell: fissell\@pitt.edu
 * http://kraepelin.wpic.pitt.edu/~fissell/NIFTI_ECODE_WORKFLOW_FWDS/NIFTI_ECODE_WORKFLOW_FWDS.html
 *  (workflow_fwds::workflow_fwds)
 */
#define CNIFTI_WORKFLOW_FWDS_12 12
/** @brief http://surfer.nmr.mgh.harvard.edu/ (freesurfer::freesurfer) */
#define CNIFTI_FREESURFER_14 14
/** @brief embedded Python objects (pypickle::pypickle) */
#define CNIFTI_PYPICKLE_16 16
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (mind_ident::mind_ident)
 */
#define CNIFTI_MIND_IDENT_18 18
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (b_value::b_value)
 */
#define CNIFTI_B_VALUE_20 20
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (spherical_direction::spherical_direction)
 */
#define CNIFTI_SPHERICAL_DIRECTION_22 22
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (dt_component::dt_component)
 */
#define CNIFTI_DT_COMPONENT_24 24
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (shc_degreeorder::shc_degreeorder)
 */
#define CNIFTI_SHC_DEGREEORDER_26 26
/** @brief Dan Kimberg: www.voxbo.org (voxbo::voxbo) */
#define CNIFTI_VOXBO_28 28
/**
 * @brief John Harwell: john\@brainvis.wustl.edu
 * http://brainvis.wustl.edu/wiki/index.php/Caret:Documentation:CaretNiftiExtension
 *  (caret::caret)
 */
#define CNIFTI_CARET_30 30
/** @brief CIFTI-2_Main_FINAL_1March2014.pdf (cifti::cifti) */
#define CNIFTI_CIFTI_32 32
/** @brief variable_frame_timing::variable_frame_timing */
#define CNIFTI_VARIABLE_FRAME_TIMING_34 34
/** @brief Munster University Hospital (eval::eval) */
#define CNIFTI_EVAL_38 38
/**
 * @brief MATLAB extension
 * http://www.mathworks.com/matlabcentral/fileexchange/42997-dicom-to-nifti-converter
 *  (matlab::matlab)
 */
#define CNIFTI_MATLAB_40 40
/**
 * @brief Quantiphyse extension
 * https://quantiphyse.readthedocs.io/en/latest/advanced/nifti_extension.html
 *  (quantiphyse::quantiphyse)
 */
#define CNIFTI_QUANTIPHYSE_42 42
/**
 * @brief Magnetic Resonance Spectroscopy (MRS)
 *  (mrs::mrs)
 */
#define CNIFTI_MRS_44 44
/** @brief ignore::ignore name string */
#define CNIFTI_IGNORE_0_STR "ignore"
/** @brief dicom::dicom name string */
#define CNIFTI_DICOM_2_STR "dicom"
/** @brief afni::afni name string */
#define CNIFTI_AFNI_4_STR "afni"
/** @brief comment::comment name string */
#define CNIFTI_COMMENT_6_STR "comment"
/** @brief xcede::xcede name string */
#define CNIFTI_XCEDE_8_STR "xcede"
/** @brief jimdiminfo::jimdiminfo name string */
#define CNIFTI_JIMDIMINFO_10_STR "jimdiminfo"
/** @brief workflow_fwds::workflow_fwds name string */
#define CNIFTI_WORKFLOW_FWDS_12_STR "workflow_fwds"
/** @brief freesurfer::freesurfer name string */
#define CNIFTI_FREESURFER_14_STR "freesurfer"
/** @brief pypickle::pypickle name string */
#define CNIFTI_PYPICKLE_16_STR "pypickle"
/** @brief mind_ident::mind_ident name string */
#define CNIFTI_MIND_IDENT_18_STR "mind_ident"
/** @brief b_value::b_value name string */
#define CNIFTI_B_VALUE_20_STR "b_value"
/** @brief spherical_direction::spherical_direction name string */
#define CNIFTI_SPHERICAL_DIRECTION_22_STR "spherical_direction"
/** @brief dt_component::dt_component name string */
#define CNIFTI_DT_COMPONENT_24_STR "dt_component"
/** @brief shc_degreeorder::shc_degreeorder name string */
#define CNIFTI_SHC_DEGREEORDER_26_STR "shc_degreeorder"
/** @brief voxbo::voxbo name string */
#define CNIFTI_VOXBO_28_STR "voxbo"
/** @brief caret::caret name string */
#define CNIFTI_CARET_30_STR "caret"
/** @brief cifti::cifti name string */
#define CNIFTI_CIFTI_32_STR "cifti"
/** @brief variable_frame_timing::variable_frame_timing name string */
#define CNIFTI_VARIABLE_FRAME_TIMING_34_STR "variable_frame_timing"
/** @brief eval::eval name string */
#define CNIFTI_EVAL_38_STR "eval"
/** @brief matlab::matlab name string */
#define CNIFTI_MATLAB_40_STR "matlab"
/** @brief quantiphyse::quantiphyse name string */
#define CNIFTI_QUANTIPHYSE_42_STR "quantiphyse"
/** @brief mrs::mrs name string */
#define CNIFTI_MRS_44_STR "mrs"

/* Returns the name of the ecode value. */
static inline const char *cnifti_ecode_name(const int32_t value) {
  switch (value) {
    case CNIFTI_IGNORE_0: return CNIFTI_IGNORE_0_STR;
    case CNIFTI_DICOM_2: return CNIFTI_DICOM_2_STR;
    case CNIFTI_AFNI_4: return CNIFTI_AFNI_4_STR;
    case CNIFTI_COMMENT_6: return CNIFTI_COMMENT_6_STR;
    case CNIFTI_XCEDE_8: return CNIFTI_XCEDE_8_STR;
    case CNIFTI_JIMDIMINFO_10: return CNIFTI_JIMDIMINFO_10_STR;
    case CNIFTI_WORKFLOW_FWDS_12: return CNIFTI_WORKFLOW_FWDS_12_STR;
    case CNIFTI_FREESURFER_14: return CNIFTI_FREESURFER_14_STR;
    case CNIFTI_PYPICKLE_16: return CNIFTI_PYPICKLE_16_STR;
    case CNIFTI_MIND_IDENT_18: return CNIFTI_MIND_IDENT_18_STR;
    case CNIFTI_B_VALUE_20: return CNIFTI_B_VALUE_20_STR;
    case CNIFTI_SPHERICAL_DIRECTION_22: return CNIFTI_SPHERICAL_DIRECTION_22_STR;
    case CNIFTI_DT_COMPONENT_24: return CNIFTI_DT_COMPONENT_24_STR;
    case CNIFTI_SHC_DEGREEORDER_26: return CNIFTI_SHC_DEGREEORDER_26_STR;
    case CNIFTI_VOXBO_28: return CNIFTI_VOXBO_28_STR;
    case CNIFTI_CARET_30: return CNIFTI_CARET_30_STR;
    case CNIFTI_CIFTI_32: return CNIFTI_CIFTI_32_STR;
    case CNIFTI_VARIABLE_FRAME_TIMING_34: return CNIFTI_VARIABLE_FRAME_TIMING_34_STR;
    case CNIFTI_EVAL_38: return CNIFTI_EVAL_38_STR;
    case CNIFTI_MATLAB_40: return CNIFTI_MATLAB_40_STR;
    case CNIFTI_QUANTIPHYSE_42: return CNIFTI_QUANTIPHYSE_42_STR;
    case CNIFTI_MRS_44: return CNIFTI_MRS_44_STR;
  default: return NULL;
  }
}
/* Returns the ecode value from its name. */
static inline int32_t cnifti_ecode_from_name(const char *t_ecode) {
  if (t_ecode == NULL) return -1;
  if (strcmp(t_ecode, CNIFTI_IGNORE_0_STR) == 0) return CNIFTI_IGNORE_0;
    else if (strcmp(t_ecode, CNIFTI_IGNORE_0_STR) == 0) return CNIFTI_IGNORE_0;
    else if (strcmp(t_ecode, CNIFTI_DICOM_2_STR) == 0) return CNIFTI_DICOM_2;
    else if (strcmp(t_ecode, CNIFTI_AFNI_4_STR) == 0) return CNIFTI_AFNI_4;
    else if (strcmp(t_ecode, CNIFTI_COMMENT_6_STR) == 0) return CNIFTI_COMMENT_6;
    else if (strcmp(t_ecode, CNIFTI_XCEDE_8_STR) == 0) return CNIFTI_XCEDE_8;
    else if (strcmp(t_ecode, CNIFTI_JIMDIMINFO_10_STR) == 0) return CNIFTI_JIMDIMINFO_10;
    else if (strcmp(t_ecode, CNIFTI_WORKFLOW_FWDS_12_STR) == 0) return CNIFTI_WORKFLOW_FWDS_12;
    else if (strcmp(t_ecode, CNIFTI_FREESURFER_14_STR) == 0) return CNIFTI_FREESURFER_14;
    else if (strcmp(t_ecode, CNIFTI_PYPICKLE_16_STR) == 0) return CNIFTI_PYPICKLE_16;
    else if (strcmp(t_ecode, CNIFTI_MIND_IDENT_18_STR) == 0) return CNIFTI_MIND_IDENT_18;
    else if (strcmp(t_ecode, CNIFTI_B_VALUE_20_STR) == 0) return CNIFTI_B_VALUE_20;
    else if (strcmp(t_ecode, CNIFTI_SPHERICAL_DIRECTION_22_STR) == 0) return CNIFTI_SPHERICAL_DIRECTION_22;
    else if (strcmp(t_ecode, CNIFTI_DT_COMPONENT_24_STR) == 0) return CNIFTI_DT_COMPONENT_24;
    else if (strcmp(t_ecode, CNIFTI_SHC_DEGREEORDER_26_STR) == 0) return CNIFTI_SHC_DEGREEORDER_26;
    else if (strcmp(t_ecode, CNIFTI_VOXBO_28_STR) == 0) return CNIFTI_VOXBO_28;
    else if (strcmp(t_ecode, CNIFTI_CARET_30_STR) == 0) return CNIFTI_CARET_30;
    else if (strcmp(t_ecode, CNIFTI_CIFTI_32_STR) == 0) return CNIFTI_CIFTI_32;
    else if (strcmp(t_ecode, CNIFTI_VARIABLE_FRAME_TIMING_34_STR) == 0) return CNIFTI_VARIABLE_FRAME_TIMING_34;
    else if (strcmp(t_ecode, CNIFTI_EVAL_38_STR) == 0) return CNIFTI_EVAL_38;
    else if (strcmp(t_ecode, CNIFTI_MATLAB_40_STR) == 0) return CNIFTI_MATLAB_40;
    else if (strcmp(t_ecode, CNIFTI_QUANTIPHYSE_42_STR) == 0) return CNIFTI_QUANTIPHYSE_42;
    else if (strcmp(t_ecode, CNIFTI_MRS_44_STR) == 0) return CNIFTI_MRS_44;
  return -1;
}/* Datatype size */

/** @brief dt unknown size (bytes) */
#define CNIFTI_UNKNOWN_0_SIZE 0
/** @brief dt binary size (bytes) */
#define CNIFTI_BINARY_1_SIZE 0
/** @brief dt uint8 size (bytes) */
#define CNIFTI_UINT8_2_SIZE 1
/** @brief dt int16 size (bytes) */
#define CNIFTI_INT16_4_SIZE 2
/** @brief dt int32 size (bytes) */
#define CNIFTI_INT32_8_SIZE 4
/** @brief dt float32 size (bytes) */
#define CNIFTI_FLOAT32_16_SIZE 4
/** @brief dt complex64 size (bytes) */
#define CNIFTI_COMPLEX64_32_SIZE 8
/** @brief dt float64 size (bytes) */
#define CNIFTI_FLOAT64_64_SIZE 8
/** @brief dt rgb24 size (bytes) */
#define CNIFTI_RGB24_128_SIZE 3
/** @brief dt int8 size (bytes) */
#define CNIFTI_INT8_256_SIZE 1
/** @brief dt unit16 size (bytes) */
#define CNIFTI_UNIT16_512_SIZE 2
/** @brief dt uint32 size (bytes) */
#define CNIFTI_UINT32_768_SIZE 4
/** @brief dt int64 size (bytes) */
#define CNIFTI_INT64_1024_SIZE 8
/** @brief dt uint64 size (bytes) */
#define CNIFTI_UINT64_1280_SIZE 8
/** @brief dt float128 size (bytes) */
#define CNIFTI_FLOAT128_1536_SIZE 16
/** @brief dt complex128 size (bytes) */
#define CNIFTI_COMPLEX128_1792_SIZE 16
/** @brief dt complex256 size (bytes) */
#define CNIFTI_COMPLEX256_2048_SIZE 32
/** @brief dt rgba32 size (bytes) */
#define CNIFTI_RGBA32_2304_SIZE 4

//// Nifti headers ////

CNIFTI_STATIC_ASSERT(sizeof(cnifti_n1_header_t) == 348, "nifti1 header size is not 348 bytes");
CNIFTI_STATIC_ASSERT(sizeof(cnifti_n2_header_t) == 540, "nifti2 header size is not 540 bytes");

/* Computed header field frequency_dim */
static inline int32_t cnifti_n1_header_frequency_dim(const cnifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info & 3;
}
/* Computed header field phase_dim */
static inline int32_t cnifti_n1_header_phase_dim(const cnifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info >> 2 & 3;
}
/* Computed header field slice_dim */
static inline int32_t cnifti_n1_header_slice_dim(const cnifti_n1_header_t *t_n1_header) {
  return t_n1_header->dim_info >> 4 & 3;
}
/* Computed header field spatial_units */
static inline int32_t cnifti_n1_header_spatial_units(const cnifti_n1_header_t *t_n1_header) {
  return t_n1_header->xyzt_units & 7;
}
/* Computed header field temporal_units */
static inline int32_t cnifti_n1_header_temporal_units(const cnifti_n1_header_t *t_n1_header) {
  return t_n1_header->xyzt_units & 56;
}
/* Computed header field frequency_dim */
static inline int32_t cnifti_n2_header_frequency_dim(const cnifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info & 3;
}
/* Computed header field phase_dim */
static inline int32_t cnifti_n2_header_phase_dim(const cnifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info >> 2 & 3;
}
/* Computed header field slice_dim */
static inline int32_t cnifti_n2_header_slice_dim(const cnifti_n2_header_t *t_n2_header) {
  return t_n2_header->dim_info >> 4 & 3;
}
/* Computed header field spatial_units */
static inline int32_t cnifti_n2_header_spatial_units(const cnifti_n2_header_t *t_n2_header) {
  return t_n2_header->xyzt_units & 7;
}
/* Computed header field temporal_units */
static inline int32_t cnifti_n2_header_temporal_units(const cnifti_n2_header_t *t_n2_header) {
  return t_n2_header->xyzt_units & 56;
}CNIFTI_STATIC_ASSERT(sizeof(cnifti_extension_indicator_t) == 4, "extension header size is not 4 bytes");
CNIFTI_STATIC_ASSERT(sizeof(cnifti_extension_header_t) == 8, "extension header size is not 8 bytes");

/** @brief Nifti header union */
typedef union cnifti_header_t {
  cnifti_n1_header_t n1_header;
    cnifti_n2_header_t n2_header;
  } cnifti_header_t;

//// Implementation ////

/** @brief Get datatype size in bytes */
static inline int32_t cnifti_dt_size(int32_t t_dt) {
  switch (t_dt) {
    case CNIFTI_UNKNOWN_0: return CNIFTI_UNKNOWN_0_SIZE;
    case CNIFTI_BINARY_1: return CNIFTI_BINARY_1_SIZE;
    case CNIFTI_UINT8_2: return CNIFTI_UINT8_2_SIZE;
    case CNIFTI_INT16_4: return CNIFTI_INT16_4_SIZE;
    case CNIFTI_INT32_8: return CNIFTI_INT32_8_SIZE;
    case CNIFTI_FLOAT32_16: return CNIFTI_FLOAT32_16_SIZE;
    case CNIFTI_COMPLEX64_32: return CNIFTI_COMPLEX64_32_SIZE;
    case CNIFTI_FLOAT64_64: return CNIFTI_FLOAT64_64_SIZE;
    case CNIFTI_RGB24_128: return CNIFTI_RGB24_128_SIZE;
    case CNIFTI_INT8_256: return CNIFTI_INT8_256_SIZE;
    case CNIFTI_UNIT16_512: return CNIFTI_UNIT16_512_SIZE;
    case CNIFTI_UINT32_768: return CNIFTI_UINT32_768_SIZE;
    case CNIFTI_INT64_1024: return CNIFTI_INT64_1024_SIZE;
    case CNIFTI_UINT64_1280: return CNIFTI_UINT64_1280_SIZE;
    case CNIFTI_FLOAT128_1536: return CNIFTI_FLOAT128_1536_SIZE;
    case CNIFTI_COMPLEX128_1792: return CNIFTI_COMPLEX128_1792_SIZE;
    case CNIFTI_COMPLEX256_2048: return CNIFTI_COMPLEX256_2048_SIZE;
    case CNIFTI_RGBA32_2304: return CNIFTI_RGBA32_2304_SIZE;
  default: return 0;
  }
}
/* Utility function for printing n1_header. */
static inline void cnifti_n1_header_print(const cnifti_n1_header_t *t_n1_header) {
  const char *intent_intent_code = cnifti_intent_name(t_n1_header->intent_code);
  const char *dt_datatype = cnifti_dt_name(t_n1_header->datatype);
  const char *slice_slice_code = cnifti_slice_name(t_n1_header->slice_code);
  const char *xform_qform_code = cnifti_xform_name(t_n1_header->qform_code);
  const char *xform_sform_code = cnifti_xform_name(t_n1_header->sform_code);
  const char *units_spatial_units = cnifti_units_name(cnifti_n1_header_spatial_units(t_n1_header));
  const char *units_temporal_units = cnifti_units_name(cnifti_n1_header_temporal_units(t_n1_header));
    CNIFTI_PRINTF(
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
      "intent_code     : %i\n"
      "datatype        : %i\n"
      "bitpix          : %i\n"
      "slice_start     : %i\n"
      "pixdim          : [ %f, %f, %f, %f, %f, %f, %f, %f ]\n"
      "vox_offset      : %f\n"
      "scl_slope       : %f\n"
      "scl_inter       : %f\n"
      "slice_end       : %i\n"
      "slice_code      : %i\n"
      "xyzt_units      : %i\n"
      "cal_max         : %f\n"
      "cal_min         : %f\n"
      "slice_duration  : %f\n"
      "toffset         : %f\n"
      "glmax           : %i\n"
      "glmin           : %i\n"
      "descrip         : '%.80s'\n"
      "aux_file        : '%.24s'\n"
      "qform_code      : %i\n"
      "sform_code      : %i\n"
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
      (dt_datatype == NULL ? "<non standard>" : dt_datatype),
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
      (xform_sform_code == NULL ? "<non standard>" : xform_sform_code),
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
      t_n1_header->magic,
      t_n1_header->magic,
      t_n1_header->magic,
      (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
      cnifti_n1_header_spatial_units(t_n1_header),
      (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
      cnifti_n1_header_temporal_units(t_n1_header)
    );
}
/* Utility function for printing n2_header. */
static inline void cnifti_n2_header_print(const cnifti_n2_header_t *t_n2_header) {
  const char *dt_datatype = cnifti_dt_name(t_n2_header->datatype);
  const char *xform_qform_code = cnifti_xform_name(t_n2_header->qform_code);
  const char *xform_sform_code = cnifti_xform_name(t_n2_header->sform_code);
  const char *slice_slice_code = cnifti_slice_name(t_n2_header->slice_code);
  const char *intent_intent_code = cnifti_intent_name(t_n2_header->intent_code);
  const char *units_spatial_units = cnifti_units_name(cnifti_n2_header_spatial_units(t_n2_header));
  const char *units_temporal_units = cnifti_units_name(cnifti_n2_header_temporal_units(t_n2_header));
    CNIFTI_PRINTF(
      "sizeof_hdr      : %i\n"
      "magic           : '%.4s'\n"
      "magic2          : [ %i, %i, %i, %i ]\n"
      "datatype        : %i\n"
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
      "qform_code      : %i\n"
      "sform_code      : %i\n"
      "quatern_b       : %f\n"
      "quatern_c       : %f\n"
      "quatern_d       : %f\n"
      "qoffset_x       : %f\n"
      "qoffset_y       : %f\n"
      "qoffset_z       : %f\n"
      "srow_x          : [ %f, %f, %f, %f ]\n"
      "srow_y          : [ %f, %f, %f, %f ]\n"
      "srow_z          : [ %f, %f, %f, %f ]\n"
      "slice_code      : %i\n"
      "xyzt_units      : %i\n"
      "intent_code     : %i\n"
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
      (xform_sform_code == NULL ? "<non standard>" : xform_sform_code),
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
      t_n2_header->xyzt_units,
      (intent_intent_code == NULL ? "<non standard>" : intent_intent_code),
      t_n2_header->intent_name,
      t_n2_header->dim_info,
      t_n2_header->unused_str,
      t_n2_header->unused_str,
      t_n2_header->unused_str,
      t_n2_header->unused_str,
      (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
      cnifti_n2_header_spatial_units(t_n2_header),
      (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
      cnifti_n2_header_temporal_units(t_n2_header)
    );
}
#define CNIFTI_PEEK_NIFTI2 1
#define CNIFTI_PEEK_SWAP 2
/**
 * @brief Peek at first 4 bytes of header to determine nifti version and endianness.
 * Return value can be bit compared with CNIFTI_PEEK_* values.
 * If return value is -1 this is not a nifti header.
 */
static inline int32_t cnifti_peek(const uint32_t t_header_start) {
  switch (t_header_start) {
  case 348: return 0;
  case 1543569408: return CNIFTI_PEEK_SWAP;
  case 540: return CNIFTI_PEEK_NIFTI2;
  case 469893120: return CNIFTI_PEEK_NIFTI2 & CNIFTI_PEEK_SWAP;
  default: return -1;
  }
}
/* Utility function for byte swapping n1_header. */
static inline void cnifti_n1_header_swap(cnifti_n1_header_t *t_n1_header) {
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
static inline void cnifti_n2_header_swap(cnifti_n2_header_t *t_n2_header) {
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
static inline int64_t cnifti_n1_header_array_size(const cnifti_n1_header_t *t_n1_header) {
  int64_t size = t_n1_header->bitpix / 8;
  for (int i = 0; i < t_n1_header->dim[0]; ++i) { size *= t_n1_header->dim[i+1]; }
  return size;
}
/** @brief Calculate n2_header data array size (in bytes). */
static inline int64_t cnifti_n2_header_array_size(const cnifti_n2_header_t *t_n2_header) {
  int64_t size = t_n2_header->bitpix / 8;
  for (int i = 0; i < t_n2_header->dim[0]; ++i) { size *= t_n2_header->dim[i+1]; }
  return size;
}



#ifdef __cplusplus
}
#endif

#endif /* CNIFTI_cnifti_HEADER_H */