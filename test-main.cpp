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
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  abramov::Matrix matrix(abramov::Matrix{});
}
