#include <fstream>
#include <iomanip>
#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"

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
  abramov::Matrix< int > m1;
  abramov::Matrix< int > m2;
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
    abramov::Matrix< int > copy = m1;
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

    copy = m1;
    copy = m1.power(2);
    std::cout << "power with k = 2\n";
    copy.print();
    copy = m1.power(3);
    std::cout << "power with k = 3\n";
    copy.print();
    std::cout << '\n';

    copy = m1.transpose();
    std::cout << "transpose\n";
    copy.print();
    std::cout << '\n';

    std::cout << "determinant of the first matrix: " << m1.determinant() << '\n';
    std::cout << "determinant of the second matrix: " << m2.determinant() << '\n';
    std::cout << '\n';

    std::cout << "trace of the first matrix: " << m1.trace() << '\n';
    std::cout << "trace of the second matrix: " << m2.trace() << '\n';
    std::cout << '\n';

    std::cout << "permanent of the first matrix: " << m1.perm() << '\n';
    std::cout << "permanent of the second matrix: " << m2.perm() << '\n';
    std::cout << '\n';

    std::cout << "rank of the first matrix: " << m1.rank() << '\n';
    std::cout << "rank of the second matrix: " << m2.rank() << '\n';
    std::cout << '\n';

    std::cout << "first norm of the first matrix: " << m1.firstNorm() << '\n';
    std::cout << "first norm of the second matrix: " << m2.firstNorm() << '\n';
    std::cout << '\n';

    std::cout << "infinity norm of the first matrix: " << m1.infinityNorm() << '\n';
    std::cout << "infinity norm of the second matrix: " << m2.infinityNorm() << '\n';
    std::cout << '\n';

    auto p1 = m1.inverse();
    std::cout << "first inverse matrix\n";
    std::cout << "factor " << std::setprecision(2) << p1.first << '\n';
    std::cout << "integer matrix\n";
    p1.second.print();
    auto p2 = m2.inverse();
    std::cout << "second inverse matrix\n";
    std::cout << "factor " << p2.first << '\n';
    std::cout << "integer matrix\n";
    p2.second.print();
    std::cout << '\n';

    std::ifstream input3("cramer.txt");
    abramov::Matrix< int > cr;
    cr.read(input3);
    auto v1 = cr.solveCramer();
    std::cout << "solutions of the matrix as system of linear equations\n";
    std::cout << *(v1.begin());
    for (auto it = ++v1.begin(); it != v1.end(); ++it)
    {
      std::cout << ' ' << *it;
    }
    std::cout << '\n' << '\n';

    copy = m1 * 2;
    std::cout << "operator_multiple_matrix_scalar\n";
    copy.print();
    std::cout << '\n';
    copy = 2 * m1;
    std::cout << "operator_multiple_scalar_matrix\n";
    copy.print();
    std::cout << '\n';

    copy = Matrix< int >::horizontalConcat(m1, m2);
    std::cout << "horizontal_concatenation\n";
    copy.print();
    std::cout << '\n';
    copy = Matrix< int >::verticalConcat(m1, m2);
    std::cout << "vertical_concatenation\n";
    copy.print();
    std::cout << '\n';
    copy = Matrix< int >::diagonalConcat(m1,m2);
    std::cout << "diagonal_concatenation\n";
    copy.print();
    std::cout << '\n';

    copy = Matrix< int >::kroneckerProduct(m1, m2);
    std::cout << "Kronecker product\n";
    copy.print();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
  }
}
