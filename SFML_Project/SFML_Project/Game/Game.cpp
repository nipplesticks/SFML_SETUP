#include "Game.h"
#include "Utility/Timer.h"
#include "States/StateHandler.h"
#include "States/MainMenu.h"
#include "Utility/Atlas.h"
#include "Utility/Globals.h"

Game::DrawQueue Game::GAME_DRAW_QUEUE;
std::mutex Game::GAME_EVENT_LOCK;
float Global::WIN_X = 0.0f;
float Global::WIN_Y = 0.0f;

Game::Game(sf::RenderTarget* renderTarget_p)
{
  Atlas::GetInstance()->LoadTexture("default_button", "Assets/Buttons/default_button.jpg");
  Atlas::GetInstance()->LoadFont("default_font", "Assets/Fonts/defaultFont.TTF");

  myRenderTarget_p = renderTarget_p;


  myStateHandler_p = StateHandler::GetInstance();
  myStateHandler_p->PushState(new MainMenu);
}

Game::~Game()
{

}

void Game::Run()
{
  myRequestedExit = false;
  myIsRunning = true;
  myRenderTarget_p->setActive(true);
  float fpsTimer = 0.0f;
  size_t frames = 0;

  Timer deltaTime;
  deltaTime.Start();
  while (!myRequestedExit)
  {
    HandleEvents();
    float dt = (float)deltaTime.Stop();
    if (myLostFocus)
      continue;

    frames++;
    fpsTimer += dt;

    sf::Vector2f mp;

    if ((sf::RenderWindow*)myRenderTarget_p)
      mp = (sf::Vector2f)sf::Mouse::getPosition(*(sf::RenderWindow*)myRenderTarget_p);
    else if ((sf::Window*)myRenderTarget_p)
      mp = (sf::Vector2f)sf::Mouse::getPosition(*(sf::Window*)myRenderTarget_p);
    else
      mp = (sf::Vector2f)sf::Mouse::getPosition();

    myStateHandler_p->Update(dt, mp);
    myRenderTarget_p->clear();
    myStateHandler_p->Draw(myRenderTarget_p);
    GAME_DRAW_QUEUE.Flush(myRenderTarget_p);

    if ((sf::RenderWindow*)myRenderTarget_p)
      ((sf::RenderWindow*)myRenderTarget_p)->display();
    else if ((sf::Window*)myRenderTarget_p)
      ((sf::Window*)myRenderTarget_p)->display();

    if (fpsTimer > 5.0f)
    {
      myFps = frames / fpsTimer;
      myMpf = (fpsTimer * 1000.f) / frames;
      fpsTimer = 0;
      frames = 0;
    }
  }

  myIsRunning = false;
}

bool Game::IsRunning()
{
  return myIsRunning;
}

void Game::Exit()
{
  myRequestedExit = true;
}

void Game::PushEvent(sf::Event e)
{
  GAME_EVENT_LOCK.lock();
  myEvents.push_back(e);
  GAME_EVENT_LOCK.unlock();
}

void Game::HandleEvents()
{
  GAME_EVENT_LOCK.lock();
  for (auto& e : myEvents)
  {
    switch (e.type)
    {
    case sf::Event::LostFocus:
      myLostFocus = true;
      break;
    case sf::Event::GainedFocus:
      myLostFocus = false;
      break;
    case sf::Event::MouseButtonReleased:
    {
      int asdsad = 123;
      break;
    }
    default:
      break;
    }
    
    for (auto& s : EventSubscriber::SUBSCRIBERS[e.type])
    {
      if (s.second)
        s.first->OnEvent(e);
    }
  }
  myEvents.clear();
  GAME_EVENT_LOCK.unlock();
}

float Game::GetFPS() const
{
  return myFps;
}

float Game::GetMPF() const
{
  return myMpf;
}

Game::DrawQueue::DrawQueue(size_t queueSize)
{
  nrOfObjectInQueue = 0;
  queue.resize(queueSize);
}

void Game::DrawQueue::Push(const RenderObject& renderObject)
{
  queue[nrOfObjectInQueue++] = renderObject;
  if (queue.size() == nrOfObjectInQueue)
  {
    queue.resize((size_t)(queue.size() * 1.5));
  }
}

void Game::DrawQueue::Flush(sf::RenderTarget* target_p)
{
  std::sort(queue.begin(), queue.end());
  for (size_t i = 0; i < nrOfObjectInQueue; i++)
  {
    auto drawVec = queue[i].GetDrawables();
    for (auto& d : *drawVec)
      target_p->draw(*d);
  }
  nrOfObjectInQueue = 0;
}
