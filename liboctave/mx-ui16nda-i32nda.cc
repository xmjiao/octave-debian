// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui16nda-i32nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint16NDArray.h"
#include "int32NDArray.h"
NDND_CMP_OPS (uint16NDArray, , int32NDArray, )
NDND_BOOL_OPS2 (uint16NDArray, int32NDArray, octave_uint16::zero, octave_int32::zero)
