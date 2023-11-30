#pragma once

#include "State.h"
#include "../UI/Button.h"

class MainMenu : public State
{
public:
  MainMenu();
  virtual ~MainMenu();
  virtual void PreUpdate(float dt, const sf::Vector2f& mousePosition) override;
  virtual void Update(float dt, const sf::Vector2f& mousePosition) override;
  virtual void LateUpdate(float dt, const sf::Vector2f& mousePosition) override;
  virtual void Draw() override;
  virtual void OnEvent(const sf::Event& e) override;
  void TestPrint(std::string output);
  void Print();

private:
  void UpdateUI();
  std::vector<Button> myButtons;
};