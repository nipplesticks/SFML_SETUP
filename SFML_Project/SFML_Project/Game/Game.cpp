#include "Game.h"
#include "Utility/Timer.h"

Game::DrawQueue Game::GAME_DRAW_QUEUE;
std::mutex Game::GAME_EVENT_LOCK;

Game::Game(sf::RenderTarget* renderTarget_p)
{
  myRenderTarget_p = renderTarget_p;
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

    Update(dt, (sf::Vector2f)sf::Mouse::getPosition());

    myRenderTarget_p->clear();

    Draw(myRenderTarget_p);

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

void Game::Update(float dt, const sf::Vector2f& mousePosition)
{

}

void Game::Draw(sf::RenderTarget* renderTarget_p)
{
  GAME_DRAW_QUEUE.Flush(renderTarget_p);
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
    default:
      break;
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
    target_p->draw(*queue[i].GetDrawablePtr());
  }
  nrOfObjectInQueue = 0;
}
