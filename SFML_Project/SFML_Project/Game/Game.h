#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <deque>
#include <mutex>

class Game
{
public:
  struct DrawQueue
  {
    size_t nrOfObjectInQueue;
    std::vector<RenderObject> queue;
    DrawQueue(size_t queueSize = 256);
    void Push(const RenderObject& renderObject);
    void Flush(sf::RenderTarget* target_p);
  };

  static std::mutex GAME_EVENT_LOCK;
  static DrawQueue GAME_DRAW_QUEUE;

  Game(sf::RenderTarget* renderTarget_p);
  ~Game();

  void Run();
  bool IsRunning();
  void Exit();
  void Update(float dt, const sf::Vector2f& mousePosition);
  void Draw(sf::RenderTarget* renderTarget_p);
  void PushEvent(sf::Event e);
  void HandleEvents();
  float GetFPS() const;
  float GetMPF() const;

private:
  sf::RenderTarget* myRenderTarget_p = nullptr;
  bool myIsRunning = false;
  bool myRequestedExit = true;
  bool myLostFocus = false;
  float myFps = 0.0f;
  float myMpf = 0.0f;
  std::deque<sf::Event> myEvents;
};