// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-i32-fnda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int32NDArray.h"
#include "oct-inttypes.h"
#include "fNDArray.h"
SND_BIN_OPS (int32NDArray, octave_int32, FloatNDArray)
SND_CMP_OPS1 (octave_int32, , FloatNDArray, , int32_t)
SND_BOOL_OPS2 (octave_int32, FloatNDArray, octave_int32::zero, static_cast<float>(0.0))
