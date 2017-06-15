#include <stdlib.h>
#include <chrono>
#include <stdio.h>

#define N (1024 * 1024 * 1024)

void __attribute__ ((noinline)) vector_addition(float *A, float *B) {
  // We assume that N is a multiple of 4.
  for (long i = 0; i < N; i++)
    A[i] += B[i];
}

int main() {
  float *A = (float *) malloc(N * sizeof(float)); 
  float *B = (float *) malloc(N * sizeof(float)); 

  auto start = std::chrono::steady_clock::now();

  vector_addition(A, B);

  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
  printf("Time: %ld\n", duration.count());
}
