#include "bvector.h"

#include <cmath>
#include <random>

int BVector::w_height = 10000;
int BVector::w_width = 10000;

void BVector::setBorders(int height, int width) {
  w_height = height;
  w_width = width;
}

void BVector::setvalue(float x, float y)
{
  m_x = x;
  m_y = y;
}

void BVector::limitsize(double max)
{

  float n = norm();
  if (n > max)
  {
    setvalue(m_x * max / n, m_y * max / n);
  }
}


float BVector::dist(const BVector &v)
{
  float dx = abs(m_x - v.x());
  if (dx > w_width / 2)
  {
    dx = w_width - dx;
  }
  float dy = abs(m_y - v.y());
  if (dy > w_height / 2)
  {
    dy = w_height - dy;
  }
  float d = sqrt(pow(dx, 2) + pow(dy, 2));
  return d;
}

float BVector::norm()
{
  float n = sqrt(pow(m_x, 2) + pow(m_y, 2));
  return n;
}

/*
float BVector::angle(const BVector &v)
{
  if (x == 0 && y == 0)
  {
    return 0.0f;
  }
  if (v.x() == 0 && v.y() == 0)
  {
    return 0.0f;
  }

  // per questi non sappiamo se usare float o double
  float scalprod = x * v.x + y * v.y;
  float normx = sqrt(x * x + y * y);
  float normv = sqrt(v.x * v.x + v.y * v.y);
  float cosphi = scalprod / (normx * normv);
  float phi = acos(cosphi); // ci restituisce un angolo in RADIANTI!!
  return phi;
}
*/

void BVector::normalize()
{
  float n = norm();
  if (n > 0)
  {
    m_x /= n;
    m_y /= n;
  }
}


BVector operator+(BVector const& lhs, BVector const& rhs) {
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

BVector operator+(BVector const& vector, double const& scalar) {
  return {vector.x() + scalar, vector.y() + scalar};
}

BVector operator-(BVector const& lhs, BVector const& rhs) {
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

BVector operator-(BVector const& vector, double const& scalar) {
  return {vector.x() - scalar, vector.y() - scalar};
}

BVector operator*(BVector const& lhs, BVector const& rhs) {
  return {lhs.x() * rhs.x(), lhs.y() * rhs.y()};
}

BVector operator*(BVector const& vector, double const& scalar) {
  return {vector.x() * scalar, vector.y() * scalar};
}

BVector operator/(BVector const& vector, double const& scalar) {
  return {vector.x() / scalar, vector.y() / scalar};
}