#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <iostream>
#include <initializer_list>

namespace abramov
{
  struct Matrix
  {
    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    Matrix(size_t m, size_t n, int value);
    Matrix(size_t m, size_t n, const int *values);
    Matrix(std::initializer_list< std::initializer_list< int > > init);
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
    bool operator==(const Matrix &other);
    Matrix transpose();
    int determinant();
    static Matrix horizontalConcat(const Matrix &lhs, const Matrix &rhs, int fill = 0);
    static Matrix verticalConcat(const Matrix &top, const Matrix &bottom, int fill = 0);
    static Matrix diagonalConcat(const Matrix &a, const Matrix &b, int fill = 0);
    static Matrix kroneckerProduct(const Matrix &a, const Matrix &b);
    std::ostream &print(std::ostream &out = std::cout);
    std::istream &read(std::istream &in = std::cin);

    friend Matrix operator+(Matrix lhs, const Matrix &rhs);
    friend Matrix operator-(Matrix lhs, const Matrix &rhs);
    friend Matrix operator*(Matrix lhs, const Matrix &rhs);
  private:
    int **data;
    size_t rows;
    size_t cols;

    static int **initMatrix(size_t m, size_t n);
    static void destroyMatrix(int **data, size_t m) noexcept;
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

template< class T >
abramov::Matrix &abramov::Matrix::operator*=(T scalar)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      data[i][j] *= static_cast< int >(scalar);
    }
  }
  return *this;
}

template< class T >
abramov::Matrix abramov::operator*(Matrix lhs, T scalar)
{
  lhs *= scalar;
  return lhs;
}

template< class T >
abramov::Matrix abramov::operator*(T scalar, const Matrix &rhs)
{
  return rhs * scalar;
}
#endif
