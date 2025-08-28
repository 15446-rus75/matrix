#define BOOST_TEST_MODULE Vector
#include <boost/test/unit_test.hpp>
#include "vector.hpp"

namespace
{
  constexpr size_t N = 3;
}

BOOST_AUTO_TEST_CASE(default_construction)
{
  abramov::Vector< double, N > vect{};
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2(vect1);
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  abramov::Vector< double, N > vect = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect1(std::move(vect));
  abramov::Vector< double, N > vect2 = { 1.0, 2.0, 3.0 };
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(init_list_constructor)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2 = vect1;
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(copy_assignment)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2 = vect1;
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(move_assignment)
{
  abramov::Vector< double, N > vect1 = std::move(abramov::Vector< double, N >({ 1.0, 2.0, 3.0 }));
  abramov::Vector< double, N > vect2 = { 1.0, 2.0, 3.0 };
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(operator_plus_equal)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { 3, 2, 1 };
  vect2 += vect1;
  abramov::Vector< int, N > vect = { 4, 4, 4 };
  BOOST_TEST((vect2 == vect));
}

BOOST_AUTO_TEST_CASE(operator_unary_plus)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2 = +vect1;
  BOOST_TEST((vect1 == vect2 ));
}

BOOST_AUTO_TEST_CASE(operator_binary_plus)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { 3, 2, 1 };
  abramov::Vector< int, N > vect = vect1 + vect2;
  abramov::Vector< int, N > vect3 = { 4, 4, 4 };
  BOOST_TEST((vect == vect3));
}

BOOST_AUTO_TEST_CASE(operator_equal_minus)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = vect1;
  vect2 -= vect1;
  abramov::Vector< int, N > vect = { 0, 0, 0 };
  BOOST_TEST((vect2 == vect));
}

BOOST_AUTO_TEST_CASE(operator_unary_minus)
{
  abramov::Vector< double, N > vect1 = { -1.0, -2.0, -3.0 };
  abramov::Vector< double, N > vect2 = -vect1;
  abramov::Vector< double, N > vect = { 1.0, 2.0, 3.0 };
  BOOST_TEST((vect == vect2));
}

BOOST_AUTO_TEST_CASE(operator_binary_minus)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { 3, 2, 1 };
  abramov::Vector< int, N > vect = vect2 - vect1;
  abramov::Vector< int, N > vect3 = { 2, 0, -2 };
  BOOST_TEST((vect3 == vect));
}

BOOST_AUTO_TEST_CASE(operator_multiply_equal)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { 2, 4, 6 };
  vect1 *= 2;
  BOOST_TEST((vect2 == vect1));
}

BOOST_AUTO_TEST_CASE(operator_multiply_vector_scalar)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = vect1 * 2;
  abramov::Vector< int, N > vect = { 2, 4, 6 };
  BOOST_TEST((vect == vect2));
}

BOOST_AUTO_TEST_CASE(operator_multiply_scalar_vector)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = 2 * vect1;
  abramov::Vector< int, N > vect = { 2, 4, 6 };
  BOOST_TEST((vect == vect2));
}

BOOST_AUTO_TEST_CASE(dot)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { -2, 0, 6 };
  int res = vect1.dot(vect2);
  BOOST_TEST(res == 16);
}

BOOST_AUTO_TEST_CASE(cross)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { -2, 0, 6 };
  abramov::Vector< int, N > vect3 = vect1.cross(vect2);
  abramov::Vector< int, N > vect = {12, -12, 4 };
  BOOST_TEST((vect == vect3));
}

BOOST_AUTO_TEST_CASE(triple)
{
  abramov::Vector< int, N > vect1 = { 1, 2, 3 };
  abramov::Vector< int, N > vect2 = { -2, 0, 6 };
  abramov::Vector< int, N > vect3 = { 4, 2, 1 };
  int res = vect1.triple(vect2, vect3);
  BOOST_TEST(res == 28);
}

BOOST_AUTO_TEST_CASE(norm)
{
  abramov::Vector< int, N > vect = { 3, 4, 0 };
  double res = vect.norm();
  BOOST_TEST(res == 5.0);
}

BOOST_AUTO_TEST_CASE(normalized)
{
  abramov::Vector< int, N > vect1 = { 3, 4, 0 };
  abramov::Vector< double, N > vect2 = vect1.normalized();
  abramov::Vector< double, N > vect = { 0.6, 0.8, 0.0 };
  BOOST_TEST((vect2 == vect));
}

BOOST_AUTO_TEST_CASE(equal_operator)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2 = vect1;
  BOOST_TEST((vect1 == vect2));
}

BOOST_AUTO_TEST_CASE(not_equal_operator)
{
  abramov::Vector< double, N > vect1 = { 1.0, 2.0, 3.0 };
  abramov::Vector< double, N > vect2 = { 3.0, 2.0, 1.0 };
  BOOST_TEST((vect1 != vect2));
}
