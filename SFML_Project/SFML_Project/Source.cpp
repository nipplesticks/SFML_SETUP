#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game/Game.h"
#include "Game/Utility/Globals.h"

int main()
{
  std::string title = "SFML";
  sf::RenderWindow wnd(sf::VideoMode(1280, 720), title);
  Global::WIN_X = 1280.f;
  Global::WIN_Y = 720.f;
  wnd.setActive(false);
  Game app(&wnd);

  sf::Thread gameThread(&Game::Run, &app);

  gameThread.launch();

  while (wnd.isOpen())
  {
    sf::Event e;
    while (wnd.pollEvent(e))
    {
      app.PushEvent(e);
      switch (e.type)
      {
      case sf::Event::Closed:
        app.Exit();
        while (app.IsRunning());
        wnd.close();
        break;
      default:
        break;
      }
    }

    wnd.setTitle(title + " [MSPF:" + std::to_string(app.GetMPF()) + " FPS:" + std::to_string(app.GetFPS()) + "]");

  }

  gameThread.terminate();

  return 0;
}