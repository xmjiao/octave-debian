// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-i32nda-nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int32NDArray.h"
#include "dNDArray.h"
NDND_BIN_OPS (int32NDArray, int32NDArray, NDArray)
NDND_CMP_OPS (int32NDArray, , NDArray, )
NDND_BOOL_OPS2 (int32NDArray, NDArray, octave_int32::zero, 0.0)