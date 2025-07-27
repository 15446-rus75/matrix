#include <fstream>
#include <iostream>
#include "matrix.hpp"

int main(int argc, char **argv)
{
  using namespace abramov;

  if (argc != 3)
  {
    std::cerr << "Incorrect num of args\n";
    return 1;
  }
  std::ifstream input1(argv[1]);
  std::ifstream input2(argv[2]);
  if (!input1 || !input2)
  {
    std::cerr << "Incorrect filename\n";
    return 1;
  }
  abramov::Matrix m1;
  abramov::Matrix m2;
  if (!m1.read(input1))
  {
    std::cerr << "Fail to read first matrix\n";
    return 1;
  }
  if (!m2.read(input2))
  {
    std::cerr << "Fail to read second matrix\n";
    return 1;
  }

  try
  {
    abramov::Matrix copy = m1;
    copy += m2;
    std::cout << "operator+=\n";
    copy.print();
    std::cout << '\n';
    copy = m1 + m2;
    std::cout << "operator_binary_plus\n";
    copy.print();
    std::cout << '\n';
    copy = +m1;
    std::cout << "operator_unary_plus\n";
    copy.print();
    std::cout << '\n';

    copy = m1;
    copy -= m2;
    std::cout << "operator-=\n";
    copy.print();
    std::cout << '\n';
    copy = m1 - m2;
    std::cout << "operator_binary_minus\n";
    copy.print();
    std::cout << '\n';
    copy = -m1;
    std::cout << "operator_unary_minus\n";
    copy.print();
    std::cout << '\n';

    copy = m1;
    copy *= m2;
    std::cout << "operator*=\n";
    copy.print();
    std::cout << '\n';
    copy = m1 * m2;
    std::cout << "operator_multiple_matrix_matrix\n";
    copy.print();
    std::cout << '\n';

    copy = m1.transpose();
    std::cout << "transpose\n";
    copy.print();
    std::cout << '\n';

    std::cout << "determinant of the first matrix: " << m1.determinant() << '\n';
    std::cout << "determinant of the second matrix: " << m2.determinant() << '\n';
    std::cout << '\n';

    copy = m1 * 2;
    std::cout << "operator_multiple_matrix_scalar\n";
    copy.print();
    std::cout << '\n';
    copy = 2 * m1;
    std::cout << "operator_multiple_scalar_matrix\n";
    copy.print();
    std::cout << '\n';

    copy = m1.horizontalConcat(m1, m2);
    std::cout << "horizontal_concatenation\n";
    copy.print();
    std::cout << '\n';
    copy = m1.verticalConcat(m1, m2);
    std::cout << "vertical_concatenation\n";
    copy.print();
    std::cout << '\n';
    copy = m1.diagonalConcat(m1,m2);
    std::cout << "diagonal_concatenation\n";
    copy.print();
    std::cout << '\n';

    copy = m1.kroneckerProduct(m1, m2);
    std::cout << "Kronecker product\n";
    copy.print();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
  }
}
