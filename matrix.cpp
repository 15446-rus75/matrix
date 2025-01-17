#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

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
    throw;
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
    throw std::logic_error("Wrong input\n");
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

Matrix::Matrix(size_t m, size_t n, int value)
{
  rows = m;
  cols = n;
  data = createMatrix(m, n);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      data[i][j] = value;
    }
  }
}

Matrix::Matrix(size_t m, size_t n, const int *values)
{
  rows = m;
  cols = n;
  data = createMatrix(m, n);
  size_t k = 0;
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      data[i][j] = values[k++];
    }
  }
}
