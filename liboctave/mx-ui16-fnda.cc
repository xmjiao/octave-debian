// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui16-fnda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint16NDArray.h"
#include "oct-inttypes.h"
#include "fNDArray.h"
SND_BIN_OPS (uint16NDArray, octave_uint16, FloatNDArray)
SND_CMP_OPS1 (octave_uint16, , FloatNDArray, , uint16_t)
SND_BOOL_OPS2 (octave_uint16, FloatNDArray, octave_uint16::zero, static_cast<float>(0.0))