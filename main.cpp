#include <iostream>
#include "matrix.hpp"

int main()
{
  size_t M = 0, N = 0;
  std::cin >> M >> N;
  if (!std::cin || M == 0 || N == 0)
  {
    std::cerr << "Wrong input!\n";
    return 1;
  }
  Matrix mtx = Matrix(M, N);
  mtx.read();
  mtx.write();
  mtx.destroy();
}
