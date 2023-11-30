#include "StateHandler.h"

StateHandler StateHandler::gState;

StateHandler* StateHandler::GetInstance()
{
    return &gState;
}

void StateHandler::PushState(State* newState_p)
{
  myStateStack.push(newState_p);
}

void StateHandler::PopState()
{
  if (IsEmpty()) return;

  delete myStateStack.top();
  myStateStack.pop();
}

void StateHandler::PopAndPush(State* newState_p)
{
  PopState();
  PushState(newState_p);
}

void StateHandler::Update(float dt, const sf::Vector2f& mousePosition)
{
  myLastDeltaTime = dt;
  myLastMousePosition = mousePosition;
  if (!IsEmpty())
  {
    myStateStack.top()->PreUpdate(myLastDeltaTime, myLastMousePosition);
    myStateStack.top()->Update(myLastDeltaTime, myLastMousePosition);
  }
}

void StateHandler::Draw(sf::RenderTarget* renderTarget_p)
{
  if (!IsEmpty())
  {
    myStateStack.top()->Draw();
    myStateStack.top()->LateUpdate(myLastDeltaTime, myLastMousePosition);
  }
}

bool StateHandler::IsEmpty() const
{
  return myStateStack.empty();
}

size_t StateHandler::Size() const
{
  return myStateStack.size();
}
