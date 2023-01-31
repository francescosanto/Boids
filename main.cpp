#include "boid.h"
#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;    //Da togliere

int main()
{
  ofstream output_file1("dati1.txt");
  if (!output_file1.is_open())
  {
      cout << "Impossibile aprire il file di uscita." << '\n';
      return 1;
  }
  ofstream output_file2("dati2.txt");
  if (!output_file2.is_open())
  {
      cout << "Impossibile aprire il file di uscita." << '\n';
      return 1;
  }
  ofstream output_file3("dati3.txt");
  if (!output_file3.is_open())
  {
      cout << "Impossibile aprire il file di uscita." << '\n';
      return 1;
  }
  ofstream output_file4("dati4.txt");
  if (!output_file4.is_open())
  {
      cout << "Impossibile aprire il file di uscita." << '\n';
      return 1;
  }
  ofstream output_file_pos("dati_pos.txt");
  if (!output_file_pos.is_open())
  {
      cout << "Impossibile aprire il file di uscita." << '\n';
      return 1;
  }

  double parameterS;
  double parameterC;
  double parameterA;
  int cNumber;
  double bNumber;

  BVector::setBorders(10000, 10000);    //superfluo 
  Boid::setmaxVel(200); //superfluo

  int minPos = 0;
  int maxPos = BVector::width();
  int minVel = -200;
  int maxVel = 200;
  //DA settare (qua o cin)

  cout << "Inserire il valore del coefficiente di separazione: ";
  cin >> parameterS;
  cout << "Inserire il valore del coefficiente di coesione: ";
  cin >> parameterC;
  cout << "Inserire il valore del coefficiente di allineamento: ";
  cin >> parameterA;
  cout << "Inserire il numero di boids desiderati: ";
  cin >> bNumber;
  cout << "Inserire il numero di evoluzioni: ";
  cin >> cNumber;

  std::vector<Boid> flock(bNumber);
  for (int j = 0; j < flock.size(); j++)
  {
    flock[j].setRandomValues();
    float a = flock[j].velocity().x();    //per debug
    float b = flock[j].velocity().y();
    std::cout << "x = " << a << '\n';
    cout << "y = " << b << '\n';
    flock[j].setValueS(parameterS);
    flock[j].setValueC(parameterC);
    flock[j].setValueA(parameterA);
  }

  for (int i = 0; i < cNumber; i++) // i < numero evoluzioni
  {
    /*std::vector<Boid> u;
    u = flock;*/
    //std::cout << "Evoluzione " << i << '\n';
    for (int k = 0; k < flock.size(); k++)
    {
       flock[k].newvalues(flock);
       float posx = flock[k].position().x();
       float posy = flock[k].position().y();
       output_file_pos << posx << " " << posy << '\n';
    }

    float distanzamedia = flock[0].meanDist(flock);
    float velocitaxmedia = flock[0].meanVelX(flock);
    float velocitaymedia = flock[0].meanVelY(flock);
    float velocitamedia = flock[0].meanVel(flock);
    /*std::cout << distanzamedia << '\n';
    std::cout << velocitaxmedia << '\n';
    std::cout << velocitaymedia << '\n';
    std::cout << velocitamedia << '\n';*/

      output_file1 << i << " " << distanzamedia << '\n';
      output_file2 << velocitaxmedia << '\n';
      output_file3 << velocitaymedia << '\n';
      output_file4 << velocitamedia << '\n';
  }

  output_file1.close();
  output_file2.close();
  output_file3.close();
  output_file4.close();
  output_file_pos.close();
}