#include <iostream>
#include "matrix.hpp"

int main()
{
  size_t M = 0, N = 0;
  std::cin >> M >> N;
  if (!std::cin)
  {
    std::cerr << "Wrong input!\n";
    return 1;
  }
  int **t = nullptr;
  try
  {
    t = createMatrix(M, N);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Memory fail\n";
    delete[] t;
    return 2;
  }
  try
  {
    readMatrix(t, M, N);
  }
  catch(const char* e)
  {
    std::cerr << e;
    return 1;
  }
  writeMatrix(t, M, N);
  destroyMatrix(t, M, N);
}
