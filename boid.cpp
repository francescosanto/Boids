#include "boid.h"
#include <random>

/*Boid::Boid(float x, float y){
    acceleration = BVector(0, 0);
    velocity.setRandomValue();
    position.setvalue(x, y);
    maxVel = 3;
    maxAcc = 0.5;
}*/

// la funzione si applica ad un boid e scorre tutti gli altri
// misurandone la distanza. Se il boid è dentro al raggio d'azione
// Aliora creo un "Vettore media" che indica la nuova direzione e intensità
// della velocità. Ritorno il vettore media velocità.
// Per farlo normalizziamo la differenza tra le posizioni e la moltiplichiamo
// per maxvelocity considerando un peso (maggiore se sei più vicino).
// Le singole variazioni sono sommate e divise infine per il numero di
// boid nel raggio (count).

float Boid::SepRange = 100;
float Boid::AliRange = 10;
float Boid::CohRange = 100;
float Boid::maxVel = 200;
float Boid::maxAcc = 50;

BVector Boid::separation(const std::vector<Boid> &boids)
{
  int count = 0;
  BVector separationVector;
  for (int i = 0; i < boids.size(); i++)
  {
    float distance = m_position.dist(boids[i].position());
    if (distance > 0 && distance < SepRange)
    {
      BVector dev = boids[i].position() - m_position;
      dev.normalize();
      dev = dev / distance;
      separationVector = separationVector + dev;
      count++;
    }
  }

  if (count > 0)
  {
    separationVector = separationVector / (float)count;
    separationVector.normalize();
    separationVector = separationVector / maxVel;
    BVector acc = separationVector - m_velocity;
    acc.limitsize(maxAcc);
    return acc;
  }
  else
  {
    return {0, 0};
  }
}

//
BVector Boid::alignment(const std::vector<Boid> &boids)
{
  BVector alignmentVector;
  int count = 0; // lo uso per poter fare la media
  for (int i = 0; i < boids.size(); i++)
  {
    float distance = m_position.dist(boids[i].position());
    if (distance > 0 && distance < AliRange)
    {
      alignmentVector = alignmentVector + boids[i].velocity();
      count++;
    }
  }
  if (count > 0)
  {
    alignmentVector = alignmentVector / (float)count; // velocità media
    alignmentVector.normalize();
    alignmentVector = alignmentVector * maxVel; // impongo il modulo di sum = maxVel

    BVector acceleration;
    acceleration = alignmentVector;
    acceleration = steer(acceleration);
    /*acceleration = acceleration.vectorTwoSub(alignmentVector, velocity); //accelerazione
    acceleration.limitsize(maxAcc);*/
    return acceleration;
  }
  else
  {
    return {0, 0};
  }
}

BVector Boid::cohesion(const std::vector<Boid> &boids)
{
  BVector cohesionVector;
  int count = 0;
  for (int i = 0; i < boids.size(); i++)
  {
    float distance = m_position.dist(boids[i].position());
    if (distance > 0 && distance < CohRange)
    {
      cohesionVector = cohesionVector + boids[i].position();
      count++;
    }
  }

  if (count > 0)
  {
    cohesionVector = cohesionVector / (float)count;
    return steer(cohesionVector);
    /*BVector headto;
    BVector u;
    headto.vectorSub(mc);
    headto.normalize();
    headto.scalarMul(maxVel);
    u.vectorTwoSub(velocity, headto);
    u.limitsize(maxAcc);
    return u;*/
  }
  else
  {
    return {0, 0};
  }
}

BVector Boid::steer(const BVector &target)
{
  BVector desired = target - m_position;
  float distance = desired.norm();
  if (distance > 0)
  {
    desired.normalize();
    desired = desired * maxVel;
    BVector steer = desired - m_velocity;
    steer.limitsize(maxAcc);
    return steer;
  }
  else
  {
    return {0, 0};
  }
}

void Boid::resultantforce(BVector &v, BVector &u, BVector &w)
{
  m_acceleration = m_acceleration + v + u + w;
  m_acceleration.limitsize(maxAcc);
}

void Boid::setRandomValues() {
  std::random_device seed;
  std::uniform_real_distribution<float> distPos(0, BVector::width());
  std::uniform_real_distribution<float> distVel(-maxVel, maxVel);
  m_position.setvalue(distPos(seed), distPos(seed));
  m_velocity.setvalue(distVel(seed), distVel(seed));
}


void Boid::newvalues(const std::vector<Boid> &boids)
{
  // creiamo un vettore per ogni funzione
  BVector sep = separation(boids) * m_sepCoef;
  BVector ali = alignment(boids) * m_aliCoef;
  BVector coh = cohesion(boids) * m_cohCoef;

  // questi parametri saranno di input nel main
  //sep.scalarMul(sepCoef);
  //ali.scalarMul(aliCoef);
  //coh.scalarMul(cohCoef);

  resultantforce(sep, ali, coh); // somma i contributi di ogni funzione

  // update delle velocità e posizioni con reset accelerazione.
  m_velocity = m_velocity + m_acceleration;
  m_velocity.limitsize(maxVel);
  m_position = m_position + m_velocity;
  if (m_position.x() < 0)
    m_position.setX(m_position.x() + BVector::width());
  if (m_position.y() < 0)
    m_position.setY(m_position.y() + BVector::height());
  if (m_position.x() > 1000)
    m_position.setX(m_position.x() - BVector::width());
  if (m_position.y() > 1000)
    m_position.setY(m_position.y() - BVector::height());
  m_acceleration.setvalue(0,0);
}

// Si applica ad un boid e ritorna "sum".
// Creo target(0,0) e lo sottraggo a un vettore in ingresso, così
// che diventi il negativo del punto verso cui tendo. Normalizzo,
// moltiplico per la velocità massima (così diventa target diventa velocità).
// sottraggo alla velocità del boid il vettore target, e ne limito la dimensione.

/*BVector Boid::seek(BVector v)
{ // v è il target
  BVector target;
  target.vectorSub(v);
  target.normalize(); // v viene normalizzato e reso una velocità
  target.scalarMul(maxVel);
  acceleration.vectorTwoSub(velocity, target); // si fa la differenza fra la direzione del boid e il target
  acceleration.limitsize(maxAcc);
  return acceleration;
  return acceleration;
}*/

float Boid::meanDist(std::vector<Boid> &boids)
{
  int count = 0;
  float u = 0;
  for (int i = 0; i < boids.size(); i++)
  {
    BVector positionI = boids[i].position();
    // std::cout << "i=" << i << endl;
    for (int j = i; j < boids.size(); j++)
    {
      // std::cout << "j=" << j << endl;
      float a = positionI.dist(boids[j].position());
      // std::cout << "a=" << a << endl;
      u += a;
      if (a != 0)
      {
        count++;
      }
      // std::cout << "count" << count << endl;
    }
  }
  u /= count;
  return u;
  // std::cout << "u=" << u << endl;
}

float Boid::meanVelX(std::vector<Boid> &boids)
{
  float u = 0;
  for (int i = 0; i < boids.size(); i++)
  {
    float a = boids[i].velocity().x();
    u += a;
  }
  u /= boids.size();
  return u;
}

float Boid::meanVelY(std::vector<Boid> &boids)
{
  float u = 0;
  for (int i = 0; i < boids.size(); i++)
  {
    float a = boids[i].velocity().y();
    u += a;
  }
  u /= boids.size();
  return u;
}

float Boid::meanVel(std::vector<Boid> &boids)
{
  float u = 0;
  for (int i = 0; i < boids.size(); i++)
  {
    float a = boids[i].velocity().norm();
    u += a;
  }
  u /= boids.size();
  return u;
}