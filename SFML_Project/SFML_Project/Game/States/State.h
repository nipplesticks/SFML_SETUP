#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/EventSubscriber.h"

class State : public EventSubscriber
{
public:
  State() : EventSubscriber() {}
  virtual ~State() = default;
  virtual void PreUpdate(float dt, const sf::Vector2f& mousePosition) = 0;
  virtual void Update(float dt, const sf::Vector2f& mousePosition) = 0;
  virtual void Draw() = 0;
  virtual void LateUpdate(float dt, const sf::Vector2f& mousePosition) = 0;
};