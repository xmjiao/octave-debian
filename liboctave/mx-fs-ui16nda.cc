// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-fs-ui16nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint16NDArray.h"
SND_BIN_OPS (uint16NDArray, float, uint16NDArray)
SND_CMP_OPS1 (float, , uint16NDArray, , uint16_t)
SND_BOOL_OPS2 (float, uint16NDArray, static_cast<float>(0.0), octave_uint16::zero)