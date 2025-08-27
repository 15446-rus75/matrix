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
