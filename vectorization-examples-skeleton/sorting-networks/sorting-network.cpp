#include <stdlib.h>
#include <chrono>
#include <stdio.h>
#include <assert.h>

typedef double double8 __attribute__((ext_vector_type(8)));
typedef double double4 __attribute__((ext_vector_type(4)));
typedef double double2 __attribute__((ext_vector_type(2)));

double4 min(double4 A, double4 B) {
  return __builtin_ia32_minpd256(A, B);
}

double4 max(double4 A, double4 B) {
  return __builtin_ia32_maxpd256(A, B);
}

double2 min(double2 A, double2 B) {
  return __builtin_ia32_minpd(A, B);
}

double2 max(double2 A, double2 B) {
  return __builtin_ia32_maxpd(A, B);
}

double4 __attribute__ ((noinline)) sort(double4 A) {

double8 __attribute__ ((noinline)) sort(double8 A) {
}

void test(double4 A) {
  A = sort(A);
  printf("%f %f %f %f\n", A[0], A[1], A[2], A[3]);

  for (long i = 0; i < 4; i++)
    assert(A[i] == i);
}

void test(double8 A) {
  A = sort(A);
  printf("%f %f %f %f %f %f %f %f\n",
         A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7]);
  for (long i = 0; i < 8; i++)
    assert(A[i] == i);
}

int main() {
  double4 A;
  double8 B;

  A = { 0, 1, 2, 3};
  test(A);

  A = { 3, 2, 1, 0};
  test(A);

  A = { 3, 1, 2, 0};
  test(A);

  A = { 0, 1, 2, 3};
  test(A);

  A = { 0, 3, 2, 1};
  test(A);

  A = { 2, 3, 0, 1};
  test(A);

  B = { 0, 1, 2, 3, 4, 5, 6, 7};
  test(B);

  B = { 7, 6, 5, 4, 3, 2, 1, 0};
  test(B);

  B = { 0, 1, 2, 3, 7, 6, 5, 4};
  test(B);

  B = { 3, 2, 1, 0, 4, 5, 6, 7};
  test(B);
}
