// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-i32nda-i8nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int32NDArray.h"
#include "int8NDArray.h"
NDND_CMP_OPS (int32NDArray, , int8NDArray, )
NDND_BOOL_OPS2 (int32NDArray, int8NDArray, octave_int32::zero, octave_int8::zero)