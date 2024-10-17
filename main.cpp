#include <iostream>

int** createMatrix(size_t m, size_t n);
void destroyMatrix (int** t, size_t m, size_t n);

int main()
{
  size_t M = 0, N = 0;
  std::cin >> M >> N;
  int** t = createMatrix(M, N);

  destroyMatrix(t, M, N);
  std::cout << M << " " << N << "\n";
}
