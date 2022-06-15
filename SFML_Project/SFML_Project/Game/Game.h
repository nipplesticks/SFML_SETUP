#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <mutex>
#include "RenderObject.h"

class StateHandler;

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
  StateHandler* myStateHandler_p = nullptr;
};