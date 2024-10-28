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
  std::cout << "Number of rows: " << mtx.getRows() << "\n";
  std::cout << "Number of columns: " << mtx.getColumns() << "\n";
  int a = 0;
  std::cin >> a;
  if (!std::cin)
  {
    std::cerr << "Wrong input!\n";
    return 1;
  }
  else
  {
    mtx.filling(a);
    mtx.write();
  }
  mtx.destroy();
}
