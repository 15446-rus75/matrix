#include "matrix.hpp"
#include <stdexcept>

abramov::Matrix::Matrix():
  data(nullptr),
  rows(0),
  cols(0)
{}

abramov::Matrix::Matrix(const Matrix &matrix):
  data(initMatrix(data, matrix.rows, matrix.cols)),
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
  data(initMatrix(data, m, n)),
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
  data(initMatrix(data, m, n)),
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

abramov::Matrix &abramov::Matrix::operator*=(const Matrix &other)
{
  if (cols != other.rows)
  {
    throw std::invalid_argument("Matrix dimensions do not agree\n");
  }
  Matrix res;
  initMatrix(res.data, rows, other.cols);
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < other.cols; ++ j)
    {
      for (size_t k = 0; k < cols; ++k)
      {
        res.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  destroyMatrix(data, rows);
  swap(res);
  return *this;
}

abramov::Matrix abramov::operator*(Matrix lhs, const Matrix &rhs)
{
  lhs *= rhs;
  return lhs;
}

abramov::Matrix abramov::Matrix::transpose()
{
  Matrix res;
  res.rows = cols;
  res.cols = rows;
  initMatrix(res.data, res.rows, res.cols);
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      res.data[j][i] = data[i][j];
    }
  }
  return res;
}

int abramov::Matrix::determinant()
{
  if (rows != cols)
  {
    throw std::logic_error("Matrix must be square to get determinant\n");
  }
  if (rows == 1)
  {
    return data[0][0];
  }
  if (rows == 2)
  {
    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
  }
  if (rows == 3)
  {
    int det = 0;
    det += data[0][0] * data[1][1] * data[2][2];
    det += data[0][1] * data[1][2] * data[2][0];
    det += data[0][2] * data[1][0] * data[2][1];
    det -= data[0][2] * data[1][1] * data[2][0];
    det -= data[0][1] * data[1][0] * data[2][2];
    det -= data[0][0] * data[1][2] * data[2][1];
    return det;
  }
  int det = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    Matrix minor = createMinor(0, j);
    int minor_det = minor.determinant();
    if (j % 2 == 0)
    {
      det += data[0][j] * minor_det;
    }
    else
    {
      det -= data[0][j] * minor_det;
    }
  }
  return det;
}

int **abramov::Matrix::initMatrix(int **data, size_t m, size_t n)
{
  data = new int*[m];
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

abramov::Matrix abramov::Matrix::createMinor(size_t row, size_t col)
{
  Matrix minor;
  minor.rows = rows - 1;
  minor.cols = cols - 1;
  initMatrix(minor.data, minor.rows, minor.cols);
  for (size_t i = 0, mi = 0; i < rows; ++i)
  {
    if (i == row)
    {
      continue;
    }
    for (size_t j = 0, mj = 0; j < cols; ++j)
    {
      if (j == col)
      {
        continue;
      }
      minor.data[mi][mj] = data[i][j];
      ++mj;
    }
    ++mi;
  }
  return minor;
}

void abramov::Matrix::swap(Matrix &matrix) noexcept
{
  std::swap(data, matrix.data);
  std::swap(rows, matrix.rows);
  std::swap(cols, matrix.cols);
}
