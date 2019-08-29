#ifndef TINKER_RT_CUDART_H_
#define TINKER_RT_CUDART_H_

#include "macro.h"
#include <cuda_runtime.h>
#include <cufft.h>

TINKER_NAMESPACE_BEGIN
typedef cudaStream_t Stream;

typedef cufftHandle FFTPlan;
TINKER_NAMESPACE_END

#endif