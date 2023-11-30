#pragma once

#include "State.h"
#include "../UI/Button.h"

class GameState : public State
{
public:
  GameState();
  virtual ~GameState();
  virtual void OnEvent(const sf::Event& e) override;
  virtual void PreUpdate(float dt, const sf::Vector2f& mousePosition) override;
  virtual void Update(float dt, const sf::Vector2f& mousePosition) override;
  virtual void Draw() override;
  virtual void LateUpdate(float dt, const sf::Vector2f& mousePosition) override;

private:
  //Button myButton;
};