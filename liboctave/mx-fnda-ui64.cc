// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-fnda-ui64.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint64NDArray.h"
#include "fNDArray.h"
#include "oct-inttypes.h"
NDS_BIN_OPS (uint64NDArray, FloatNDArray, octave_uint64)
NDS_CMP_OPS1 (FloatNDArray, , octave_uint64, , uint64_t)
NDS_BOOL_OPS2 (FloatNDArray, octave_uint64, static_cast<float>(0.0), octave_uint64::zero)