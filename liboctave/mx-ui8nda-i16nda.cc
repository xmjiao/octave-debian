// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui8nda-i16nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint8NDArray.h"
#include "int16NDArray.h"
NDND_CMP_OPS (uint8NDArray, , int16NDArray, )
NDND_BOOL_OPS2 (uint8NDArray, int16NDArray, octave_uint8::zero, octave_int16::zero)