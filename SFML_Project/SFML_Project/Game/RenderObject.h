#pragma once

#include <SFML/Graphics.hpp>

class RenderObject
{
public:
  RenderObject(const std::vector<sf::Drawable*>& drawThis = {});
  bool operator<(const RenderObject& other);
  virtual void PushToQueue();
  const std::vector<sf::Drawable*>* GetDrawables() const;
  void SetLayer(int layer);
  int GetLayer() const;
  void SetDrawables(const std::vector<sf::Drawable*>& drawThis);

protected:
  int myLayer = 0;
  std::vector<sf::Drawable*> myDrawables;
};