#include "RenderObject.h"
#include "Game.h"

RenderObject::RenderObject(const std::vector<sf::Drawable*>& drawThis)
{
  SetDrawables(drawThis);
}

bool RenderObject::operator<(const RenderObject& other)
{
    return myLayer < other.myLayer;
}

void RenderObject::PushToQueue()
{
  Game::GAME_DRAW_QUEUE.Push(*this);
}

const std::vector<sf::Drawable*>* RenderObject::GetDrawables() const
{
  return &myDrawables;
}

void RenderObject::SetLayer(int layer)
{
  myLayer = layer;
}

int RenderObject::GetLayer() const
{
  return myLayer;
}

void RenderObject::SetDrawables(const std::vector<sf::Drawable*>& drawThis)
{
  myDrawables = drawThis;
}
