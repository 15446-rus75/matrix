#include "matrix.hpp"
#include <iostream>
#include <exception>

void destroyMatrix (int **t, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] t[i];
  }
  delete[] t;
}

int** createMatrix(size_t m, size_t n)
{
  int **t = new int* [m];
  size_t created = 0;
  try
  {
    for (; created < m; ++created)
    {
      t[created] = new int[n];
    }
  }
  catch (const std::bad_alloc &e)
  {
    destroyMatrix(t, created, 0);
    throw "Memory fail\n";
  }
  return t;
}

void readMatrix(int **t, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      std::cin >> t[i][j];
    }
  }
  if (!std::cin)
  {
    throw "Wrong input!\n";
  }
}

void writeMatrix(const int * const * t, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    std::cout << t[i][0];
    for (size_t j = 1; j < n; ++j)
    {
      std::cout << " " << t[i][j];
    }
    std::cout << "\n";
  }
}

void Matrix::destroy()
{
  ::destroyMatrix(t_, m_, n_);
}

void Matrix::read()
{
  ::readMatrix(t_, m_, n_);
}

void Matrix::write() const
{
  ::writeMatrix(t_, m_, n_);
}

size_t Matrix::getColumns() const
{
  return n_;
}

size_t Matrix::getRows() const
{
  return m_;
}

void Matrix::filling(int a)
{
  for (size_t i = 0; i < m_; ++i)
  {
    for (size_t j = 0; j < n_; ++j)
    {
      t_[i][j] = a;
    }
  }
}

void Matrix::transform(size_t m, size_t n)
{
  destroyMatrix(t_, m_, n_);
  t_ = createMatrix(m, n);
  m_ = m;
  n_ = n;
  filling(0);
}
