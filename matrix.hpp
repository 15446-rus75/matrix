#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>

namespace abramov
{
  struct Matrix
  {
    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    Matrix(size_t m, size_t n, int value);
    Matrix(size_t m, size_t n, const int *values);
    ~Matrix();
    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix) noexcept;
    Matrix &operator+=(const Matrix &other);
    Matrix operator+() const;
    Matrix &operator-=(const Matrix &other);
    Matrix operator-() const;

    friend Matrix operator+(Matrix lhs, const Matrix &rhs);
    friend Matrix operator-(Matrix lhs, const Matrix &rhs);
  private:
    int **data;
    size_t rows;
    size_t cols;

    int **initMatrix(size_t m, size_t n);
    void destroyMatrix(int **data, size_t m) noexcept;
    void swap(Matrix &matrix) noexcept;
  };

  Matrix operator+(Matrix lhs, const Matrix &rhs);
  Matrix operator-(Matrix lhs, const Matrix &rhs);
}
#endif
