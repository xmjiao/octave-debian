// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-nda-i8nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int8NDArray.h"
#include "dNDArray.h"
NDND_BIN_OPS (int8NDArray, NDArray, int8NDArray)
NDND_CMP_OPS (NDArray, , int8NDArray, )
NDND_BOOL_OPS2 (NDArray, int8NDArray, 0.0, octave_int8::zero)
