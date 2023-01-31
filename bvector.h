#ifndef BVECTOR_H
#define BVECTOR_H

#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

class BVector
{
private:
  static int w_height;
  static int w_width;
  float m_x;
  float m_y;

public:
  BVector() {};
  BVector(float x, float y) : m_x{x}, m_y{y} {}; // costruttore con info in ingresso

  static void setBorders(int height, int width);
  static int height() { return w_height; };
  static int width() { return w_width; };

  float x() const { return m_x; };
  float y() const { return m_y; };
  void setX(float x) { m_x = x; };
  void setY(float y) { m_y = y; };
  void setvalue(float x, float y); // setta x e y dei vettori non inizializzati

  void limitsize(double max); // limita la dimensione di un vettore
  float dist(const BVector &v);
  float norm(); // norma di un vettore
  // float angle(const BVector &v); //angolo compreso tra due vettori
  void normalize(); // setta la norma del vettore a 1
};

BVector operator+(BVector const &lhs, BVector const &rhs);
BVector operator+(BVector const &vector, double const &scalar);
BVector operator-(BVector const &lhs, BVector const &rhs);
BVector operator-(BVector const &vector, double const &scalar);
BVector operator*(BVector const &lhs, BVector const &rhs);
BVector operator*(BVector const &vector, double const &scalar);
BVector operator/(BVector const &vector, double const &scalar);

#endif