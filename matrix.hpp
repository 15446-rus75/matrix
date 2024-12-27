#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
int** createMatrix(size_t m, size_t n);
void destroyMatrix(int **t, size_t m, size_t n);
void readMatrix(int **t, size_t m, size_t n);
void writeMatrix(const int * const *t, size_t m, size_t n);

struct Matrix
{
  Matrix(size_t m, size_t n, int value);
  Matrix(size_t m, size_t n, const int *values);
private:
  int **data;
  size_t rows;
  size_t cols;
};
#endif
