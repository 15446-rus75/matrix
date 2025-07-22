#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <iostream>

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
    Matrix &operator*=(const Matrix &other);
    template< class T >
    Matrix &operator*=(T scalar);
    Matrix transpose();
    int determinant();
    Matrix horizontalConcat(const Matrix &lhs, const Matrix &rhs, int fill = 0);
    Matrix verticalConcat(const Matrix &top, const Matrix &bottom, int fill = 0);
    Matrix diagonalConcat(const Matrix &a, const Matrix &b, int fill = 0);
    Matrix kroneckerProduct(const Matrix &a, const Matrix &b);
    std::ostream &print(std::ostream &out = std::cout);
    std::istream &read(std::istream &in = std::cin);

    friend Matrix operator+(Matrix lhs, const Matrix &rhs);
    friend Matrix operator-(Matrix lhs, const Matrix &rhs);
    friend Matrix operator*(Matrix lhs, const Matrix &rhs);
  private:
    int **data;
    size_t rows;
    size_t cols;

    int **initMatrix(size_t m, size_t n);
    void destroyMatrix(int **data, size_t m) noexcept;
    Matrix createMinor(size_t row, size_t col);
    void swap(Matrix &matrix) noexcept;
  };

  Matrix operator+(Matrix lhs, const Matrix &rhs);
  Matrix operator-(Matrix lhs, const Matrix &rhs);
  Matrix operator*(Matrix lhs, const Matrix &rhs);
  template< class T >
  Matrix operator*(Matrix lhs, T scalar);
  template< class T >
  Matrix operator*(T scalar, const Matrix &rhs);
}
#endif
