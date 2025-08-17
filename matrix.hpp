#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <concepts>
#include <iostream>
#include <initializer_list>

namespace abramov
{
  template< class T >
  concept Integral = std::is_integral_v< T >;

  template< Integral T >
  struct Matrix
  {
    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    Matrix(size_t m, size_t n, int value);
    Matrix(size_t m, size_t n, const int *values);
    Matrix(std::initializer_list< std::initializer_list< T > > init);
    ~Matrix();
    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix) noexcept;
    Matrix &operator+=(const Matrix &other);
    Matrix operator+() const;
    Matrix &operator-=(const Matrix &other);
    Matrix operator-() const;
    Matrix &operator*=(const Matrix &other);
    template< class V >
    Matrix &operator*=(V scalar);
    bool operator==(const Matrix &other) const;
    Matrix power(size_t k) const;
    Matrix transpose() const;
    int determinant() const;
    int trace() const;
    int perm() const;
    int rank() const;
    int firstNorm() const;
    int infinityNorm() const;

    static Matrix horizontalConcat(const Matrix &lhs, const Matrix &rhs, T fill = 0);
    static Matrix verticalConcat(const Matrix &top, const Matrix &bottom, T fill = 0);
    static Matrix diagonalConcat(const Matrix &a, const Matrix &b, T fill = 0);
    static Matrix kroneckerProduct(const Matrix &a, const Matrix &b);

    std::ostream &print(std::ostream &out = std::cout) const;
    std::istream &read(std::istream &in = std::cin);

    friend Matrix operator+(Matrix lhs, const Matrix &rhs);
    friend Matrix operator-(Matrix lhs, const Matrix &rhs);
    friend Matrix operator*(Matrix lhs, const Matrix &rhs);
  private:
    T **data;
    size_t rows;
    size_t cols;

    static int **initMatrix(size_t m, size_t n);
    static void destroyMatrix(T **data, size_t m) noexcept;
    Matrix createMinor(size_t row, size_t col) const;
    void swap(Matrix &matrix) noexcept;
  };

  Matrix operator+(Matrix lhs, const Matrix &rhs);
  Matrix operator-(Matrix lhs, const Matrix &rhs);
  Matrix operator*(Matrix lhs, const Matrix &rhs);
  template< class V >
  Matrix operator*(Matrix lhs, V scalar);
  template< class V >
  Matrix operator*(V scalar, const Matrix &rhs);
}

#endif
