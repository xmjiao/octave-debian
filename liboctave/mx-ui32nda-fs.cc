// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui32nda-fs.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint32NDArray.h"
NDS_BIN_OPS (uint32NDArray, uint32NDArray, float)
NDS_CMP_OPS1 (uint32NDArray, , float, , uint32_t)
NDS_BOOL_OPS2 (uint32NDArray, float, octave_uint32::zero, static_cast<float>(0.0))