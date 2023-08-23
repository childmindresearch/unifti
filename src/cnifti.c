/** @file cnifti.c */

#include "cnifti.h"

#include <string.h>
#include <stdio.h>
#include <stdio.h>


#include "endianness.h"



#include "endianness.h"



/* Implementation */

/* Get the datatype size in bytes */
int32_t cnifti_dt_size(int32_t dt) {
  switch (dt) {
    case CNIFTI_DT_UNKNOWN: return CNIFTI_DT_UNKNOWN_SIZE;
    case CNIFTI_DT_BINARY: return CNIFTI_DT_BINARY_SIZE;
    case CNIFTI_DT_UINT8: return CNIFTI_DT_UINT8_SIZE;
    case CNIFTI_DT_INT16: return CNIFTI_DT_INT16_SIZE;
    case CNIFTI_DT_INT32: return CNIFTI_DT_INT32_SIZE;
    case CNIFTI_DT_FLOAT32: return CNIFTI_DT_FLOAT32_SIZE;
    case CNIFTI_DT_COMPLEX64: return CNIFTI_DT_COMPLEX64_SIZE;
    case CNIFTI_DT_FLOAT64: return CNIFTI_DT_FLOAT64_SIZE;
    case CNIFTI_DT_RGB24: return CNIFTI_DT_RGB24_SIZE;
    case CNIFTI_DT_INT8: return CNIFTI_DT_INT8_SIZE;
    case CNIFTI_DT_UNIT16: return CNIFTI_DT_UNIT16_SIZE;
    case CNIFTI_DT_UINT32: return CNIFTI_DT_UINT32_SIZE;
    case CNIFTI_DT_INT64: return CNIFTI_DT_INT64_SIZE;
    case CNIFTI_DT_UINT64: return CNIFTI_DT_UINT64_SIZE;
    case CNIFTI_DT_FLOAT128: return CNIFTI_DT_FLOAT128_SIZE;
    case CNIFTI_DT_COMPLEX128: return CNIFTI_DT_COMPLEX128_SIZE;
    case CNIFTI_DT_COMPLEX256: return CNIFTI_DT_COMPLEX256_SIZE;
    case CNIFTI_DT_RGBA32: return CNIFTI_DT_RGBA32_SIZE;
    default: return 0;
  }
}

/* Get the dt name */
const char *cnifti_dt_name(int32_t dt) {
  switch (dt) {
    case CNIFTI_DT_UNKNOWN: return CNIFTI_DT_UNKNOWN_NAME;
    case CNIFTI_DT_BINARY: return CNIFTI_DT_BINARY_NAME;
    case CNIFTI_DT_UINT8: return CNIFTI_DT_UINT8_NAME;
    case CNIFTI_DT_INT16: return CNIFTI_DT_INT16_NAME;
    case CNIFTI_DT_INT32: return CNIFTI_DT_INT32_NAME;
    case CNIFTI_DT_FLOAT32: return CNIFTI_DT_FLOAT32_NAME;
    case CNIFTI_DT_COMPLEX64: return CNIFTI_DT_COMPLEX64_NAME;
    case CNIFTI_DT_FLOAT64: return CNIFTI_DT_FLOAT64_NAME;
    case CNIFTI_DT_RGB24: return CNIFTI_DT_RGB24_NAME;
    case CNIFTI_DT_INT8: return CNIFTI_DT_INT8_NAME;
    case CNIFTI_DT_UNIT16: return CNIFTI_DT_UNIT16_NAME;
    case CNIFTI_DT_UINT32: return CNIFTI_DT_UINT32_NAME;
    case CNIFTI_DT_INT64: return CNIFTI_DT_INT64_NAME;
    case CNIFTI_DT_UINT64: return CNIFTI_DT_UINT64_NAME;
    case CNIFTI_DT_FLOAT128: return CNIFTI_DT_FLOAT128_NAME;
    case CNIFTI_DT_COMPLEX128: return CNIFTI_DT_COMPLEX128_NAME;
    case CNIFTI_DT_COMPLEX256: return CNIFTI_DT_COMPLEX256_NAME;
    case CNIFTI_DT_RGBA32: return CNIFTI_DT_RGBA32_NAME;
    default: return NULL;
  }
}

/* Get the dt code from the dt name */
int32_t cnifti_dt_from_name(const char *dt_name) {
  if (dt_name == NULL) return -1;
  if (strcmp(dt_name, CNIFTI_DT_UNKNOWN_NAME) == 0) return CNIFTI_DT_UNKNOWN;
  if (strcmp(dt_name, CNIFTI_DT_BINARY_NAME) == 0) return CNIFTI_DT_BINARY;
  if (strcmp(dt_name, CNIFTI_DT_UINT8_NAME) == 0) return CNIFTI_DT_UINT8;
  if (strcmp(dt_name, CNIFTI_DT_INT16_NAME) == 0) return CNIFTI_DT_INT16;
  if (strcmp(dt_name, CNIFTI_DT_INT32_NAME) == 0) return CNIFTI_DT_INT32;
  if (strcmp(dt_name, CNIFTI_DT_FLOAT32_NAME) == 0) return CNIFTI_DT_FLOAT32;
  if (strcmp(dt_name, CNIFTI_DT_COMPLEX64_NAME) == 0) return CNIFTI_DT_COMPLEX64;
  if (strcmp(dt_name, CNIFTI_DT_FLOAT64_NAME) == 0) return CNIFTI_DT_FLOAT64;
  if (strcmp(dt_name, CNIFTI_DT_RGB24_NAME) == 0) return CNIFTI_DT_RGB24;
  if (strcmp(dt_name, CNIFTI_DT_INT8_NAME) == 0) return CNIFTI_DT_INT8;
  if (strcmp(dt_name, CNIFTI_DT_UNIT16_NAME) == 0) return CNIFTI_DT_UNIT16;
  if (strcmp(dt_name, CNIFTI_DT_UINT32_NAME) == 0) return CNIFTI_DT_UINT32;
  if (strcmp(dt_name, CNIFTI_DT_INT64_NAME) == 0) return CNIFTI_DT_INT64;
  if (strcmp(dt_name, CNIFTI_DT_UINT64_NAME) == 0) return CNIFTI_DT_UINT64;
  if (strcmp(dt_name, CNIFTI_DT_FLOAT128_NAME) == 0) return CNIFTI_DT_FLOAT128;
  if (strcmp(dt_name, CNIFTI_DT_COMPLEX128_NAME) == 0) return CNIFTI_DT_COMPLEX128;
  if (strcmp(dt_name, CNIFTI_DT_COMPLEX256_NAME) == 0) return CNIFTI_DT_COMPLEX256;
  if (strcmp(dt_name, CNIFTI_DT_RGBA32_NAME) == 0) return CNIFTI_DT_RGBA32;
  return -1;
}

/* Get the intent name */
const char *cnifti_intent_name(int32_t intent) {
  switch (intent) {
    case CNIFTI_INTENT_NONE: return CNIFTI_INTENT_NONE_NAME;
    case CNIFTI_INTENT_CORREL: return CNIFTI_INTENT_CORREL_NAME;
    case CNIFTI_INTENT_TTEST: return CNIFTI_INTENT_TTEST_NAME;
    case CNIFTI_INTENT_FTEST: return CNIFTI_INTENT_FTEST_NAME;
    case CNIFTI_INTENT_ZSCORE: return CNIFTI_INTENT_ZSCORE_NAME;
    case CNIFTI_INTENT_CHISQ: return CNIFTI_INTENT_CHISQ_NAME;
    case CNIFTI_INTENT_BETA: return CNIFTI_INTENT_BETA_NAME;
    case CNIFTI_INTENT_BINOM: return CNIFTI_INTENT_BINOM_NAME;
    case CNIFTI_INTENT_GAMMA: return CNIFTI_INTENT_GAMMA_NAME;
    case CNIFTI_INTENT_POISSON: return CNIFTI_INTENT_POISSON_NAME;
    case CNIFTI_INTENT_NORMAL: return CNIFTI_INTENT_NORMAL_NAME;
    case CNIFTI_INTENT_FTEST_NONC: return CNIFTI_INTENT_FTEST_NONC_NAME;
    case CNIFTI_INTENT_CHISQ_NONC: return CNIFTI_INTENT_CHISQ_NONC_NAME;
    case CNIFTI_INTENT_LOGISTIC: return CNIFTI_INTENT_LOGISTIC_NAME;
    case CNIFTI_INTENT_LAPLACE: return CNIFTI_INTENT_LAPLACE_NAME;
    case CNIFTI_INTENT_UNIFORM: return CNIFTI_INTENT_UNIFORM_NAME;
    case CNIFTI_INTENT_TTEST_NONC: return CNIFTI_INTENT_TTEST_NONC_NAME;
    case CNIFTI_INTENT_WEIBULL: return CNIFTI_INTENT_WEIBULL_NAME;
    case CNIFTI_INTENT_CHI: return CNIFTI_INTENT_CHI_NAME;
    case CNIFTI_INTENT_INVGAUSS: return CNIFTI_INTENT_INVGAUSS_NAME;
    case CNIFTI_INTENT_EXTVAL: return CNIFTI_INTENT_EXTVAL_NAME;
    case CNIFTI_INTENT_PVAL: return CNIFTI_INTENT_PVAL_NAME;
    case CNIFTI_INTENT_LOGPVAL: return CNIFTI_INTENT_LOGPVAL_NAME;
    case CNIFTI_INTENT_LOG10PVAL: return CNIFTI_INTENT_LOG10PVAL_NAME;
    case CNIFTI_INTENT_ESTIMATE: return CNIFTI_INTENT_ESTIMATE_NAME;
    case CNIFTI_INTENT_LABEL: return CNIFTI_INTENT_LABEL_NAME;
    case CNIFTI_INTENT_NEURONAME: return CNIFTI_INTENT_NEURONAME_NAME;
    case CNIFTI_INTENT_GENMATRIX: return CNIFTI_INTENT_GENMATRIX_NAME;
    case CNIFTI_INTENT_SYMMATRIX: return CNIFTI_INTENT_SYMMATRIX_NAME;
    case CNIFTI_INTENT_DISPVECT: return CNIFTI_INTENT_DISPVECT_NAME;
    case CNIFTI_INTENT_VECTOR: return CNIFTI_INTENT_VECTOR_NAME;
    case CNIFTI_INTENT_POINTSET: return CNIFTI_INTENT_POINTSET_NAME;
    case CNIFTI_INTENT_TRIANGLE: return CNIFTI_INTENT_TRIANGLE_NAME;
    case CNIFTI_INTENT_QUATERNION: return CNIFTI_INTENT_QUATERNION_NAME;
    case CNIFTI_INTENT_DIMLESS: return CNIFTI_INTENT_DIMLESS_NAME;
    case CNIFTI_INTENT_TIME_SERIES: return CNIFTI_INTENT_TIME_SERIES_NAME;
    case CNIFTI_INTENT_NODE_INDEX: return CNIFTI_INTENT_NODE_INDEX_NAME;
    case CNIFTI_INTENT_RGB_VECTOR: return CNIFTI_INTENT_RGB_VECTOR_NAME;
    case CNIFTI_INTENT_RGBA_VECTOR: return CNIFTI_INTENT_RGBA_VECTOR_NAME;
    case CNIFTI_INTENT_SHAPE: return CNIFTI_INTENT_SHAPE_NAME;
    case CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD: return CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_NAME;
    case CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS: return CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_NAME;
    case CNIFTI_INTENT_FSL_DCT_COEFFICIENTS: return CNIFTI_INTENT_FSL_DCT_COEFFICIENTS_NAME;
    case CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS: return CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_NAME;
    case CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS: return CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_NAME;
    case CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS: return CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_NAME;
    case CNIFTI_INTENT_FSL_TOPUP_FIELD: return CNIFTI_INTENT_FSL_TOPUP_FIELD_NAME;
    default: return NULL;
  }
}

/* Get the intent code from the intent name */
int32_t cnifti_intent_from_name(const char *intent_name) {
  if (intent_name == NULL) return -1;
  if (strcmp(intent_name, CNIFTI_INTENT_NONE_NAME) == 0) return CNIFTI_INTENT_NONE;
  if (strcmp(intent_name, CNIFTI_INTENT_CORREL_NAME) == 0) return CNIFTI_INTENT_CORREL;
  if (strcmp(intent_name, CNIFTI_INTENT_TTEST_NAME) == 0) return CNIFTI_INTENT_TTEST;
  if (strcmp(intent_name, CNIFTI_INTENT_FTEST_NAME) == 0) return CNIFTI_INTENT_FTEST;
  if (strcmp(intent_name, CNIFTI_INTENT_ZSCORE_NAME) == 0) return CNIFTI_INTENT_ZSCORE;
  if (strcmp(intent_name, CNIFTI_INTENT_CHISQ_NAME) == 0) return CNIFTI_INTENT_CHISQ;
  if (strcmp(intent_name, CNIFTI_INTENT_BETA_NAME) == 0) return CNIFTI_INTENT_BETA;
  if (strcmp(intent_name, CNIFTI_INTENT_BINOM_NAME) == 0) return CNIFTI_INTENT_BINOM;
  if (strcmp(intent_name, CNIFTI_INTENT_GAMMA_NAME) == 0) return CNIFTI_INTENT_GAMMA;
  if (strcmp(intent_name, CNIFTI_INTENT_POISSON_NAME) == 0) return CNIFTI_INTENT_POISSON;
  if (strcmp(intent_name, CNIFTI_INTENT_NORMAL_NAME) == 0) return CNIFTI_INTENT_NORMAL;
  if (strcmp(intent_name, CNIFTI_INTENT_FTEST_NONC_NAME) == 0) return CNIFTI_INTENT_FTEST_NONC;
  if (strcmp(intent_name, CNIFTI_INTENT_CHISQ_NONC_NAME) == 0) return CNIFTI_INTENT_CHISQ_NONC;
  if (strcmp(intent_name, CNIFTI_INTENT_LOGISTIC_NAME) == 0) return CNIFTI_INTENT_LOGISTIC;
  if (strcmp(intent_name, CNIFTI_INTENT_LAPLACE_NAME) == 0) return CNIFTI_INTENT_LAPLACE;
  if (strcmp(intent_name, CNIFTI_INTENT_UNIFORM_NAME) == 0) return CNIFTI_INTENT_UNIFORM;
  if (strcmp(intent_name, CNIFTI_INTENT_TTEST_NONC_NAME) == 0) return CNIFTI_INTENT_TTEST_NONC;
  if (strcmp(intent_name, CNIFTI_INTENT_WEIBULL_NAME) == 0) return CNIFTI_INTENT_WEIBULL;
  if (strcmp(intent_name, CNIFTI_INTENT_CHI_NAME) == 0) return CNIFTI_INTENT_CHI;
  if (strcmp(intent_name, CNIFTI_INTENT_INVGAUSS_NAME) == 0) return CNIFTI_INTENT_INVGAUSS;
  if (strcmp(intent_name, CNIFTI_INTENT_EXTVAL_NAME) == 0) return CNIFTI_INTENT_EXTVAL;
  if (strcmp(intent_name, CNIFTI_INTENT_PVAL_NAME) == 0) return CNIFTI_INTENT_PVAL;
  if (strcmp(intent_name, CNIFTI_INTENT_LOGPVAL_NAME) == 0) return CNIFTI_INTENT_LOGPVAL;
  if (strcmp(intent_name, CNIFTI_INTENT_LOG10PVAL_NAME) == 0) return CNIFTI_INTENT_LOG10PVAL;
  if (strcmp(intent_name, CNIFTI_INTENT_ESTIMATE_NAME) == 0) return CNIFTI_INTENT_ESTIMATE;
  if (strcmp(intent_name, CNIFTI_INTENT_LABEL_NAME) == 0) return CNIFTI_INTENT_LABEL;
  if (strcmp(intent_name, CNIFTI_INTENT_NEURONAME_NAME) == 0) return CNIFTI_INTENT_NEURONAME;
  if (strcmp(intent_name, CNIFTI_INTENT_GENMATRIX_NAME) == 0) return CNIFTI_INTENT_GENMATRIX;
  if (strcmp(intent_name, CNIFTI_INTENT_SYMMATRIX_NAME) == 0) return CNIFTI_INTENT_SYMMATRIX;
  if (strcmp(intent_name, CNIFTI_INTENT_DISPVECT_NAME) == 0) return CNIFTI_INTENT_DISPVECT;
  if (strcmp(intent_name, CNIFTI_INTENT_VECTOR_NAME) == 0) return CNIFTI_INTENT_VECTOR;
  if (strcmp(intent_name, CNIFTI_INTENT_POINTSET_NAME) == 0) return CNIFTI_INTENT_POINTSET;
  if (strcmp(intent_name, CNIFTI_INTENT_TRIANGLE_NAME) == 0) return CNIFTI_INTENT_TRIANGLE;
  if (strcmp(intent_name, CNIFTI_INTENT_QUATERNION_NAME) == 0) return CNIFTI_INTENT_QUATERNION;
  if (strcmp(intent_name, CNIFTI_INTENT_DIMLESS_NAME) == 0) return CNIFTI_INTENT_DIMLESS;
  if (strcmp(intent_name, CNIFTI_INTENT_TIME_SERIES_NAME) == 0) return CNIFTI_INTENT_TIME_SERIES;
  if (strcmp(intent_name, CNIFTI_INTENT_NODE_INDEX_NAME) == 0) return CNIFTI_INTENT_NODE_INDEX;
  if (strcmp(intent_name, CNIFTI_INTENT_RGB_VECTOR_NAME) == 0) return CNIFTI_INTENT_RGB_VECTOR;
  if (strcmp(intent_name, CNIFTI_INTENT_RGBA_VECTOR_NAME) == 0) return CNIFTI_INTENT_RGBA_VECTOR;
  if (strcmp(intent_name, CNIFTI_INTENT_SHAPE_NAME) == 0) return CNIFTI_INTENT_SHAPE;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_NAME) == 0) return CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_NAME) == 0) return CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_DCT_COEFFICIENTS_NAME) == 0) return CNIFTI_INTENT_FSL_DCT_COEFFICIENTS;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_NAME) == 0) return CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_NAME) == 0) return CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_NAME) == 0) return CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS;
  if (strcmp(intent_name, CNIFTI_INTENT_FSL_TOPUP_FIELD_NAME) == 0) return CNIFTI_INTENT_FSL_TOPUP_FIELD;
  return -1;
}

/* Get the xform name */
const char *cnifti_xform_name(int32_t xform) {
  switch (xform) {
    case CNIFTI_XFORM_UNKNOWN: return CNIFTI_XFORM_UNKNOWN_NAME;
    case CNIFTI_XFORM_SCANNER_ANAT: return CNIFTI_XFORM_SCANNER_ANAT_NAME;
    case CNIFTI_XFORM_ALIGNED_ANAT: return CNIFTI_XFORM_ALIGNED_ANAT_NAME;
    case CNIFTI_XFORM_TALAIRACH: return CNIFTI_XFORM_TALAIRACH_NAME;
    case CNIFTI_XFORM_MNI_152: return CNIFTI_XFORM_MNI_152_NAME;
    case CNIFTI_XFORM_TEMPLATE_OTHER: return CNIFTI_XFORM_TEMPLATE_OTHER_NAME;
    default: return NULL;
  }
}

/* Get the xform code from the xform name */
int32_t cnifti_xform_from_name(const char *xform_name) {
  if (xform_name == NULL) return -1;
  if (strcmp(xform_name, CNIFTI_XFORM_UNKNOWN_NAME) == 0) return CNIFTI_XFORM_UNKNOWN;
  if (strcmp(xform_name, CNIFTI_XFORM_SCANNER_ANAT_NAME) == 0) return CNIFTI_XFORM_SCANNER_ANAT;
  if (strcmp(xform_name, CNIFTI_XFORM_ALIGNED_ANAT_NAME) == 0) return CNIFTI_XFORM_ALIGNED_ANAT;
  if (strcmp(xform_name, CNIFTI_XFORM_TALAIRACH_NAME) == 0) return CNIFTI_XFORM_TALAIRACH;
  if (strcmp(xform_name, CNIFTI_XFORM_MNI_152_NAME) == 0) return CNIFTI_XFORM_MNI_152;
  if (strcmp(xform_name, CNIFTI_XFORM_TEMPLATE_OTHER_NAME) == 0) return CNIFTI_XFORM_TEMPLATE_OTHER;
  return -1;
}

/* Get the units name */
const char *cnifti_units_name(int32_t units) {
  switch (units) {
    case CNIFTI_UNITS_UNKNOWN: return CNIFTI_UNITS_UNKNOWN_NAME;
    case CNIFTI_UNITS_METER: return CNIFTI_UNITS_METER_NAME;
    case CNIFTI_UNITS_MM: return CNIFTI_UNITS_MM_NAME;
    case CNIFTI_UNITS_MICRON: return CNIFTI_UNITS_MICRON_NAME;
    case CNIFTI_UNITS_SEC: return CNIFTI_UNITS_SEC_NAME;
    case CNIFTI_UNITS_MSEC: return CNIFTI_UNITS_MSEC_NAME;
    case CNIFTI_UNITS_USEC: return CNIFTI_UNITS_USEC_NAME;
    case CNIFTI_UNITS_HZ: return CNIFTI_UNITS_HZ_NAME;
    case CNIFTI_UNITS_PPM: return CNIFTI_UNITS_PPM_NAME;
    case CNIFTI_UNITS_RADS: return CNIFTI_UNITS_RADS_NAME;
    default: return NULL;
  }
}

/* Get the units code from the units name */
int32_t cnifti_units_from_name(const char *units_name) {
  if (units_name == NULL) return -1;
  if (strcmp(units_name, CNIFTI_UNITS_UNKNOWN_NAME) == 0) return CNIFTI_UNITS_UNKNOWN;
  if (strcmp(units_name, CNIFTI_UNITS_METER_NAME) == 0) return CNIFTI_UNITS_METER;
  if (strcmp(units_name, CNIFTI_UNITS_MM_NAME) == 0) return CNIFTI_UNITS_MM;
  if (strcmp(units_name, CNIFTI_UNITS_MICRON_NAME) == 0) return CNIFTI_UNITS_MICRON;
  if (strcmp(units_name, CNIFTI_UNITS_SEC_NAME) == 0) return CNIFTI_UNITS_SEC;
  if (strcmp(units_name, CNIFTI_UNITS_MSEC_NAME) == 0) return CNIFTI_UNITS_MSEC;
  if (strcmp(units_name, CNIFTI_UNITS_USEC_NAME) == 0) return CNIFTI_UNITS_USEC;
  if (strcmp(units_name, CNIFTI_UNITS_HZ_NAME) == 0) return CNIFTI_UNITS_HZ;
  if (strcmp(units_name, CNIFTI_UNITS_PPM_NAME) == 0) return CNIFTI_UNITS_PPM;
  if (strcmp(units_name, CNIFTI_UNITS_RADS_NAME) == 0) return CNIFTI_UNITS_RADS;
  return -1;
}

/* Get the slice name */
const char *cnifti_slice_name(int32_t slice) {
  switch (slice) {
    case CNIFTI_SLICE_UNKNOWN: return CNIFTI_SLICE_UNKNOWN_NAME;
    case CNIFTI_SLICE_SEQ_INC: return CNIFTI_SLICE_SEQ_INC_NAME;
    case CNIFTI_SLICE_SEQ_DEC: return CNIFTI_SLICE_SEQ_DEC_NAME;
    case CNIFTI_SLICE_ALT_INC: return CNIFTI_SLICE_ALT_INC_NAME;
    case CNIFTI_SLICE_ALT_DEC: return CNIFTI_SLICE_ALT_DEC_NAME;
    case CNIFTI_SLICE_ALT_INC2: return CNIFTI_SLICE_ALT_INC2_NAME;
    case CNIFTI_SLICE_ALT_DEC2: return CNIFTI_SLICE_ALT_DEC2_NAME;
    default: return NULL;
  }
}

/* Get the slice code from the slice name */
int32_t cnifti_slice_from_name(const char *slice_name) {
  if (slice_name == NULL) return -1;
  if (strcmp(slice_name, CNIFTI_SLICE_UNKNOWN_NAME) == 0) return CNIFTI_SLICE_UNKNOWN;
  if (strcmp(slice_name, CNIFTI_SLICE_SEQ_INC_NAME) == 0) return CNIFTI_SLICE_SEQ_INC;
  if (strcmp(slice_name, CNIFTI_SLICE_SEQ_DEC_NAME) == 0) return CNIFTI_SLICE_SEQ_DEC;
  if (strcmp(slice_name, CNIFTI_SLICE_ALT_INC_NAME) == 0) return CNIFTI_SLICE_ALT_INC;
  if (strcmp(slice_name, CNIFTI_SLICE_ALT_DEC_NAME) == 0) return CNIFTI_SLICE_ALT_DEC;
  if (strcmp(slice_name, CNIFTI_SLICE_ALT_INC2_NAME) == 0) return CNIFTI_SLICE_ALT_INC2;
  if (strcmp(slice_name, CNIFTI_SLICE_ALT_DEC2_NAME) == 0) return CNIFTI_SLICE_ALT_DEC2;
  return -1;
}

/* Get the ecode name */
const char *cnifti_ecode_name(int32_t ecode) {
  switch (ecode) {
    case CNIFTI_ECODE_IGNORE: return CNIFTI_ECODE_IGNORE_NAME;
    case CNIFTI_ECODE_DICOM: return CNIFTI_ECODE_DICOM_NAME;
    case CNIFTI_ECODE_AFNI: return CNIFTI_ECODE_AFNI_NAME;
    case CNIFTI_ECODE_COMMENT: return CNIFTI_ECODE_COMMENT_NAME;
    case CNIFTI_ECODE_XCEDE: return CNIFTI_ECODE_XCEDE_NAME;
    case CNIFTI_ECODE_JIMDIMINFO: return CNIFTI_ECODE_JIMDIMINFO_NAME;
    case CNIFTI_ECODE_WORKFLOW_FWDS: return CNIFTI_ECODE_WORKFLOW_FWDS_NAME;
    case CNIFTI_ECODE_FREESURFER: return CNIFTI_ECODE_FREESURFER_NAME;
    case CNIFTI_ECODE_PYPICKLE: return CNIFTI_ECODE_PYPICKLE_NAME;
    case CNIFTI_ECODE_MIND_IDENT: return CNIFTI_ECODE_MIND_IDENT_NAME;
    case CNIFTI_ECODE_B_VALUE: return CNIFTI_ECODE_B_VALUE_NAME;
    case CNIFTI_ECODE_SPHERICAL_DIRECTION: return CNIFTI_ECODE_SPHERICAL_DIRECTION_NAME;
    case CNIFTI_ECODE_DT_COMPONENT: return CNIFTI_ECODE_DT_COMPONENT_NAME;
    case CNIFTI_ECODE_SHC_DEGREEORDER: return CNIFTI_ECODE_SHC_DEGREEORDER_NAME;
    case CNIFTI_ECODE_VOXBO: return CNIFTI_ECODE_VOXBO_NAME;
    case CNIFTI_ECODE_CARET: return CNIFTI_ECODE_CARET_NAME;
    case CNIFTI_ECODE_CIFTI: return CNIFTI_ECODE_CIFTI_NAME;
    case CNIFTI_ECODE_VARIABLE_FRAME_TIMING: return CNIFTI_ECODE_VARIABLE_FRAME_TIMING_NAME;
    case CNIFTI_ECODE_EVAL: return CNIFTI_ECODE_EVAL_NAME;
    case CNIFTI_ECODE_MATLAB: return CNIFTI_ECODE_MATLAB_NAME;
    case CNIFTI_ECODE_QUANTIPHYSE: return CNIFTI_ECODE_QUANTIPHYSE_NAME;
    case CNIFTI_ECODE_MRS: return CNIFTI_ECODE_MRS_NAME;
    default: return NULL;
  }
}

/* Get the ecode code from the ecode name */
int32_t cnifti_ecode_from_name(const char *ecode_name) {
  if (ecode_name == NULL) return -1;
  if (strcmp(ecode_name, CNIFTI_ECODE_IGNORE_NAME) == 0) return CNIFTI_ECODE_IGNORE;
  if (strcmp(ecode_name, CNIFTI_ECODE_DICOM_NAME) == 0) return CNIFTI_ECODE_DICOM;
  if (strcmp(ecode_name, CNIFTI_ECODE_AFNI_NAME) == 0) return CNIFTI_ECODE_AFNI;
  if (strcmp(ecode_name, CNIFTI_ECODE_COMMENT_NAME) == 0) return CNIFTI_ECODE_COMMENT;
  if (strcmp(ecode_name, CNIFTI_ECODE_XCEDE_NAME) == 0) return CNIFTI_ECODE_XCEDE;
  if (strcmp(ecode_name, CNIFTI_ECODE_JIMDIMINFO_NAME) == 0) return CNIFTI_ECODE_JIMDIMINFO;
  if (strcmp(ecode_name, CNIFTI_ECODE_WORKFLOW_FWDS_NAME) == 0) return CNIFTI_ECODE_WORKFLOW_FWDS;
  if (strcmp(ecode_name, CNIFTI_ECODE_FREESURFER_NAME) == 0) return CNIFTI_ECODE_FREESURFER;
  if (strcmp(ecode_name, CNIFTI_ECODE_PYPICKLE_NAME) == 0) return CNIFTI_ECODE_PYPICKLE;
  if (strcmp(ecode_name, CNIFTI_ECODE_MIND_IDENT_NAME) == 0) return CNIFTI_ECODE_MIND_IDENT;
  if (strcmp(ecode_name, CNIFTI_ECODE_B_VALUE_NAME) == 0) return CNIFTI_ECODE_B_VALUE;
  if (strcmp(ecode_name, CNIFTI_ECODE_SPHERICAL_DIRECTION_NAME) == 0) return CNIFTI_ECODE_SPHERICAL_DIRECTION;
  if (strcmp(ecode_name, CNIFTI_ECODE_DT_COMPONENT_NAME) == 0) return CNIFTI_ECODE_DT_COMPONENT;
  if (strcmp(ecode_name, CNIFTI_ECODE_SHC_DEGREEORDER_NAME) == 0) return CNIFTI_ECODE_SHC_DEGREEORDER;
  if (strcmp(ecode_name, CNIFTI_ECODE_VOXBO_NAME) == 0) return CNIFTI_ECODE_VOXBO;
  if (strcmp(ecode_name, CNIFTI_ECODE_CARET_NAME) == 0) return CNIFTI_ECODE_CARET;
  if (strcmp(ecode_name, CNIFTI_ECODE_CIFTI_NAME) == 0) return CNIFTI_ECODE_CIFTI;
  if (strcmp(ecode_name, CNIFTI_ECODE_VARIABLE_FRAME_TIMING_NAME) == 0) return CNIFTI_ECODE_VARIABLE_FRAME_TIMING;
  if (strcmp(ecode_name, CNIFTI_ECODE_EVAL_NAME) == 0) return CNIFTI_ECODE_EVAL;
  if (strcmp(ecode_name, CNIFTI_ECODE_MATLAB_NAME) == 0) return CNIFTI_ECODE_MATLAB;
  if (strcmp(ecode_name, CNIFTI_ECODE_QUANTIPHYSE_NAME) == 0) return CNIFTI_ECODE_QUANTIPHYSE;
  if (strcmp(ecode_name, CNIFTI_ECODE_MRS_NAME) == 0) return CNIFTI_ECODE_MRS;
  return -1;
}

/* Print n1_header */
void cnifti_n1_header_print(const cnifti_n1_header_t* t_n1_header) {
  const char *intent_intent_code = cnifti_intent_name(t_n1_header->intent_code);
  const char *dt_datatype = cnifti_dt_name(t_n1_header->datatype);
  const char *slice_slice_code = cnifti_slice_name(t_n1_header->slice_code);
  const char *xform_qform_code = cnifti_xform_name(t_n1_header->qform_code);
  const char *xform_sform_code = cnifti_xform_name(t_n1_header->sform_code);
  const char *units_spatial_units = cnifti_units_name(cnifti_n1_header_spatial_units(t_n1_header));
  const char *units_temporal_units = cnifti_units_name(cnifti_n1_header_temporal_units(t_n1_header));
  CNIFTI_PRINTF(
    "sizeof_hdr      : %i\n"
    "data_type       : \"%.10s\"\n"
    "db_name         : \"%.18s\"\n"
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
    "descrip         : \"%.80s\"\n"
    "aux_file        : \"%.24s\"\n"
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
    "intent_name     : \"%.16s\"\n"
    "magic           : \"%.4s\"\n"
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
    cnifti_n1_header_frequency_dim(t_n1_header),
    cnifti_n1_header_phase_dim(t_n1_header),
    cnifti_n1_header_slice_dim(t_n1_header),
    (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
    cnifti_n1_header_spatial_units(t_n1_header),
    (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
    cnifti_n1_header_temporal_units(t_n1_header)
  );

}

/* Print n2_header */
void cnifti_n2_header_print(const cnifti_n2_header_t* t_n2_header) {
  const char *dt_datatype = cnifti_dt_name(t_n2_header->datatype);
  const char *xform_qform_code = cnifti_xform_name(t_n2_header->qform_code);
  const char *xform_sform_code = cnifti_xform_name(t_n2_header->sform_code);
  const char *slice_slice_code = cnifti_slice_name(t_n2_header->slice_code);
  const char *intent_intent_code = cnifti_intent_name(t_n2_header->intent_code);
  const char *units_spatial_units = cnifti_units_name(cnifti_n2_header_spatial_units(t_n2_header));
  const char *units_temporal_units = cnifti_units_name(cnifti_n2_header_temporal_units(t_n2_header));
  CNIFTI_PRINTF(
    "sizeof_hdr      : %i\n"
    "magic           : \"%.4s\"\n"
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
    "descrip         : \"%.80s\"\n"
    "aux_file        : \"%.24s\"\n"
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
    "intent_name     : \"%.16s\"\n"
    "dim_info        : %i\n"
    "unused_str      : \"%.15s\"\n"
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
    cnifti_n2_header_frequency_dim(t_n2_header),
    cnifti_n2_header_phase_dim(t_n2_header),
    cnifti_n2_header_slice_dim(t_n2_header),
    (units_spatial_units == NULL ? "<non standard>" : units_spatial_units),
    cnifti_n2_header_spatial_units(t_n2_header),
    (units_temporal_units == NULL ? "<non standard>" : units_temporal_units),
    cnifti_n2_header_temporal_units(t_n2_header)
  );

}

/* Byte-swap n1_header */
void cnifti_n1_header_swap(cnifti_n1_header_t* t_n1_header) {
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

/* Byte-swap n2_header */
void cnifti_n2_header_swap(cnifti_n2_header_t* t_n2_header) {
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