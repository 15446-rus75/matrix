#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <array>
#include <cmath>
#include <concepts>
#include <initializer_list>

namespace abramov
{
  template< class T >
  concept Numeric = std::integral< T > || std::floating_point< T >;
  template< Numeric T, size_t N >
  struct Vector;


  template< Numeric T, size_t N >
  Vector< T, N > operator+(Vector< T, N > lhs, const Vector< T, N > &rhs);
  template< Numeric T, size_t N >
  Vector< T, N > operator-(Vector< T, N > lhs, const Vector< T, N > &rhs);
  template< Numeric T, size_t N >
  Vector< T, N > operator*(Vector< T, N > lhs, T scalar);
  template< Numeric T, size_t N >
  Vector< T, N > operator*(T scalar, const Vector< T, N > &rhs);

  template< Numeric T, size_t N >
  struct Vector
  {
    friend Vector< T, N > operator+<>(Vector< T, N > lhs, const Vector< T, N > &rhs);
    friend Vector< T, N > operator-<>(Vector< T, N > lhs, const Vector< T, N > &rhs);

    Vector();
    Vector(const Vector< T, N > &other);
    Vector(Vector< T, N > &&other) noexcept;
    Vector(std::initializer_list< T > init);
    explicit Vector(const std::array< T, N > &arr);
    ~Vector() = default;
    Vector< T, N > &operator=(const Vector< T, N > &other);
    Vector< T, N > &operator=(Vector &&other) noexcept;
    Vector< T, N > &operator+=(const Vector< T, N > &other);
    Vector< T, N > operator+() const;
    Vector< T, N > &operator-=(const Vector< T, N > &other);
    Vector< T, N > operator-() const;
    Vector< T, N > &operator*=(T scalar);
    bool operator==(const Vector< T, N > &other) const;
    bool operator!=(const Vector< T, N > &other) const;
    T dot(const Vector< T, N > &other) const;
    Vector< T, N > cross(const Vector< T, N > &other) const;
    T triple(const Vector< T, N > &b, const Vector< T, N > &c) const;
    double norm() const;
    Vector< double, N > normalized() const;
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
abramov::Vector< T, N >::Vector(const std::array< T, N > &arr):
  data(arr)
{}

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
abramov::Vector< T, N > &abramov::Vector< T, N >::operator+=(const Vector< T, N > &other)
{
  for (size_t i = 0; i < N; ++i)
  {
    data[i] += other.data[i];
  }
  return *this;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::operator+(Vector< T, N > lhs, const Vector< T, N > &rhs)
{
  lhs += rhs;
  return lhs;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::Vector< T, N >::operator+() const
{
  return *this;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > &abramov::Vector< T, N >::operator-=(const Vector< T, N > &other)
{
  for (size_t i = 0; i < N; ++i)
  {
    data[i] -= other.data[i];
  }
  return *this;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::operator-(Vector< T, N > lhs, const Vector< T, N > &rhs)
{
  lhs -= rhs;
  return lhs;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::Vector< T, N >::operator-() const
{
  abramov::Vector< T, N > res(*this);
  for (size_t i = 0; i < N; ++i)
  {
    res.data[i] *= -1;
  }
  return res;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > &abramov::Vector< T, N >::operator*=(T scalar)
{
  for (size_t i = 0; i < N; ++i)
  {
    data[i] *= scalar;
  }
  return *this;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::operator*(Vector< T, N > lhs, T scalar)
{
  lhs *= scalar;
  return lhs;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N > abramov::operator*(T scalar, const Vector< T, N > &rhs)
{
  return rhs * scalar;
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
T abramov::Vector< T, N >::dot(const Vector< T, N > &other) const
{
  T res = 0;
  for (size_t i = 0; i < N; ++i)
  {
    res += data[i] * other.data[i];
  }
  return res;
}

template< abramov::Numeric T, size_t N >
abramov::Vector< T, N >abramov::Vector< T, N >::cross(const Vector< T, N > &other) const
{
  if (N != 3)
  {
    throw std::logic_error("Vector must be 3D\n");
  }
  T x = data[1] * other.data[2] - data[2] * other.data[1];
  T y = data[2] * other.data[0] - data[0] * other.data[2];
  T z = data[0] * other.data[1] - data[1] * other.data[0];
  return Vector({ x, y, z });
}

template< abramov::Numeric T, size_t N >
T abramov::Vector< T, N >::triple(const Vector< T, N > &b, const Vector< T, N > &c) const
{
  if (N != 3)
  {
    throw std::logic_error("Vector must be 3D\n");
  }
  return dot(b.cross(c));
}

template< abramov::Numeric T, size_t N >
double abramov::Vector< T, N >::norm() const
{
  double res = 0;
  for (size_t i = 0; i < N; ++i)
  {
    res += data[i] * data[i];
  }
  return std::sqrt(res);
}

template< abramov::Numeric T, size_t N >
abramov::Vector< double, N > abramov::Vector< T, N >::normalized() const
{
  double len = norm();
  if (len == 0)
  {
    throw std::logic_error("Zero vector can not be normalized\n");
  }
  std::array< double, N > arr;
  for (size_t i = 0; i < N; ++i)
  {
    arr[i] = static_cast< double >(data[i]) / len;
  }
  Vector< double, N > res(arr);
  return res;
}

template< abramov::Numeric T, size_t N >
void abramov::Vector< T, N >::swap(Vector< T, N > &other) noexcept
{
  std::swap(data, other.data);
}
#endif
