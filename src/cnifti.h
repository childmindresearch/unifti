/** @file cnifti.h */
               
#ifndef CNIFTI_HEADER_H
#define CNIFTI_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


#if __STDC_VERSION__ >= 201112L
#include <assert.h>
#define CNIFTI_STATIC_ASSERT(COND,MSG) static_assert(COND,MSG)
#else
#define CNIFTI_STATIC_ASSERT(COND,MSG)
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef CNIFTI_PRINTF
#include <stdio.h>
#define CNIFTI_PRINTF printf
#endif




/** @brief cnifti version */
#define CNIFTI_VERSION 1/* Begin: dt */

/** @brief dt::unknown */
#define CNIFTI_DT_UNKNOWN 0
/** @brief dt::binary */
#define CNIFTI_DT_BINARY 1
/** @brief dt::uint8 */
#define CNIFTI_DT_UINT8 2
/** @brief dt::int16 */
#define CNIFTI_DT_INT16 4
/** @brief dt::int32 */
#define CNIFTI_DT_INT32 8
/** @brief dt::float32 */
#define CNIFTI_DT_FLOAT32 16
/** @brief dt::complex64 */
#define CNIFTI_DT_COMPLEX64 32
/** @brief dt::float64 */
#define CNIFTI_DT_FLOAT64 64
/** @brief dt::rgb24 */
#define CNIFTI_DT_RGB24 128
/** @brief dt::int8 */
#define CNIFTI_DT_INT8 256
/** @brief dt::unit16 */
#define CNIFTI_DT_UNIT16 512
/** @brief dt::uint32 */
#define CNIFTI_DT_UINT32 768
/** @brief dt::int64 */
#define CNIFTI_DT_INT64 1024
/** @brief dt::uint64 */
#define CNIFTI_DT_UINT64 1280
/** @brief dt::float128 */
#define CNIFTI_DT_FLOAT128 1536
/** @brief dt::complex128 */
#define CNIFTI_DT_COMPLEX128 1792
/** @brief dt::complex256 */
#define CNIFTI_DT_COMPLEX256 2048
/** @brief dt::rgba32 */
#define CNIFTI_DT_RGBA32 2304
/** @brief dt unknown name */
#define CNIFTI_DT_UNKNOWN_NAME "unknown"
/** @brief dt binary name */
#define CNIFTI_DT_BINARY_NAME "binary"
/** @brief dt uint8 name */
#define CNIFTI_DT_UINT8_NAME "uint8"
/** @brief dt int16 name */
#define CNIFTI_DT_INT16_NAME "int16"
/** @brief dt int32 name */
#define CNIFTI_DT_INT32_NAME "int32"
/** @brief dt float32 name */
#define CNIFTI_DT_FLOAT32_NAME "float32"
/** @brief dt complex64 name */
#define CNIFTI_DT_COMPLEX64_NAME "complex64"
/** @brief dt float64 name */
#define CNIFTI_DT_FLOAT64_NAME "float64"
/** @brief dt rgb24 name */
#define CNIFTI_DT_RGB24_NAME "rgb24"
/** @brief dt int8 name */
#define CNIFTI_DT_INT8_NAME "int8"
/** @brief dt unit16 name */
#define CNIFTI_DT_UNIT16_NAME "unit16"
/** @brief dt uint32 name */
#define CNIFTI_DT_UINT32_NAME "uint32"
/** @brief dt int64 name */
#define CNIFTI_DT_INT64_NAME "int64"
/** @brief dt uint64 name */
#define CNIFTI_DT_UINT64_NAME "uint64"
/** @brief dt float128 name */
#define CNIFTI_DT_FLOAT128_NAME "float128"
/** @brief dt complex128 name */
#define CNIFTI_DT_COMPLEX128_NAME "complex128"
/** @brief dt complex256 name */
#define CNIFTI_DT_COMPLEX256_NAME "complex256"
/** @brief dt rgba32 name */
#define CNIFTI_DT_RGBA32_NAME "rgba32"

/* End: dt */

/* Begin: intent */

/** @brief intent::none */
#define CNIFTI_INTENT_NONE 0
/** @brief intent::correl */
#define CNIFTI_INTENT_CORREL 2
/** @brief intent::ttest */
#define CNIFTI_INTENT_TTEST 3
/** @brief intent::ftest */
#define CNIFTI_INTENT_FTEST 4
/** @brief intent::zscore */
#define CNIFTI_INTENT_ZSCORE 5
/** @brief intent::chisq */
#define CNIFTI_INTENT_CHISQ 6
/** @brief intent::beta */
#define CNIFTI_INTENT_BETA 7
/** @brief intent::binom */
#define CNIFTI_INTENT_BINOM 8
/** @brief intent::gamma */
#define CNIFTI_INTENT_GAMMA 9
/** @brief intent::poisson */
#define CNIFTI_INTENT_POISSON 10
/** @brief intent::normal */
#define CNIFTI_INTENT_NORMAL 11
/** @brief intent::ftest_nonc */
#define CNIFTI_INTENT_FTEST_NONC 12
/** @brief intent::chisq_nonc */
#define CNIFTI_INTENT_CHISQ_NONC 13
/** @brief intent::logistic */
#define CNIFTI_INTENT_LOGISTIC 14
/** @brief intent::laplace */
#define CNIFTI_INTENT_LAPLACE 15
/** @brief intent::uniform */
#define CNIFTI_INTENT_UNIFORM 16
/** @brief intent::ttest_nonc */
#define CNIFTI_INTENT_TTEST_NONC 17
/** @brief intent::weibull */
#define CNIFTI_INTENT_WEIBULL 18
/** @brief intent::chi */
#define CNIFTI_INTENT_CHI 19
/** @brief intent::invgauss */
#define CNIFTI_INTENT_INVGAUSS 20
/** @brief intent::extval */
#define CNIFTI_INTENT_EXTVAL 21
/** @brief intent::pval */
#define CNIFTI_INTENT_PVAL 22
/** @brief intent::logpval */
#define CNIFTI_INTENT_LOGPVAL 23
/** @brief intent::log10pval */
#define CNIFTI_INTENT_LOG10PVAL 24
/** @brief intent::estimate */
#define CNIFTI_INTENT_ESTIMATE 1001
/** @brief intent::label */
#define CNIFTI_INTENT_LABEL 1002
/** @brief intent::neuroname */
#define CNIFTI_INTENT_NEURONAME 1003
/** @brief intent::genmatrix */
#define CNIFTI_INTENT_GENMATRIX 1004
/** @brief intent::symmatrix */
#define CNIFTI_INTENT_SYMMATRIX 1005
/** @brief intent::dispvect */
#define CNIFTI_INTENT_DISPVECT 1006
/** @brief intent::vector */
#define CNIFTI_INTENT_VECTOR 1007
/** @brief intent::pointset */
#define CNIFTI_INTENT_POINTSET 1008
/** @brief intent::triangle */
#define CNIFTI_INTENT_TRIANGLE 1009
/** @brief intent::quaternion */
#define CNIFTI_INTENT_QUATERNION 1010
/** @brief intent::dimless */
#define CNIFTI_INTENT_DIMLESS 1011
/** @brief intent::time_series */
#define CNIFTI_INTENT_TIME_SERIES 2001
/** @brief intent::node_index */
#define CNIFTI_INTENT_NODE_INDEX 2002
/** @brief intent::rgb_vector */
#define CNIFTI_INTENT_RGB_VECTOR 2003
/** @brief intent::rgba_vector */
#define CNIFTI_INTENT_RGBA_VECTOR 2004
/** @brief intent::shape */
#define CNIFTI_INTENT_SHAPE 2005
/** @brief intent::fsl_fnirt_displacement_field */
#define CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD 2006
/** @brief intent::fsl_cubic_spline_coefficients */
#define CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS 2007
/** @brief intent::fsl_dct_coefficients */
#define CNIFTI_INTENT_FSL_DCT_COEFFICIENTS 2008
/** @brief intent::fsl_quadratic_spline_coefficients */
#define CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS 2009
/** @brief intent::fsl_topup_cubic_spline_coefficients */
#define CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS 2016
/** @brief intent::fsl_topup_quadratic_spline_coefficients */
#define CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS 2017
/** @brief intent::fsl_topup_field */
#define CNIFTI_INTENT_FSL_TOPUP_FIELD 2018
/** @brief intent none name */
#define CNIFTI_INTENT_NONE_NAME "none"
/** @brief intent correl name */
#define CNIFTI_INTENT_CORREL_NAME "correl"
/** @brief intent ttest name */
#define CNIFTI_INTENT_TTEST_NAME "ttest"
/** @brief intent ftest name */
#define CNIFTI_INTENT_FTEST_NAME "ftest"
/** @brief intent zscore name */
#define CNIFTI_INTENT_ZSCORE_NAME "zscore"
/** @brief intent chisq name */
#define CNIFTI_INTENT_CHISQ_NAME "chisq"
/** @brief intent beta name */
#define CNIFTI_INTENT_BETA_NAME "beta"
/** @brief intent binom name */
#define CNIFTI_INTENT_BINOM_NAME "binom"
/** @brief intent gamma name */
#define CNIFTI_INTENT_GAMMA_NAME "gamma"
/** @brief intent poisson name */
#define CNIFTI_INTENT_POISSON_NAME "poisson"
/** @brief intent normal name */
#define CNIFTI_INTENT_NORMAL_NAME "normal"
/** @brief intent ftest_nonc name */
#define CNIFTI_INTENT_FTEST_NONC_NAME "ftest_nonc"
/** @brief intent chisq_nonc name */
#define CNIFTI_INTENT_CHISQ_NONC_NAME "chisq_nonc"
/** @brief intent logistic name */
#define CNIFTI_INTENT_LOGISTIC_NAME "logistic"
/** @brief intent laplace name */
#define CNIFTI_INTENT_LAPLACE_NAME "laplace"
/** @brief intent uniform name */
#define CNIFTI_INTENT_UNIFORM_NAME "uniform"
/** @brief intent ttest_nonc name */
#define CNIFTI_INTENT_TTEST_NONC_NAME "ttest_nonc"
/** @brief intent weibull name */
#define CNIFTI_INTENT_WEIBULL_NAME "weibull"
/** @brief intent chi name */
#define CNIFTI_INTENT_CHI_NAME "chi"
/** @brief intent invgauss name */
#define CNIFTI_INTENT_INVGAUSS_NAME "invgauss"
/** @brief intent extval name */
#define CNIFTI_INTENT_EXTVAL_NAME "extval"
/** @brief intent pval name */
#define CNIFTI_INTENT_PVAL_NAME "pval"
/** @brief intent logpval name */
#define CNIFTI_INTENT_LOGPVAL_NAME "logpval"
/** @brief intent log10pval name */
#define CNIFTI_INTENT_LOG10PVAL_NAME "log10pval"
/** @brief intent estimate name */
#define CNIFTI_INTENT_ESTIMATE_NAME "estimate"
/** @brief intent label name */
#define CNIFTI_INTENT_LABEL_NAME "label"
/** @brief intent neuroname name */
#define CNIFTI_INTENT_NEURONAME_NAME "neuroname"
/** @brief intent genmatrix name */
#define CNIFTI_INTENT_GENMATRIX_NAME "genmatrix"
/** @brief intent symmatrix name */
#define CNIFTI_INTENT_SYMMATRIX_NAME "symmatrix"
/** @brief intent dispvect name */
#define CNIFTI_INTENT_DISPVECT_NAME "dispvect"
/** @brief intent vector name */
#define CNIFTI_INTENT_VECTOR_NAME "vector"
/** @brief intent pointset name */
#define CNIFTI_INTENT_POINTSET_NAME "pointset"
/** @brief intent triangle name */
#define CNIFTI_INTENT_TRIANGLE_NAME "triangle"
/** @brief intent quaternion name */
#define CNIFTI_INTENT_QUATERNION_NAME "quaternion"
/** @brief intent dimless name */
#define CNIFTI_INTENT_DIMLESS_NAME "dimless"
/** @brief intent time_series name */
#define CNIFTI_INTENT_TIME_SERIES_NAME "time_series"
/** @brief intent node_index name */
#define CNIFTI_INTENT_NODE_INDEX_NAME "node_index"
/** @brief intent rgb_vector name */
#define CNIFTI_INTENT_RGB_VECTOR_NAME "rgb_vector"
/** @brief intent rgba_vector name */
#define CNIFTI_INTENT_RGBA_VECTOR_NAME "rgba_vector"
/** @brief intent shape name */
#define CNIFTI_INTENT_SHAPE_NAME "shape"
/** @brief intent fsl_fnirt_displacement_field name */
#define CNIFTI_INTENT_FSL_FNIRT_DISPLACEMENT_FIELD_NAME "fsl_fnirt_displacement_field"
/** @brief intent fsl_cubic_spline_coefficients name */
#define CNIFTI_INTENT_FSL_CUBIC_SPLINE_COEFFICIENTS_NAME "fsl_cubic_spline_coefficients"
/** @brief intent fsl_dct_coefficients name */
#define CNIFTI_INTENT_FSL_DCT_COEFFICIENTS_NAME "fsl_dct_coefficients"
/** @brief intent fsl_quadratic_spline_coefficients name */
#define CNIFTI_INTENT_FSL_QUADRATIC_SPLINE_COEFFICIENTS_NAME "fsl_quadratic_spline_coefficients"
/** @brief intent fsl_topup_cubic_spline_coefficients name */
#define CNIFTI_INTENT_FSL_TOPUP_CUBIC_SPLINE_COEFFICIENTS_NAME "fsl_topup_cubic_spline_coefficients"
/** @brief intent fsl_topup_quadratic_spline_coefficients name */
#define CNIFTI_INTENT_FSL_TOPUP_QUADRATIC_SPLINE_COEFFICIENTS_NAME "fsl_topup_quadratic_spline_coefficients"
/** @brief intent fsl_topup_field name */
#define CNIFTI_INTENT_FSL_TOPUP_FIELD_NAME "fsl_topup_field"

/* End: intent */

/* Begin: xform */

/** @brief Arbitrary coordinates. (xform::unknown) */
#define CNIFTI_XFORM_UNKNOWN 0
/** @brief Scanner-based anatomical coordinates. (xform::scanner_anat) */
#define CNIFTI_XFORM_SCANNER_ANAT 1
/** @brief Coordinates aligned to another file's, or to the anatomical "truth" (with an arbitrary coordinate center). (xform::aligned_anat) */
#define CNIFTI_XFORM_ALIGNED_ANAT 2
/** @brief Coordinates aligned to the Talairach space. (xform::talairach) */
#define CNIFTI_XFORM_TALAIRACH 3
/** @brief Coordinates aligned to the MNI152 space. (xform::mni_152) */
#define CNIFTI_XFORM_MNI_152 4
/** @brief Coordinates aligned to some template that is not MNI152 or Talairach. (xform::template_other) */
#define CNIFTI_XFORM_TEMPLATE_OTHER 5
/** @brief xform unknown name */
#define CNIFTI_XFORM_UNKNOWN_NAME "unknown"
/** @brief xform scanner_anat name */
#define CNIFTI_XFORM_SCANNER_ANAT_NAME "scanner_anat"
/** @brief xform aligned_anat name */
#define CNIFTI_XFORM_ALIGNED_ANAT_NAME "aligned_anat"
/** @brief xform talairach name */
#define CNIFTI_XFORM_TALAIRACH_NAME "talairach"
/** @brief xform mni_152 name */
#define CNIFTI_XFORM_MNI_152_NAME "mni_152"
/** @brief xform template_other name */
#define CNIFTI_XFORM_TEMPLATE_OTHER_NAME "template_other"

/* End: xform */

/* Begin: units */

/** @brief Unknown units (units::unknown) */
#define CNIFTI_UNITS_UNKNOWN 0
/** @brief Meter (m) (units::meter) */
#define CNIFTI_UNITS_METER 1
/** @brief Millimeter (mm) (units::mm) */
#define CNIFTI_UNITS_MM 2
/** @brief Micron (um) (units::micron) */
#define CNIFTI_UNITS_MICRON 3
/** @brief Seconds (s) (units::sec) */
#define CNIFTI_UNITS_SEC 8
/** @brief Miliseconds (ms) (units::msec) */
#define CNIFTI_UNITS_MSEC 16
/** @brief Microseconds (us) (units::usec) */
#define CNIFTI_UNITS_USEC 24
/** @brief Hertz (Hz) (units::hz) */
#define CNIFTI_UNITS_HZ 32
/** @brief Parts-per-million (ppm) (units::ppm) */
#define CNIFTI_UNITS_PPM 40
/** @brief Radians per second (rad/s) (units::rads) */
#define CNIFTI_UNITS_RADS 48
/** @brief units unknown name */
#define CNIFTI_UNITS_UNKNOWN_NAME "unknown"
/** @brief units meter name */
#define CNIFTI_UNITS_METER_NAME "meter"
/** @brief units mm name */
#define CNIFTI_UNITS_MM_NAME "mm"
/** @brief units micron name */
#define CNIFTI_UNITS_MICRON_NAME "micron"
/** @brief units sec name */
#define CNIFTI_UNITS_SEC_NAME "sec"
/** @brief units msec name */
#define CNIFTI_UNITS_MSEC_NAME "msec"
/** @brief units usec name */
#define CNIFTI_UNITS_USEC_NAME "usec"
/** @brief units hz name */
#define CNIFTI_UNITS_HZ_NAME "hz"
/** @brief units ppm name */
#define CNIFTI_UNITS_PPM_NAME "ppm"
/** @brief units rads name */
#define CNIFTI_UNITS_RADS_NAME "rads"

/* End: units */

/* Begin: slice */

/** @brief Slice order: Unknown (slice::unknown) */
#define CNIFTI_SLICE_UNKNOWN 0
/** @brief Slice order: Sequential, increasing (slice::seq_inc) */
#define CNIFTI_SLICE_SEQ_INC 1
/** @brief Slice order: Sequential, decreasing (slice::seq_dec) */
#define CNIFTI_SLICE_SEQ_DEC 2
/** @brief Slice order: Interleaved, increasing, starting at the first slice (slice::alt_inc) */
#define CNIFTI_SLICE_ALT_INC 3
/** @brief Slice order: Interleaved, decreasing, starting at the last slice (slice::alt_dec) */
#define CNIFTI_SLICE_ALT_DEC 4
/** @brief Slice order: Interleaved, increasing, starting at the second slice (slice::alt_inc2) */
#define CNIFTI_SLICE_ALT_INC2 5
/** @brief Slice order: Interleaved, decreasing, starting at the second to last slice (slice::alt_dec2) */
#define CNIFTI_SLICE_ALT_DEC2 6
/** @brief slice unknown name */
#define CNIFTI_SLICE_UNKNOWN_NAME "unknown"
/** @brief slice seq_inc name */
#define CNIFTI_SLICE_SEQ_INC_NAME "seq_inc"
/** @brief slice seq_dec name */
#define CNIFTI_SLICE_SEQ_DEC_NAME "seq_dec"
/** @brief slice alt_inc name */
#define CNIFTI_SLICE_ALT_INC_NAME "alt_inc"
/** @brief slice alt_dec name */
#define CNIFTI_SLICE_ALT_DEC_NAME "alt_dec"
/** @brief slice alt_inc2 name */
#define CNIFTI_SLICE_ALT_INC2_NAME "alt_inc2"
/** @brief slice alt_dec2 name */
#define CNIFTI_SLICE_ALT_DEC2_NAME "alt_dec2"

/* End: slice */

/* Begin: ecode */

/** @brief ecode::ignore */
#define CNIFTI_ECODE_IGNORE 0
/** @brief intended for raw DICOM attributes (ecode::dicom) */
#define CNIFTI_ECODE_DICOM 2
/**
 * @brief Robert W Cox: rwcox\@nih.gov
 * https://afni.nimh.nih.gov/afni
 *  (ecode::afni)
 */
#define CNIFTI_ECODE_AFNI 4
/** @brief plain ASCII text only (ecode::comment) */
#define CNIFTI_ECODE_COMMENT 6
/**
 * @brief David B Keator: dbkeator\@uci.edu
 * http://www.nbirn.net/Resources/Users/Applications/xcede/index.htm
 *  (ecode::xcede)
 */
#define CNIFTI_ECODE_XCEDE 8
/**
 * @brief Mark A Horsfield
 * mah5\@leicester.ac.uk
 *  (ecode::jimdiminfo)
 */
#define CNIFTI_ECODE_JIMDIMINFO 10
/**
 * @brief Kate Fissell: fissell\@pitt.edu
 * http://kraepelin.wpic.pitt.edu/~fissell/NIFTI_ECODE_WORKFLOW_FWDS/NIFTI_ECODE_WORKFLOW_FWDS.html
 *  (ecode::workflow_fwds)
 */
#define CNIFTI_ECODE_WORKFLOW_FWDS 12
/** @brief http://surfer.nmr.mgh.harvard.edu/ (ecode::freesurfer) */
#define CNIFTI_ECODE_FREESURFER 14
/** @brief embedded Python objects (ecode::pypickle) */
#define CNIFTI_ECODE_PYPICKLE 16
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::mind_ident)
 */
#define CNIFTI_ECODE_MIND_IDENT 18
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::b_value)
 */
#define CNIFTI_ECODE_B_VALUE 20
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::spherical_direction)
 */
#define CNIFTI_ECODE_SPHERICAL_DIRECTION 22
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::dt_component)
 */
#define CNIFTI_ECODE_DT_COMPONENT 24
/**
 * @brief LONI MiND codes: http://www.loni.ucla.edu/twiki/bin/view/Main/MiND
 * Vishal Patel: vishal.patel\@ucla.edu
 *  (ecode::shc_degreeorder)
 */
#define CNIFTI_ECODE_SHC_DEGREEORDER 26
/** @brief Dan Kimberg: www.voxbo.org (ecode::voxbo) */
#define CNIFTI_ECODE_VOXBO 28
/**
 * @brief John Harwell: john\@brainvis.wustl.edu
 * http://brainvis.wustl.edu/wiki/index.php/Caret:Documentation:CaretNiftiExtension
 *  (ecode::caret)
 */
#define CNIFTI_ECODE_CARET 30
/** @brief CIFTI-2_Main_FINAL_1March2014.pdf (ecode::cifti) */
#define CNIFTI_ECODE_CIFTI 32
/** @brief ecode::variable_frame_timing */
#define CNIFTI_ECODE_VARIABLE_FRAME_TIMING 34
/** @brief Munster University Hospital (ecode::eval) */
#define CNIFTI_ECODE_EVAL 38
/**
 * @brief MATLAB extension
 * http://www.mathworks.com/matlabcentral/fileexchange/42997-dicom-to-nifti-converter
 *  (ecode::matlab)
 */
#define CNIFTI_ECODE_MATLAB 40
/**
 * @brief Quantiphyse extension
 * https://quantiphyse.readthedocs.io/en/latest/advanced/nifti_extension.html
 *  (ecode::quantiphyse)
 */
#define CNIFTI_ECODE_QUANTIPHYSE 42
/**
 * @brief Magnetic Resonance Spectroscopy (MRS)
 *  (ecode::mrs)
 */
#define CNIFTI_ECODE_MRS 44
/** @brief ecode ignore name */
#define CNIFTI_ECODE_IGNORE_NAME "ignore"
/** @brief ecode dicom name */
#define CNIFTI_ECODE_DICOM_NAME "dicom"
/** @brief ecode afni name */
#define CNIFTI_ECODE_AFNI_NAME "afni"
/** @brief ecode comment name */
#define CNIFTI_ECODE_COMMENT_NAME "comment"
/** @brief ecode xcede name */
#define CNIFTI_ECODE_XCEDE_NAME "xcede"
/** @brief ecode jimdiminfo name */
#define CNIFTI_ECODE_JIMDIMINFO_NAME "jimdiminfo"
/** @brief ecode workflow_fwds name */
#define CNIFTI_ECODE_WORKFLOW_FWDS_NAME "workflow_fwds"
/** @brief ecode freesurfer name */
#define CNIFTI_ECODE_FREESURFER_NAME "freesurfer"
/** @brief ecode pypickle name */
#define CNIFTI_ECODE_PYPICKLE_NAME "pypickle"
/** @brief ecode mind_ident name */
#define CNIFTI_ECODE_MIND_IDENT_NAME "mind_ident"
/** @brief ecode b_value name */
#define CNIFTI_ECODE_B_VALUE_NAME "b_value"
/** @brief ecode spherical_direction name */
#define CNIFTI_ECODE_SPHERICAL_DIRECTION_NAME "spherical_direction"
/** @brief ecode dt_component name */
#define CNIFTI_ECODE_DT_COMPONENT_NAME "dt_component"
/** @brief ecode shc_degreeorder name */
#define CNIFTI_ECODE_SHC_DEGREEORDER_NAME "shc_degreeorder"
/** @brief ecode voxbo name */
#define CNIFTI_ECODE_VOXBO_NAME "voxbo"
/** @brief ecode caret name */
#define CNIFTI_ECODE_CARET_NAME "caret"
/** @brief ecode cifti name */
#define CNIFTI_ECODE_CIFTI_NAME "cifti"
/** @brief ecode variable_frame_timing name */
#define CNIFTI_ECODE_VARIABLE_FRAME_TIMING_NAME "variable_frame_timing"
/** @brief ecode eval name */
#define CNIFTI_ECODE_EVAL_NAME "eval"
/** @brief ecode matlab name */
#define CNIFTI_ECODE_MATLAB_NAME "matlab"
/** @brief ecode quantiphyse name */
#define CNIFTI_ECODE_QUANTIPHYSE_NAME "quantiphyse"
/** @brief ecode mrs name */
#define CNIFTI_ECODE_MRS_NAME "mrs"

/* End: ecode */

/* Datatype size */

/** @brief dt unknown size */
#define CNIFTI_DT_UNKNOWN_SIZE 0
/** @brief dt binary size */
#define CNIFTI_DT_BINARY_SIZE 0
/** @brief dt uint8 size */
#define CNIFTI_DT_UINT8_SIZE 1
/** @brief dt int16 size */
#define CNIFTI_DT_INT16_SIZE 2
/** @brief dt int32 size */
#define CNIFTI_DT_INT32_SIZE 4
/** @brief dt float32 size */
#define CNIFTI_DT_FLOAT32_SIZE 4
/** @brief dt complex64 size */
#define CNIFTI_DT_COMPLEX64_SIZE 8
/** @brief dt float64 size */
#define CNIFTI_DT_FLOAT64_SIZE 8
/** @brief dt rgb24 size */
#define CNIFTI_DT_RGB24_SIZE 3
/** @brief dt int8 size */
#define CNIFTI_DT_INT8_SIZE 1
/** @brief dt unit16 size */
#define CNIFTI_DT_UNIT16_SIZE 2
/** @brief dt uint32 size */
#define CNIFTI_DT_UINT32_SIZE 4
/** @brief dt int64 size */
#define CNIFTI_DT_INT64_SIZE 8
/** @brief dt uint64 size */
#define CNIFTI_DT_UINT64_SIZE 8
/** @brief dt float128 size */
#define CNIFTI_DT_FLOAT128_SIZE 16
/** @brief dt complex128 size */
#define CNIFTI_DT_COMPLEX128_SIZE 16
/** @brief dt complex256 size */
#define CNIFTI_DT_COMPLEX256_SIZE 32
/** @brief dt rgba32 size */
#define CNIFTI_DT_RGBA32_SIZE 4

/* Nifti headers */

typedef struct {
  /** @brief Must be 348. */
  int32_t sizeof_hdr;
  /** @brief Unused. */
  uint8_t data_type[10];
  /** @brief Unused. */
  uint8_t db_name[18];
  /** @brief Unused. */
  int32_t extents;
  /** @brief Unused. */
  int16_t session_error;
  /** @brief Unused. */
  int8_t regular;
  /** @brief MRI slice ordering. */
  int8_t dim_info;
  /** @brief Data array dimensions. */
  int16_t dim[8];
  /** @brief 1st intent parameter. */
  float intent_p1;
  /** @brief 2nd intent parameter. */
  float intent_p2;
  /** @brief 3rd intent parameter. */
  float intent_p3;
  /** @brief NIFTI_INTENT_* code. (enum: `CNIFTI_INTENT_*`) */
  int16_t intent_code;
  /** @brief Defines data type. (enum: `CNIFTI_DT_*`) */
  int16_t datatype;
  /** @brief Number bits/voxel. */
  int16_t bitpix;
  /** @brief First slice index. */
  int16_t slice_start;
  /** @brief Grid spacings. */
  float pixdim[8];
  /** @brief Offset into .nii file */
  float vox_offset;
  /** @brief Data scaling: slope. */
  float scl_slope;
  /** @brief Data scaling: offset. */
  float scl_inter;
  /** @brief Last slice index. */
  int16_t slice_end;
  /** @brief Slice timing order. (enum: `CNIFTI_SLICE_*`) */
  int8_t slice_code;
  /** @brief Units of pixdim[1..4] */
  int8_t xyzt_units;
  /** @brief Max display intensity. */
  float cal_max;
  /** @brief Min display intensity. */
  float cal_min;
  /** @brief Time for 1 slice. */
  float slice_duration;
  /** @brief Time axis shift. */
  float toffset;
  /** @brief Unused. */
  int32_t glmax;
  /** @brief Unused. */
  int32_t glmin;
  /** @brief Any text you like. */
  uint8_t descrip[80];
  /** @brief Auxiliary filename. */
  uint8_t aux_file[24];
  /** @brief NIFTI_XFORM_* code. (enum: `CNIFTI_XFORM_*`) */
  int16_t qform_code;
  /** @brief NIFTI_XFORM_* code. (enum: `CNIFTI_XFORM_*`) */
  int16_t sform_code;
  /** @brief Quaternion b param. */
  float quatern_b;
  /** @brief Quaternion c param. */
  float quatern_c;
  /** @brief Quaternion d param. */
  float quatern_d;
  /** @brief Quaternion x param. */
  float qoffset_x;
  /** @brief Quaternion y param. */
  float qoffset_y;
  /** @brief Quaternion z param. */
  float qoffset_z;
  /** @brief 1st row affine transform. */
  float srow_x[4];
  /** @brief 2nd row affine transform. */
  float srow_y[4];
  /** @brief 3rd row affine transform. */
  float srow_z[4];
  /** @brief 'name' or meaning of data. */
  uint8_t intent_name[16];
  /** @brief MUST be "ni1\\0" or "n+1\\0". */
  uint8_t magic[4];
} cnifti_n1_header_t;

/* Computed n1_header fields */

/** @brief frequency_dim computed header field */
inline int32_t cnifti_n1_header_frequency_dim(const cnifti_n1_header_t *t_n1_header) { return t_n1_header->dim_info & 3; }

/** @brief phase_dim computed header field */
inline int32_t cnifti_n1_header_phase_dim(const cnifti_n1_header_t *t_n1_header) { return t_n1_header->dim_info >> 2 & 3; }

/** @brief slice_dim computed header field */
inline int32_t cnifti_n1_header_slice_dim(const cnifti_n1_header_t *t_n1_header) { return t_n1_header->dim_info >> 4 & 3; }

/** @brief spatial_units computed header field */
inline int32_t cnifti_n1_header_spatial_units(const cnifti_n1_header_t *t_n1_header) { return t_n1_header->xyzt_units & 7; }

/** @brief temporal_units computed header field */
inline int32_t cnifti_n1_header_temporal_units(const cnifti_n1_header_t *t_n1_header) { return t_n1_header->xyzt_units & 56; }

CNIFTI_STATIC_ASSERT(sizeof(cnifti_n1_header_t) == 348, "nifti1 header size is not 348 bytes");
// Disable alignment for this struct
#pragma pack(push, 1)
typedef struct {
  /** @brief Must be 540. */
  int32_t sizeof_hdr;
  /** @brief MUST be 'ni2\0' or 'n+2\0'. */
  uint8_t magic[4];
  /** @brief MUST be 0D 0A 1A 0A. */
  int8_t magic2[4];
  /** @brief Defines data type. (enum: `CNIFTI_DT_*`) */
  int16_t datatype;
  /** @brief Number bits/voxel. */
  int16_t bitpix;
  /** @brief Data array dimensions. */
  int64_t dim[8];
  /** @brief 1st intent parameter. */
  double intent_p1;
  /** @brief 2nd intent parameter. */
  double intent_p2;
  /** @brief 3rd intent parameter. */
  double intent_p3;
  /** @brief Grid spacings. */
  double pixdim[8];
  /** @brief Offset into .nii file */
  int64_t vox_offset;
  /** @brief Data scaling: slope. */
  double scl_slope;
  /** @brief Data scaling: offset. */
  double scl_inter;
  /** @brief Max display intensity. */
  double cal_max;
  /** @brief Min display intensity. */
  double cal_min;
  /** @brief Time for 1 slice. */
  double slice_duration;
  /** @brief Time axis shift. */
  double toffset;
  /** @brief First slice index. */
  int64_t slice_start;
  /** @brief Last slice index. */
  int64_t slice_end;
  /** @brief Any text you like. */
  uint8_t descrip[80];
  /** @brief Auxiliary filename. */
  uint8_t aux_file[24];
  /** @brief NIFTI_XFORM_* code. (enum: `CNIFTI_XFORM_*`) */
  int32_t qform_code;
  /** @brief NIFTI_XFORM_* code. (enum: `CNIFTI_XFORM_*`) */
  int32_t sform_code;
  /** @brief Quaternion b param. */
  double quatern_b;
  /** @brief Quaternion c param. */
  double quatern_c;
  /** @brief Quaternion d param. */
  double quatern_d;
  /** @brief Quaternion x param. */
  double qoffset_x;
  /** @brief Quaternion y param. */
  double qoffset_y;
  /** @brief Quaternion z param. */
  double qoffset_z;
  /** @brief 1st row affine transform. */
  double srow_x[4];
  /** @brief 2nd row affine transform. */
  double srow_y[4];
  /** @brief 3rd row affine transform. */
  double srow_z[4];
  /** @brief Slice timing order. (enum: `CNIFTI_SLICE_*`) */
  int32_t slice_code;
  /** @brief Units of pixdim[1..4] */
  int32_t xyzt_units;
  /** @brief NIFTI_INTENT_* code. (enum: `CNIFTI_INTENT_*`) */
  int32_t intent_code;
  /** @brief 'name' or meaning of data. */
  uint8_t intent_name[16];
  /** @brief MRI slice ordering. */
  int8_t dim_info;
  /** @brief unused, filled with \0 */
  uint8_t unused_str[15];
} cnifti_n2_header_t;
#pragma pack(pop)

/* Computed n2_header fields */

/** @brief frequency_dim computed header field */
inline int32_t cnifti_n2_header_frequency_dim(const cnifti_n2_header_t *t_n2_header) { return t_n2_header->dim_info & 3; }

/** @brief phase_dim computed header field */
inline int32_t cnifti_n2_header_phase_dim(const cnifti_n2_header_t *t_n2_header) { return t_n2_header->dim_info >> 2 & 3; }

/** @brief slice_dim computed header field */
inline int32_t cnifti_n2_header_slice_dim(const cnifti_n2_header_t *t_n2_header) { return t_n2_header->dim_info >> 4 & 3; }

/** @brief spatial_units computed header field */
inline int32_t cnifti_n2_header_spatial_units(const cnifti_n2_header_t *t_n2_header) { return t_n2_header->xyzt_units & 7; }

/** @brief temporal_units computed header field */
inline int32_t cnifti_n2_header_temporal_units(const cnifti_n2_header_t *t_n2_header) { return t_n2_header->xyzt_units & 56; }

CNIFTI_STATIC_ASSERT(sizeof(cnifti_n2_header_t) == 540, "nifti2 header size is not 540 bytes");
typedef struct {
  int8_t has_extension;
  uint8_t padding[3];
} cnifti_extension_indicator_t;

CNIFTI_STATIC_ASSERT(sizeof(cnifti_extension_indicator_t) == 4, "extension header size is not 4 bytes");
typedef struct {
  int32_t esize;
  int32_t ecode;
} cnifti_extension_header_t;

CNIFTI_STATIC_ASSERT(sizeof(cnifti_extension_header_t) == 8, "extension header size is not 8 bytes");

/** @brief Nifti header union */
typedef union cnifti_header_t {
  cnifti_n1_header_t n1_header;
  cnifti_n2_header_t n2_header;
} cnifti_header_t;


/* Implementation */
#ifndef CNIFTI_HEADER_ONLY

/** @brief Get the datatype size in bytes */
int32_t cnifti_dt_size(int32_t dt);

/** @brief Get the dt name */
const char *cnifti_dt_name(int32_t dt);

/** @brief Get the dt code from the dt name */
int32_t cnifti_dt_from_name(const char *dt_name);

/** @brief Get the intent name */
const char *cnifti_intent_name(int32_t intent);

/** @brief Get the intent code from the intent name */
int32_t cnifti_intent_from_name(const char *intent_name);

/** @brief Get the xform name */
const char *cnifti_xform_name(int32_t xform);

/** @brief Get the xform code from the xform name */
int32_t cnifti_xform_from_name(const char *xform_name);

/** @brief Get the units name */
const char *cnifti_units_name(int32_t units);

/** @brief Get the units code from the units name */
int32_t cnifti_units_from_name(const char *units_name);

/** @brief Get the slice name */
const char *cnifti_slice_name(int32_t slice);

/** @brief Get the slice code from the slice name */
int32_t cnifti_slice_from_name(const char *slice_name);

/** @brief Get the ecode name */
const char *cnifti_ecode_name(int32_t ecode);

/** @brief Get the ecode code from the ecode name */
int32_t cnifti_ecode_from_name(const char *ecode_name);

/** @brief Print n1_header */
void cnifti_n1_header_print(const cnifti_n1_header_t* t_n1_header);

/** @brief Print n2_header */
void cnifti_n2_header_print(const cnifti_n2_header_t* t_n2_header);


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
}/** @brief Byte-swap n1_header */
void cnifti_n1_header_swap(cnifti_n1_header_t* t_n1_header);

/** @brief Byte-swap n2_header */
void cnifti_n2_header_swap(cnifti_n2_header_t* t_n2_header);


/** @brief Calculate n1_header data array size (in bytes). */
static inline int64_t cnifti_n1_header_array_size(const cnifti_n1_header_t* t_n1_header) {
  int64_t size = t_n1_header->bitpix / 8;
  for (int i = 0; i < t_n1_header->dim[0]; ++i) { size *= t_n1_header->dim[i+1]; }
  return size;
}
/** @brief Calculate n2_header data array size (in bytes). */
static inline int64_t cnifti_n2_header_array_size(const cnifti_n2_header_t* t_n2_header) {
  int64_t size = t_n2_header->bitpix / 8;
  for (int i = 0; i < t_n2_header->dim[0]; ++i) { size *= t_n2_header->dim[i+1]; }
  return size;
}
#endif /* CNIFTI_HEADER_ONLY */



#ifdef __cplusplus
}
#endif

#endif /* CNIFTI_HEADER_H */