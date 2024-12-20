#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
int** createMatrix(size_t m, size_t n);
void destroyMatrix(int **t, size_t m, size_t n);
void readMatrix(int **t, size_t m, size_t n);
void writeMatrix(const int * const *t, size_t m, size_t n);
struct Matrix
{
  Matrix();
  ~Matrix();
  Matrix(size_t m, size_t n);
  Matrix(size_t m, size_t n, int value);
  Matrix(const Matrix &mtx);
  void read();
  void write() const;
  size_t getRows() const;
  size_t getColumns() const;
  void filling (int a);
  void transform(size_t m, size_t n);
  private:
    int **t_;
    size_t m_;
    size_t n_;
};
#endif
