#include <SFML/Graphics.hpp>
#include "Utility/Timer.h"


int main()
{
  sf::RenderWindow wnd(sf::VideoMode(1280, 720), "SFML");
  sf::CircleShape c(64);

  while (wnd.isOpen())
  {
    sf::Event e;
    while (wnd.pollEvent(e))
    {
      switch (e.type)
      {
      case sf::Event::Closed:
        wnd.close();

        break;
      default:
        break;
      }
    }

    wnd.clear();
    wnd.draw(c);
    wnd.display();
  }

  return 0;
}