// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-s-i8nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int8NDArray.h"
SND_BIN_OPS (int8NDArray, double, int8NDArray)
SND_CMP_OPS1 (double, , int8NDArray, , int8_t)
SND_BOOL_OPS2 (double, int8NDArray, 0.0, octave_int8::zero)
