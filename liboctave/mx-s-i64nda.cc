// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-s-i64nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int64NDArray.h"
SND_BIN_OPS (int64NDArray, double, int64NDArray)
SND_CMP_OPS1 (double, , int64NDArray, , int64_t)
SND_BOOL_OPS2 (double, int64NDArray, 0.0, octave_int64::zero)
