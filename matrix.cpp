#include "matrix.hpp"
#include <stdexcept>

abramov::Matrix::Matrix():
  data(nullptr),
  rows(0),
  cols(0)
{}

abramov::Matrix::Matrix(const Matrix &matrix):
  data(initMatrix(matrix.rows, matrix.cols)),
  rows(matrix.rows),
  cols(matrix.cols)
{
  for (size_t m = 0; m < matrix.rows; ++m)
  {
    for (size_t n = 0; n < matrix.cols; ++n)
    {
      data[m][n] = matrix.data[m][n];
    }
  }
}

abramov::Matrix::Matrix(Matrix &&matrix) noexcept:
  data(matrix.data),
  rows(matrix.rows),
  cols(matrix.cols)
{
  matrix.data = nullptr;
  matrix.rows = 0;
  matrix.cols = 0;
}

abramov::Matrix::Matrix(size_t m, size_t n, int value):
  data(initMatrix(m, n)),
  rows(m),
  cols(n)
{
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      data[i][j] = value;
    }
  }
}

abramov::Matrix::Matrix(size_t m, size_t n, const int *values):
  data(initMatrix(m, n)),
  rows(m),
  cols(n)
{
  size_t count = 0;
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      data[i][j] = values[count++];
    }
  }
}

abramov::Matrix::~Matrix()
{
  destroyMatrix(data, rows);
}

abramov::Matrix &abramov::Matrix::operator=(const Matrix &matrix)
{
  Matrix tmp(matrix);
  swap(tmp);
  return *this;
}

abramov::Matrix &abramov::Matrix::operator=(Matrix &&matrix) noexcept
{
  Matrix tmp(matrix);
  swap(tmp);
  return *this;
}

abramov::Matrix &abramov::Matrix::operator+=(const Matrix &matrix)
{
  if (rows != matrix.rows || cols != matrix.cols)
  {
    throw std::invalid_argument("Matrix dimensions do not agree\n");
  }
  if (!matrix.data)
  {
    throw std::invalid_argument("Invalid matrix\n");
  }
  for (size_t i = 0; i < matrix.rows; ++i)
  {
    for (size_t j = 0; j < matrix.cols; ++i)
    {
      data[i][j] += matrix.data[i][j];
    }
  }
  return *this;
}

abramov::Matrix abramov::operator+(Matrix lhs, const Matrix &rhs)
{
  lhs += rhs;
  return lhs;
}

abramov::Matrix abramov::Matrix::operator+() const
{
  return *this;
}

abramov::Matrix &abramov::Matrix::operator-=(const Matrix &matrix)
{
  if (rows != matrix.rows || cols != matrix.cols)
  {
    throw std::invalid_argument("Matrix dimensions do not agree\n");
  }
  if (!matrix.data)
  {
    throw std::invalid_argument("Invalid matrix\n");
  }
  for (size_t i = 0; i < matrix.rows; ++i)
  {
    for (size_t j = 0; j < matrix.cols; ++j)
    {
      data[i][j] -= matrix.data[i][j];
    }
  }
  return *this;
}

abramov::Matrix abramov::operator-(Matrix lhs, const Matrix &rhs)
{
  lhs -= rhs;
  return lhs;
}

abramov::Matrix abramov::Matrix::operator-() const
{
  Matrix res(*this);
  for (size_t i = 0; i < res.rows; ++i)
  {
    for (size_t j = 0; j < res.cols; ++j)
    {
      res.data[i][j] *= -1;
    }
  }
  return res;
}

int **abramov::Matrix::initMatrix(size_t m, size_t n)
{
  int **data = new int*[m];
  size_t created = 0;
  try
  {
    for (; created < m; ++created)
    {
      data[created] = new int [n];
    }
  }
  catch (const std::bad_alloc &)
  {
    destroyMatrix(data, created);
    throw;
  }
  return data;
}

void abramov::Matrix::destroyMatrix(int **data, size_t m) noexcept
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] data[i];
  }
  delete[] data;
}

void abramov::Matrix::swap(Matrix &matrix) noexcept
{
  std::swap(data, matrix.data);
  std::swap(rows, matrix.rows);
  std::swap(cols, matrix.cols);
}
