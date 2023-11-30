#pragma once
#include "State.h"
#include <stack>

class StateHandler
{
private:
  StateHandler() = default;
  ~StateHandler() = default;

public:
  static StateHandler* GetInstance();

  void PushState(State* newState_p);
  void PopState();
  void PopAndPush(State* newState_p);
  void Update(float dt, const sf::Vector2f& mousePosition);
  void Draw(sf::RenderTarget* renderTarget_p);
  bool IsEmpty() const;
  size_t Size() const;

private:
  static StateHandler gState;
  std::stack<State*> myStateStack;
  float myLastDeltaTime = 0.0f;
  sf::Vector2f myLastMousePosition;

};

