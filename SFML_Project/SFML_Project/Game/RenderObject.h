#pragma once

#include <SFML/Graphics.hpp>


class RenderObject : public sf::RectangleShape
{
public:
  RenderObject() = default;
  bool operator<(const RenderObject& other);
  void PushToQueue();
  const sf::RectangleShape* GetDrawablePtr() const;
  void SetLayer(int layer);
  int GetLayer() const;

protected:
  int myLayer = 0;
};