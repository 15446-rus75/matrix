#define BOOST_TEST_MODULE matrix
#include <boost/test/unit_test.hpp>
#include "matrix.hpp"

BOOST_AUTO_TEST_CASE(default_constructor)
{
  abramov::Matrix< int > matrix;
}

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  abramov::Matrix< int > matrix(3, 3, 0);
  abramov::Matrix< int > res = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
  BOOST_TEST((matrix == res));
}

BOOST_AUTO_TEST_CASE(data_constructor)
{
  constexpr size_t k = 9;
  int *vals = new int[k];
  for (size_t i = 0; i < k; ++i)
  {
    vals[i] = i;
  }
  abramov::Matrix< int > matrix(3, 3, vals);
  abramov::Matrix< int > res = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 } };
  BOOST_TEST((matrix == res));
  delete[] vals;
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  constexpr size_t k = 9;
  int *vals = new int[k];
  for (size_t i = 0; i < k; ++i)
  {
    vals[i] = i;
  }
  abramov::Matrix< int > tmp(3, 3, vals);
  abramov::Matrix< int > matrix(tmp);
  abramov::Matrix< int > res = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 } };
  BOOST_TEST((matrix == res));
  delete[] vals;
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  abramov::Matrix< int > matrix(abramov::Matrix< int >{});
}

BOOST_AUTO_TEST_CASE(copy_operator_equal)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = matrix;
  BOOST_TEST((matrix == copy_matrix));
}

BOOST_AUTO_TEST_CASE(move_operator_equal)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST((matrix == copy_matrix));
}

BOOST_AUTO_TEST_CASE(operator_plus_equal)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = matrix;
  matrix += copy_matrix;
  abramov::Matrix< int > res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  BOOST_TEST((matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_binary_plus)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = matrix;
  abramov::Matrix< int > new_matrix = matrix + copy_matrix;
  abramov::Matrix< int > res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  BOOST_TEST((new_matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_unary_plus)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = +matrix;
  BOOST_TEST((matrix == copy_matrix));
}

BOOST_AUTO_TEST_CASE(operator_minus_equal)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = matrix;
  matrix -= copy_matrix;
  abramov::Matrix< int > res(3, 3, 0);
  BOOST_TEST((matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_binary_minus)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > copy_matrix = matrix;
  abramov::Matrix< int > res = matrix - copy_matrix;
  abramov::Matrix< int > zero(3, 3, 0);
  BOOST_TEST((res == zero));
}

BOOST_AUTO_TEST_CASE(operator_unary_minus)
{
  abramov::Matrix< int > matrix(3, 3, 1);
  abramov::Matrix< int > anti_matrix = -matrix;
  abramov::Matrix< int > res(3, 3, -1);
  BOOST_TEST((anti_matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_multiple_equal_matrix)
{
  abramov::Matrix< int > a = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix< int > c = { { 6, 5, 4 }, { 3, 2, 1 } };
  a *= c;
  abramov::Matrix< int > res = { { 12, 9, 6 }, { 30, 23, 16 }, { 48, 37, 26 }, { 66, 51, 36 } };
  BOOST_TEST((a == res));
}

BOOST_AUTO_TEST_CASE(operator_multiple_matrix_matrix)
{
  abramov::Matrix< int > a = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix< int > c = { { 6, 5, 4 }, { 3, 2, 1 } };
  abramov::Matrix< int > d = a * c;
  abramov::Matrix< int > res = { { 12, 9, 6 }, { 30, 23, 16 }, { 48, 37, 26 }, { 66, 51, 36 } };
  BOOST_TEST((d == res));
}

BOOST_AUTO_TEST_CASE(operator_multiple_equal_scalar)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  matrix *= 2;
  abramov::Matrix< int > res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  BOOST_TEST((matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_multiple_matrix_scalar)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > double_matrix = matrix * 2;
  abramov::Matrix< int > res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  BOOST_TEST((double_matrix == res));
}

BOOST_AUTO_TEST_CASE(operator_multiple_scalar_matrix)
{
  abramov::Matrix< int > matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > double_matrix = 2 * matrix;
  abramov::Matrix< int > res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  BOOST_TEST((double_matrix == res));
}

BOOST_AUTO_TEST_CASE(power)
{
  abramov::Matrix< int > m = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix< int > square_m = m.power(2);
  abramov::Matrix< int > res1 = { { 30, 36, 42 }, { 66, 81, 96 }, { 102, 126, 150 } };
  abramov::Matrix< int > cubic_m = m.power(3);
  abramov::Matrix< int > res2 = { { 468, 576, 684 }, { 1062, 1305, 1548 }, { 1656, 2034, 2412 } };
  BOOST_TEST((square_m == res1));
  BOOST_TEST((cubic_m == res2));
}

BOOST_AUTO_TEST_CASE(transpose)
{
  abramov::Matrix< int > matrix = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix< int > t = matrix.transpose();
  abramov::Matrix< int > res = { { 1, 3, 5, 7 }, { 2, 4, 6, 8 } };
  BOOST_TEST((t == res));
}

BOOST_AUTO_TEST_CASE(determinant)
{
  abramov::Matrix< int > m1 = { { 1 } };
  BOOST_TEST(m1.determinant() == 1);
  abramov::Matrix< int > m2 = { { 1, 2 }, { 3, 4 } };
  BOOST_TEST(m2.determinant() == -2);
  abramov::Matrix< int > m3 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m3.determinant() == 0);
  abramov::Matrix< int > m4 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
  BOOST_TEST(m4.determinant() == 0);
}

BOOST_AUTO_TEST_CASE(trace)
{
  abramov::Matrix< int > m = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m.trace() == 15);
}

BOOST_AUTO_TEST_CASE(perm)
{
  abramov::Matrix< int > m1 = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
  BOOST_TEST(m1.perm() == 64);
  abramov::Matrix< int > m2 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
  BOOST_TEST(m2.perm() == 55456);
}

BOOST_AUTO_TEST_CASE(rank)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m1.rank() == 2);
  abramov::Matrix< int > m2 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
  BOOST_TEST(m2.rank() == 2);
}

BOOST_AUTO_TEST_CASE(first_norm)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m1.firstNorm() == 18);
}

BOOST_AUTO_TEST_CASE(infinity_norm)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m1.infinityNorm() == 24);
}

BOOST_AUTO_TEST_CASE(inverse)
{
  abramov::Matrix< int > m = { { 1, 2, 3 }, { 4, 5, 4 }, { 3, 2, 1 } };
  auto p = m.inverse();
  abramov::Matrix< int > inv = p.second;
  double d = p.first;
  abramov::Matrix< int > m1 = { { -3, 4, -7 }, { 8, -8, 8 }, { -7, 4, -3 } };
  BOOST_TEST(d == -0.125);
  BOOST_TEST((inv == m1));
}

BOOST_AUTO_TEST_CASE(horizontal_concat)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 } };
  abramov::Matrix< int > m2 = { { 7, 8 }, { 9, 10 }, { 11, 12 } };
  abramov::Matrix< int > conc = abramov::Matrix< int >::horizontalConcat(m1, m2);
  abramov::Matrix< int > res = { { 1, 2, 3, 7, 8 }, { 4, 5, 6, 9, 10 }, { 0, 0, 0, 11, 12 } };
  BOOST_TEST((conc == res));
}

BOOST_AUTO_TEST_CASE(vertical_concat)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 } };
  abramov::Matrix< int > m2 = { { 7, 8 }, { 9, 10 }, { 11, 12 } };
  abramov::Matrix< int > conc = abramov::Matrix< int >::verticalConcat(m1, m2);
  abramov::Matrix< int > res = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 }, { 9, 10, 0 }, { 11, 12, 0 } };
  BOOST_TEST((conc == res));
}

BOOST_AUTO_TEST_CASE(diagonal_concat)
{
  abramov::Matrix< int > m1 = { { 1, 2, 3 }, { 4, 5, 6 } };
  abramov::Matrix< int > m2 = { { 7, 8 }, { 9, 10 }, { 11, 12 } };
  abramov::Matrix< int > conc = abramov::Matrix< int >::diagonalConcat(m1, m2);
  abramov::Matrix< int > res = { { 1, 2, 3, 0, 0 }, { 4, 5, 6, 0, 0 }, { 0, 0, 0, 7, 8 }, { 0, 0, 0, 9, 10 }, { 0, 0, 0, 11, 12 } };
  BOOST_TEST((conc == res));
}

BOOST_AUTO_TEST_CASE(kronecker_product)
{
  abramov::Matrix< int > m1 = { { 1, 2 }, { 3, 4 } };
  abramov::Matrix< int > m2 = { { 0, 5 }, { 6, 7 } };
  abramov::Matrix< int > prod = abramov::Matrix< int >::kroneckerProduct(m1, m2);
  abramov::Matrix< int > res = { { 0, 5, 0, 10 }, { 6, 7, 12, 14 }, { 0, 15, 0, 20 }, { 18, 21, 24, 28 } };
  BOOST_TEST((prod == res));
}
