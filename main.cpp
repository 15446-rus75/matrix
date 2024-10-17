#include <iostream>
#include "matrix.hpp"

int main()
{
  size_t M = 0, N = 0;
  std::cin >> M >> N;
  int **t = createMatrix(M, N);
  readMatrix(t, M, N);
  writeMatrix(t, M, N);
  destroyMatrix(t, M, N);
}
