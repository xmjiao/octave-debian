// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-m-cs.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "CMatrix.h"
#include "dMatrix.h"
#include "oct-cmplx.h"
MS_BIN_OPS (ComplexMatrix, Matrix, Complex)
MS_CMP_OPS (Matrix, , Complex, real)
MS_BOOL_OPS2 (Matrix, Complex, 0.0, 0.0)
