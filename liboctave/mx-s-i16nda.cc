// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-s-i16nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int16NDArray.h"
SND_BIN_OPS (int16NDArray, double, int16NDArray)
SND_CMP_OPS1 (double, , int16NDArray, , int16_t)
SND_BOOL_OPS2 (double, int16NDArray, 0.0, octave_int16::zero)
