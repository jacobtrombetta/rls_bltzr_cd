/**
 * nvcc compiler issue with c++20 coroutines
 */
#include "kernel.h"
#include "coroutine.h"

__global__ void print_from_GPU() {
  printf("Printing from GPU\n");
}

void print() {
  print_from_GPU<<<1,1>>>();
  cudaDeviceSynchronize();
}
