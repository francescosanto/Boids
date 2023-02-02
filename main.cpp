#include "boid.h"
#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace std;    //Da togliere

int main()
{
  /*
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
  */

  double parameterS;
  double parameterC;
  double parameterA;
  int cNumber;
  double bNumber;

  BVector::setBorders(1000, 1000);    //superfluo 
  Boid::setmaxVel(50); //superfluo

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
  /*
  cout << "Inserire il numero di evoluzioni: ";
  cin >> cNumber;
  */

  std::vector<Boid> flock(bNumber);
  for (int k = 0; k < flock.size(); k++)
  {
    flock[k].setRandomValues();
    flock[k].setValueS(parameterS);
    flock[k].setValueC(parameterC);
    flock[k].setValueA(parameterA);
  }

  int drawSize = 3;

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Boids");
  window.setFramerateLimit(10);

  while(window.isOpen()) {
    //reacts to Events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) 
        window.close();
    }

    window.clear(); //clear with default color (black)
    //draw fireflies

    /*std::vector<Boid> u;
    u = flock;*/
    //std::cout << "Evoluzione " << i << '\n';
    for (int k = 0; k < flock.size(); k++) //operatore che scorre il flock
    {
      flock[k].resultantforce(flock);
    }
    for (int k = 0; k < flock.size(); k++)
    {
      flock[k].newvalues();
      // float posx = flock[k].position().x();
      // float posy = flock[k].position().y();

      sf::CircleShape circle(drawSize);
      BVector position = flock[k].position();
      circle.setPosition(position.x(), position.y());

      circle.setFillColor(sf::Color::Yellow);
      window.draw(circle);       
    }

    // float distanzamedia = flock[0].meanDist(flock);
    // float velocitaxmedia = flock[0].meanVelX(flock);
    // float velocitaymedia = flock[0].meanVelY(flock);
    // float velocitamedia = flock[0].meanVel(flock);
    /*std::cout << distanzamedia << '\n';
    std::cout << velocitaxmedia << '\n';
    std::cout << velocitaymedia << '\n';
    std::cout << velocitamedia << '\n';*/

      //output_file1 << i << " " << distanzamedia << '\n';
      // output_file2 << velocitaxmedia << '\n';
      // output_file3 << velocitaymedia << '\n';
      // output_file4 << velocitamedia << '\n';

    //using namespace std::chrono_literals;
    //std::this_thread::sleep_for(10ms);
    
    window.display();
  }

  /*
  output_file1.close();
  output_file2.close();
  output_file3.close();
  output_file4.close();
  output_file_pos.close();
  */
}



