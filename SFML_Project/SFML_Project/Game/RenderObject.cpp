#include "RenderObject.h"
#include "Game.h"

bool RenderObject::operator<(const RenderObject& other)
{
    return myLayer < other.myLayer;
}

void RenderObject::PushToQueue()
{
  Game::GAME_DRAW_QUEUE.Push(*this);
}

const sf::RectangleShape* RenderObject::GetDrawablePtr() const
{
  return this;
}

void RenderObject::SetLayer(int layer)
{
  myLayer = layer;
}

int RenderObject::GetLayer() const
{
    return myLayer;
}
