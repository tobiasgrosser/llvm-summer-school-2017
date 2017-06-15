void vector_addition(float *A, float *B) {
  for (long i = 0; i < 1024; i++)
    A[i] += B[i];
}
