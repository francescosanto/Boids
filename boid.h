#ifndef BOID_H
#define BOID_H

#include <cmath>

#include <iostream>
#include <string>
#include <vector>

#include "bvector.h"

/*static const float sepCoef = 1;
static const float cohCoef = 1;
static const float aliCoef = 1;*/

class Boid
{
private:
  static float SepRange;
  static float AliRange;
  static float CohRange;
  static float maxVel;
  static float maxAcc;

  BVector m_position;
  BVector m_velocity;
  BVector m_acceleration;

  double m_sepCoef;
  double m_cohCoef;
  double m_aliCoef;
  int m_boidsNumber;

  //Commento: cosa fa separation
  BVector separation(const std::vector<Boid> &boids);
  BVector steer(const BVector &target);
  BVector alignment(const std::vector<Boid> &boids);
  BVector cohesion(const std::vector<Boid> &boids);
  void resultantforce(BVector &v, BVector &u, BVector &w);
public:
  Boid() {};
  Boid(double s, double c, double a, int n) 
    : m_sepCoef{s}, m_cohCoef{c}, m_aliCoef{a}, m_boidsNumber{n} {};

  static void setSepRange(float sR) { SepRange = sR; };
  static void setAliRange(float aR) { AliRange = aR; };
  static void setCohRange(float cR) { CohRange = cR; };
  static void setmaxVel(float mV) { maxVel = mV; };
  static void setmaxAcc(float mA) { maxAcc = mA; };

  BVector position() const { return m_position; };
  BVector velocity() const { return m_velocity; };
  void setRandomValues();
  //BVector acceleration() const { return m_acceleration; };
  void setValueS(double s) { m_sepCoef = s; };
  void setValueC(double c) { m_cohCoef = c; };
  void setValueA(double a) { m_aliCoef = a; };


  /*BVector seek(BVector v);*/
  void newvalues(const std::vector<Boid> &boids);
  float meanDist(std::vector<Boid> &boids);
  float meanVelX(std::vector<Boid> &boids);
  float meanVelY(std::vector<Boid> &boids);
  float meanVel(std::vector<Boid> &boids);
};

#endif // BOID_H