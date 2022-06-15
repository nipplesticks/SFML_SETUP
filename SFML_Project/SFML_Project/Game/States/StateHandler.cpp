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
  if (!IsEmpty())
  {
    myStateStack.top()->Update(dt, mousePosition);
  }
}

void StateHandler::Draw(sf::RenderTarget* renderTarget_p)
{
  if (!IsEmpty())
  {
    myStateStack.top()->Draw();
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
