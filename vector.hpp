#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <array>
#include <concepts>
#include <initializer_list>

namespace abramov
{
  template< class T >
  concept Numeric = std::integral< T > || std::floating_point< T >;

  template< Numeric T, size_t N >
  struct Vector
  {
    Vector();
    Vector(const Vector< T, N > &other);
    Vector(Vector< T, N > &&other) noexcept;
    Vector(std::initializer_list< T > init);
    ~Vector() = default;
    Vector< T, N > &operator=(const Vector< T, N > &other);
    Vector< T, N > &operator=(Vector &&other) noexcept;
    bool operator==(const Vector< T, N > &other) const;
    bool operator!=(const Vector< T, N > &other) const;
  private:
    std::array< T, N > data;

    void swap(Vector< T, N > &other) noexcept;
  };
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N >::Vector():
  data(std::array< T, N >{})
{}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N >::Vector(const Vector< T, N > &other):
  data(other.data)
{}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N >::Vector(Vector< T, N > &&other) noexcept:
  data(std::move(other.data))
{}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N >::Vector(std::initializer_list< T > init):
  data(std::array< T, N >{})
{
  if (init.size() != N )
  {
    throw std::logic_error("Incorrect initializer_list\n");
  }
  size_t i = 0;
  for (auto it = init.begin(); it != init.end(); ++it)
  {
    data[i++] = *it;
  }
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > &abramov::Vector< T, N >::operator=(const Vector< T, N > &other)
{
  Vector< T, N > tmp(other);
  swap(tmp);
  return *this;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > &abramov::Vector< T, N >::operator=(Vector< T, N > &&other) noexcept
{
  Vector< T, N > tmp(other);
  swap(tmp);
  return *this;
}

template< abramov::Numeric T, size_t N >
bool abramov::Vector< T, N >::operator==(const Vector< T, N > &other) const
{
  for (size_t i = 0; i < N; ++i)
  {
    if (std::abs(data[i] - other.data[i]) > 1e-6)
    {
      return false;
    }
  }
  return true;
}

template< abramov::Numeric T, size_t N >
bool abramov::Vector< T, N >::operator!=(const Vector< T, N > &other) const
{
  return !(*this == other);
}

template< abramov::Numeric T, size_t N >
void abramov::Vector< T, N >::swap(Vector< T, N > &other) noexcept
{
  std::swap(data, other.data);
}
#endif
