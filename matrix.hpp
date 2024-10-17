#ifndef MATRIX_HPP
#define MATRIX_HPP
int** createMatrix(size_t m, size_t n);
void destroyMatrix(int **t, size_t m, size_t n);
void readMatrix(int **t, size_t m, size_t n);
void writeMatrix(const int * const *t, size_t m, size_t n);
#endif
