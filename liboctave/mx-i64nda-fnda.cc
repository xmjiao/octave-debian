// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-i64nda-fnda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int64NDArray.h"
#include "fNDArray.h"
NDND_BIN_OPS (int64NDArray, int64NDArray, FloatNDArray)
NDND_CMP_OPS (int64NDArray, , FloatNDArray, )
NDND_BOOL_OPS2 (int64NDArray, FloatNDArray, octave_int64::zero, static_cast<float>(0.0))
