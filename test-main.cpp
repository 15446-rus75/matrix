#define BOOST_TEST_MODULE matrix
#include <boost/test/unit_test.hpp>
#include "matrix.hpp"

BOOST_AUTO_TEST_CASE(default_constructor)
{
  abramov::Matrix matrix;
}

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  abramov::Matrix matrix(3, 3, 0);
  abramov::Matrix res = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
  bool b = matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(data_constructor)
{
  constexpr size_t k = 9;
  int *vals = new int[k];
  for (size_t i = 0; i < k; ++i)
  {
    vals[i] = i;
  }
  abramov::Matrix matrix(3, 3, vals);
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
  abramov::Matrix tmp(3, 3, vals);
  abramov::Matrix matrix(tmp);
  delete[] vals;
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  abramov::Matrix matrix(abramov::Matrix{});
}

BOOST_AUTO_TEST_CASE(copy_operator_equal)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = matrix;
  bool b = matrix == copy_matrix;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(move_operator_equal)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  bool b = matrix == copy_matrix;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_plus_equal)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = matrix;
  matrix += copy_matrix;
  abramov::Matrix res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  bool b = matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_binary_plus)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = matrix;
  abramov::Matrix new_matrix = matrix + copy_matrix;
  abramov::Matrix res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  bool b = new_matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_unary_plus)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = +matrix;
  bool b = matrix == copy_matrix;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_minus_equal)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = matrix;
  matrix -= copy_matrix;
  abramov::Matrix res(3, 3, 0);
  bool b = matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_binary_minus)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix copy_matrix = matrix;
  abramov::Matrix res = matrix - copy_matrix;
  abramov::Matrix zero(3, 3, 0);
  bool b = res == zero;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_unary_minus)
{
  abramov::Matrix matrix(3, 3, 1);
  abramov::Matrix anti_matrix = -matrix;
  abramov::Matrix res(3, 3, -1);
  bool b = anti_matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_multiple_equal_matrix)
{
  abramov::Matrix a = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix c = { { 6, 5, 4 }, { 3, 2, 1 } };
  a *= c;
  abramov::Matrix res = { { 12, 9, 6 }, { 30, 23, 16 }, { 48, 37, 26 }, { 66, 51, 36 } };
  bool b = a == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_multiple_matrix_matrix)
{
  abramov::Matrix a = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix c = { { 6, 5, 4 }, { 3, 2, 1 } };
  abramov::Matrix d = a * c;
  abramov::Matrix res = { { 12, 9, 6 }, { 30, 23, 16 }, { 48, 37, 26 }, { 66, 51, 36 } };
  bool b = d == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_multiple_equal_scalar)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  matrix *= 2;
  abramov::Matrix res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  bool b = matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_multiple_matrix_scalar)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix double_matrix = matrix * 2;
  abramov::Matrix res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  bool b = double_matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(operator_multiple_scalar_matrix)
{
  abramov::Matrix matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  abramov::Matrix double_matrix = 2 * matrix;
  abramov::Matrix res = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
  bool b = double_matrix == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(transpose)
{
  abramov::Matrix matrix = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  abramov::Matrix t = matrix.transpose();
  abramov::Matrix res = { { 1, 3, 5, 7 }, { 2, 4, 6, 8 } };
  bool b = t == res;
  BOOST_TEST(b);
}

BOOST_AUTO_TEST_CASE(determinant)
{
  abramov::Matrix m1 = { { 1 } };
  BOOST_TEST(m1.determinant() == 1);
  abramov::Matrix m2 = { { 1, 2 }, { 3, 4 } };
  BOOST_TEST(m2.determinant() == -2);
  abramov::Matrix m3 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  BOOST_TEST(m3.determinant() == 0);
  abramov::Matrix m4 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
  BOOST_TEST(m4.determinant() == 0);
}
