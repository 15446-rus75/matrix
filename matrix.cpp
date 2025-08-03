#include "matrix.hpp"
#include <numeric>
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

abramov::Matrix::Matrix(std::initializer_list < std::initializer_list< int > > init)
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
    for (size_t j = 0; j < matrix.cols; ++j)
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
  Matrix res(rows,other.cols, 0);
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

abramov::Matrix abramov::operator*(Matrix lhs, const Matrix &rhs)
{
  lhs *= rhs;
  return lhs;
}

bool abramov::Matrix::operator==(const Matrix &other) const
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

abramov::Matrix abramov::Matrix::transpose() const
{
  Matrix res;
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

int abramov::Matrix::determinant() const
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

int abramov::Matrix::trace() const
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

int abramov::Matrix::perm() const
{
  int **vals = data;
  int r = rows;
  int c = cols;
  if (rows < cols)
  {
    Matrix m = transpose();
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
    Matrix minor = createMinor(i, 0);
    p += vals[i][0] * minor.perm();
  }
  return p;
}

int abramov::Matrix::rank() const
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

abramov::Matrix abramov::Matrix::horizontalConcat(const Matrix &lhs, const Matrix &rhs, int fill)
{
  size_t max_rows = std::max(lhs.rows, rhs.rows);
  size_t total_cols = lhs.cols + rhs.cols;
  Matrix res;
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

abramov::Matrix abramov::Matrix::verticalConcat(const Matrix &top, const Matrix &bottom, int fill)
{
  size_t max_cols = std::max(top.cols, bottom.cols);
  size_t total_rows = top.rows + bottom.rows;
  Matrix res;
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

abramov::Matrix abramov::Matrix::diagonalConcat(const Matrix &a, const Matrix &b, int fill)
{
  size_t total_rows = a.rows + b.rows;
  size_t total_cols = a.cols + b.cols;
  Matrix res;
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

abramov::Matrix abramov::Matrix::kroneckerProduct(const Matrix &a, const Matrix &b)
{
  Matrix res;
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

std::ostream &abramov::Matrix::print(std::ostream &out) const
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

std::istream &abramov::Matrix::read(std::istream &in)
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

abramov::Matrix abramov::Matrix::createMinor(size_t row, size_t col) const
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

void abramov::Matrix::swap(Matrix &matrix) noexcept
{
  std::swap(data, matrix.data);
  std::swap(rows, matrix.rows);
  std::swap(cols, matrix.cols);
}
