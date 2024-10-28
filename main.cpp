#include <iostream>
#include "matrix.hpp"

int main()
{
  size_t M = 0, N = 0;
  std::cout << "Number of rows and columns: ";
  std::cin >> M >> N;
  if (!std::cin || M == 0 || N == 0)
  {
    std::cerr << "Wrong input!\n";
    return 1;
  }
  Matrix mtx = Matrix(M, N);
  std::cout << "Enter elements of matrix:\n";
  mtx.read();
  std::cout << "\n";
  mtx.write();
  std::cout << "Number of rows: " << mtx.getRows() << "\n";
  std::cout << "Number of columns: " << mtx.getColumns() << "\n";
  int a = 0;
  std::cout << "Enter an integer for fill in matrix: ";
  std::cin >> a;
  if (!std::cin)
  {
    std::cerr << "Wrong input!\n";
    mtx.destroy();
    return 1;
  }
  else
  {
    mtx.filling(a);
    mtx.write();
  }
  std::cout << "Enter new number of rows and columns: ";
  std::cin >> M >> N;
  if (!std::cin || M == 0 || N == 0)
  {
    std::cerr << "Wrong input!\n";
    mtx.destroy();
    return 1;
  }
  mtx.transform(M, N);
  mtx.write();
  mtx.destroy();
}
