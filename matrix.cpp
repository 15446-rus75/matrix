#include "matrix.hpp"

void destriyMatrix (int **t, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] t[i];
  }
  delete[] t;
}
