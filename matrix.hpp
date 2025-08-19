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
  struct Matrix;

  template< Integral T >
  Matrix< T > operator+(Matrix< T > lhs, const Matrix< T > &rhs);
  template< Integral T >
  Matrix< T > operator-(Matrix< T > lhs, const Matrix< T > &rhs);
  template< Integral T >
  Matrix< T > operator*(Matrix< T > lhs, const Matrix< T > &rhs);
  template< Integral T >
  Matrix< T > operator*(Matrix< T > lhs, T scalar);
  template< Integral T  >
  Matrix< T > operator*(T scalar, const Matrix< T > &rhs);

  template< Integral T >
  struct Matrix
  {
    friend Matrix< T > operator+<>(Matrix< T > lhs, const Matrix< T > &rhs);
    friend Matrix< T > operator-<>(Matrix< T > lhs, const Matrix< T > &rhs);
    friend Matrix< T > operator*<>(Matrix< T > lhs, const Matrix< T > &rhs);

    Matrix();
    Matrix(const Matrix< T > &matrix);
    Matrix(Matrix< T > &&matrix) noexcept;
    Matrix(size_t m, size_t n, int value);
    Matrix(size_t m, size_t n, const int *values);
    Matrix(std::initializer_list< std::initializer_list< T > > init);
    ~Matrix();
    Matrix< T > &operator=(const Matrix< T > &matrix);
    Matrix< T > &operator=(Matrix< T > &&matrix) noexcept;
    Matrix< T > &operator+=(const Matrix< T > &other);
    Matrix< T > operator+() const;
    Matrix< T > &operator-=(const Matrix< T > &other);
    Matrix< T > operator-() const;
    Matrix< T > &operator*=(const Matrix< T > &other);
    Matrix< T > &operator*=(T scalar);
    bool operator==(const Matrix< T > &other) const;
    Matrix< T > power(size_t k) const;
    Matrix< T > transpose() const;
    int determinant() const;
    int trace() const;
    int perm() const;
    int rank() const;
    int firstNorm() const;
    int infinityNorm() const;
    std::pair< double, Matrix< T > > inverse() const;

    static Matrix< T > horizontalConcat(const Matrix< T > &lhs, const Matrix< T > &rhs, T fill = 0);
    static Matrix< T > verticalConcat(const Matrix< T > &top, const Matrix< T > &bottom, T fill = 0);
    static Matrix< T > diagonalConcat(const Matrix< T > &a, const Matrix< T > &b, T fill = 0);
    static Matrix< T > kroneckerProduct(const Matrix< T > &a, const Matrix< T > &b);

    std::ostream &print(std::ostream &out = std::cout) const;
    std::istream &read(std::istream &in = std::cin);
  private:
    T **data;
    size_t rows;
    size_t cols;

    static T **initMatrix(size_t m, size_t n);
    static void destroyMatrix(T **data, size_t m) noexcept;
    Matrix< T > createMinor(size_t row, size_t col) const;
    void swap(Matrix< T > &matrix) noexcept;
  };
}

template< abramov::Integral T >
abramov::Matrix< T >::Matrix():
  data(nullptr),
  rows(0),
  cols(0)
{}

template< abramov::Integral T >
abramov::Matrix< T >::Matrix(const Matrix< T > &matrix):
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

template< abramov::Integral T >
abramov::Matrix< T >::Matrix(Matrix< T > &&matrix) noexcept:
  data(matrix.data),
  rows(matrix.rows),
  cols(matrix.cols)
{
  matrix.data = nullptr;
  matrix.rows = 0;
  matrix.cols = 0;
}

template< abramov::Integral T >
abramov::Matrix< T >::Matrix(size_t m, size_t n, int value):
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

template< abramov::Integral T >
abramov::Matrix< T >::Matrix(size_t m, size_t n, const int *values):
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

template< abramov::Integral T >
abramov::Matrix< T >::Matrix(std::initializer_list< std::initializer_list< T > > init)
{
  rows = init.size();
  if (!rows)
  {
    cols = 0;
    data = nullptr;
    return;
  }
  cols = init.begin()->size();
  for (const auto &row : init)
  {
    if (row.size() != cols)
    {
      throw std::logic_error("Invalid matrix\n");
    }
  }
  data = initMatrix(rows, cols);
  size_t i = 0;
  for (const auto &row : init)
  {
    size_t j = 0;
    for (int val : row)
    {
      data[i][j] = val;
      ++j;
    }
    ++i;
  }
}

template< abramov::Integral T >
abramov::Matrix< T >::~Matrix()
{
  destroyMatrix(data, rows);
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator=(const Matrix< T > &matrix)
{
  Matrix< T > tmp(matrix);
  swap(tmp);
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator=(Matrix< T > &&matrix) noexcept
{
  Matrix< T > tmp(matrix);
  swap(tmp);
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator+=(const Matrix &matrix)
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
      data[i][j] += matrix.data[i][j];
    }
  }
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::operator+(Matrix< T > lhs, const Matrix< T > &rhs)
{
  lhs += rhs;
  return lhs;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::operator+() const
{
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator-=(const Matrix< T > &matrix)
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

template< abramov::Integral T >
abramov::Matrix< T > abramov::operator-(Matrix< T > lhs, const Matrix< T > &rhs)
{
  lhs -= rhs;
  return lhs;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::operator-() const
{
  Matrix< T > res(*this);
  for (size_t i = 0; i < res.rows; ++i)
  {
    for (size_t j = 0; j < res.cols; ++j)
    {
      res.data[i][j] *= -1;
    }
  }
  return res;
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator*=(const Matrix< T > &other)
{
  if (cols != other.rows)
  {
    throw std::invalid_argument("Matrix dimensions do not agree\n");
  }
  Matrix< T > res(rows,other.cols, 0);
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
  swap(res);
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > &abramov::Matrix< T >::operator*=(T scalar)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      data[i][j] *= scalar;
    }
  }
  return *this;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::operator*(Matrix< T > lhs, const Matrix< T > &rhs)
{
  lhs *= rhs;
  return lhs;
}

template< abramov::Integral T >
bool abramov::Matrix< T >::operator==(const Matrix< T > &other) const
{
  if (rows != other.rows || cols != other.cols)
  {
    return false;
  }
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (data[i][j] != other.data[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::power(size_t k) const
{
  if (rows != cols)
  {
    throw std::logic_error("Matrix must be square\n");
  }
  if (k == 0)
  {
    Matrix< T > res(3, 3, 0);
    for (size_t i = 0; i < 3; ++i)
    {
      res.data[i][i] = 1;
    }
    return res;
  }
  if (k == 1)
  {
    return Matrix(*this);
  }
  Matrix< T > res(*this);
  Matrix< T > temp(*this);
  size_t p = k - 1;
  while (p > 0)
  {
    if (p % 2 == 1)
    {
      res *= temp;
    }
    temp *= temp;
    p /= 2;
  }
  return res;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::transpose() const
{
  Matrix< T > res;
  res.rows = cols;
  res.cols = rows;
  res.data = initMatrix(res.rows, res.cols);
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      res.data[j][i] = data[i][j];
    }
  }
  return res;
}

template< abramov::Integral T >
int abramov::Matrix< T >::determinant() const
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
    Matrix< T > minor = createMinor(0, j);
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

template< abramov::Integral T >
int abramov::Matrix< T >::trace() const
{
  if (rows != cols)
  {
    throw std::logic_error("Matrix is not square\n");
  }
  int tr = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    tr += data[i][i];
  }
  return tr;
}

template< abramov::Integral T >
int abramov::Matrix< T >::perm() const
{
  int **vals = data;
  int r = rows;
  int c = cols;
  if (rows < cols)
  {
    Matrix< T > m = transpose();
    vals = m.data;
    r = m.rows;
    c = m.cols;
  }
  if (c == 1)
  {
    int p = 0;
    for (size_t i = 0; i < r; ++i)
    {
      p += vals[i][0];
    }
    return p;
  }
  if (c == 2)
  {
    int p = 0;
    for (size_t i = 0; i < r; ++i)
    {
      for (size_t j = i + 1; j < r; ++j)
      {
        p += vals[i][0] * vals[j][1] + vals[i][1] * vals[j][0];
      }
    }
    return p;
  }
  int p = 0;
  for (size_t i = 0; i < r; ++i)
  {
    Matrix< T > minor = createMinor(i, 0);
    p += vals[i][0] * minor.perm();
  }
  return p;
}

template< abramov::Integral T >
int abramov::Matrix< T >::rank() const
{
  abramov::Matrix copy(*this);
  int r = 0;
  for (size_t col = 0; col < cols && r < rows; ++col)
  {
    int pivot = r;
    while (pivot < rows && copy.data[pivot][col] == 0)
    {
      ++pivot;
    }
    if (pivot == rows)
    {
      continue;
    }
    if (pivot != r)
    {
      std::swap(copy.data[r], copy.data[pivot]);
    }
    for (size_t i = r + 1; i < rows; ++i)
    {
      if (copy.data[i][col] != 0)
      {
        int a = copy.data[r][col];
        int b = copy.data[i][col];
        while (b != 0)
        {
          int temp = b;
          b = a % b;
          a = temp;
        }
        int gcd_val = a;
        int f1 = copy.data[r][col] / gcd_val;
        int f2 = copy.data[i][col] / gcd_val;
        for (size_t j = col; j < cols; ++j)
        {
          copy.data[i][j] = copy.data[i][j] * f1 - copy.data[r][j] * f2;
        }
      }
    }
    ++r;
  }
  return r;
}

template< abramov::Integral T >
int abramov::Matrix< T >::firstNorm() const
{
  int norm = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    int curr = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      curr += std::abs(data[i][j]);
    }
    norm = std::max(norm, curr);
  }
  return norm;
}

template< abramov::Integral T >
int abramov::Matrix< T >::infinityNorm() const
{
  int norm = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    int curr = 0;
    for (size_t j = 0; j < cols; ++j)
    {
      curr += std::abs(data[i][j]);
    }
    norm = std::max(norm, curr);
  }
  return norm;
}

template< abramov::Integral T >
std::pair< double, abramov::Matrix< T > > abramov::Matrix< T >::inverse() const
{
  if (rows != cols)
  {
    throw std::logic_error("Matrix must be square\n");
  }
  int det = determinant();
  if (det == 0)
  {
    throw std::logic_error("Matrix does not have inverse\n");
  }
  Matrix< T > adj(rows, cols, 0);
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      Matrix< T > minor = createMinor(i, j);
      int minor_det = minor.determinant();
      if ((i + j) % 2 == 0)
      {
        adj.data[j][i] = minor_det;
      }
      else
      {
        adj.data[j][i] = -1 * minor_det;
      }
    }
  }
  return { 1.0 / det, adj };
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::horizontalConcat(const Matrix< T > &lhs, const Matrix< T > &rhs, T fill)
{
  size_t max_rows = std::max(lhs.rows, rhs.rows);
  size_t total_cols = lhs.cols + rhs.cols;
  Matrix< T > res;
  res.rows = max_rows;
  res.cols = total_cols;
  res.data = initMatrix(max_rows, total_cols);
  for (size_t i = 0; i < max_rows; ++i)
  {
    for (size_t j = 0; j < lhs.cols; ++j)
    {
      if (i < lhs.rows)
      {
        res.data[i][j] = lhs.data[i][j];
      }
      else
      {
        res.data[i][j] = fill;
      }
    }
    for (size_t j = 0; j < rhs.cols; ++j)
    {
      if (i < rhs.rows)
      {
        res.data[i][lhs.cols + j] = rhs.data[i][j];
      }
      else
      {
        res.data[i][lhs.cols + j] = fill;
      }
    }
  }
  return res;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::verticalConcat(const Matrix< T > &top, const Matrix< T > &bottom, T fill)
{
  size_t max_cols = std::max(top.cols, bottom.cols);
  size_t total_rows = top.rows + bottom.rows;
  Matrix< T > res;
  res.rows = total_rows;
  res.cols = max_cols;
  res.data = initMatrix(total_rows, max_cols);
  for (size_t i = 0; i < total_rows; ++i)
  {
    if (i < top.rows)
    {
      for (size_t j = 0; j < top.cols; ++j)
      {
        res.data[i][j] = top.data[i][j];
      }
      for (size_t j = top.cols; j < max_cols; ++j)
      {
        res.data[i][j] = fill;
      }
    }
    else
    {
      size_t bottom_i = i - top.rows;
      for (size_t j = 0; j < bottom.cols; ++j)
      {
        res.data[i][j] = bottom.data[bottom_i][j];
      }
      for (size_t j = bottom.cols; j < max_cols; ++j)
      {
        res.data[i][j] = fill;
      }
    }
  }
  return res;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::diagonalConcat(const Matrix< T > &a, const Matrix< T > &b, T fill)
{
  size_t total_rows = a.rows + b.rows;
  size_t total_cols = a.cols + b.cols;
  Matrix< T > res;
  res.rows = total_rows;
  res.cols = total_cols;
  res.data = initMatrix(total_rows, total_cols);
  for (size_t i = 0; i < total_rows; ++i)
  {
    for (size_t j = 0; j < total_cols; ++j)
    {
      if (i < a.rows && j < a.cols)
      {
        res.data[i][j] = a.data[i][j];
      }
      else if (i >= a.rows && j >= a.cols)
      {
        res.data[i][j] = b.data[i - a.rows][j - a.cols];
      }
      else
      {
        res.data[i][j] = fill;
      }
    }
  }
  return res;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::kroneckerProduct(const Matrix< T > &a, const Matrix< T > &b)
{
  Matrix< T > res;
  res.rows = a.rows * b.rows;
  res.cols = a.cols * b.cols;
  res.data = initMatrix(res.rows, res.cols);
  for (size_t i = 0; i < a.rows; ++i)
  {
    for (size_t j = 0; j < a.cols; ++j)
    {
      int curr = a.data[i][j];
      size_t block_row_start = i * b.rows;
      size_t block_col_start = j * b.cols;
      for (size_t bi = 0; bi < b.rows; ++bi)
      {
        for (size_t bj = 0; bj < b.cols; ++bj)
        {
          res.data[block_row_start + bi][block_col_start + bj] = curr * b.data[bi][bj];
        }
      }
    }
  }
  return res;
}

template< abramov::Integral T >
std::ostream &abramov::Matrix< T >::print(std::ostream &out) const
{
  std::ostream::sentry s(out);
  if (!s)
  {
    return out;
  }
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols - 1; ++j)
    {
      out << data[i][j] << " ";
    }
    out << data[i][cols - 1] << "\n";
  }
  return out;
}

template< abramov::Integral T >
std::istream &abramov::Matrix< T >::read(std::istream &in)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t m = 0;
  size_t n = 0;
  if (!(in >> m >> n))
  {
    return in;
  }
  Matrix tmp;
  tmp.rows = m;
  tmp.cols = n;
  tmp.data = initMatrix(m, n);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (!(in >> tmp.data[i][j]))
      {
        return in;
      }
    }
  }
  if (in)
  {
    swap(tmp);
  }
  return in;
}

template< abramov::Integral T >
T **abramov::Matrix< T >::initMatrix(size_t m, size_t n)
{
  T **data = new int*[m];
  size_t created = 0;
  try
  {
    for (; created < m; ++created)
    {
      data[created] = new T[n];
    }
  }
  catch (const std::bad_alloc &)
  {
    destroyMatrix(data, created);
    throw;
  }
  return data;
}

template< abramov::Integral T >
void abramov::Matrix< T >::destroyMatrix(T **data, size_t m) noexcept
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] data[i];
  }
  delete[] data;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::Matrix< T >::createMinor(size_t row, size_t col) const
{
  Matrix minor;
  minor.rows = rows - 1;
  minor.cols = cols - 1;
  minor.data = initMatrix(minor.rows, minor.cols);
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

template< abramov::Integral T >
void abramov::Matrix< T >::swap(Matrix< T > &matrix) noexcept
{
  std::swap(data, matrix.data);
  std::swap(rows, matrix.rows);
  std::swap(cols, matrix.cols);
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::operator*(Matrix< T > lhs, T scalar)
{
  lhs *= scalar;
  return lhs;
}

template< abramov::Integral T >
abramov::Matrix< T > abramov::operator*(T scalar, const Matrix< T > &rhs)
{
  return rhs * scalar;
}
#endif
