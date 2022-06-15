#include "MainMenu.h"
#include <iostream>
#include "../Utility/Globals.h"

#define START_BUTTON 0
#define OPTION_BUTTON (START_BUTTON + 1)
#define EXIT_BUTTON (OPTION_BUTTON + 1)

MainMenu::MainMenu() : State()
{
  myButtons.push_back(Button());
  myButtons.push_back(Button());
  myButtons.push_back(Button());
  
  myButtons[START_BUTTON].Bind(&MainMenu::TestPrint, this, std::string("Start Button Pressed"));
  myButtons[START_BUTTON].SetString("Start Game");
  myButtons[START_BUTTON].SetupTextColors(sf::Color::Black, sf::Color::Green, sf::Color::Red);
  myButtons[START_BUTTON].setOrigin(myButtons[START_BUTTON].getSize() * 0.5f);
  myButtons[OPTION_BUTTON].Bind(&MainMenu::TestPrint, this, std::string("Option Button Pressed"));
  myButtons[OPTION_BUTTON].SetString("Options");
  myButtons[OPTION_BUTTON].SetupTextColors(sf::Color::Black, sf::Color::Green, sf::Color::Red);
  myButtons[OPTION_BUTTON].setOrigin(myButtons[START_BUTTON].getSize() * 0.5f);
  myButtons[EXIT_BUTTON].Bind(&MainMenu::TestPrint, this, std::string("Exit Button Pressed"));
  myButtons[EXIT_BUTTON].SetString("Exit");
  myButtons[EXIT_BUTTON].SetupTextColors(sf::Color::Black, sf::Color::Green, sf::Color::Red);
  myButtons[EXIT_BUTTON].setOrigin(myButtons[START_BUTTON].getSize() * 0.5f);

  UpdateUI();

  Subscribe(sf::Event::Resized);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float dt, const sf::Vector2f& mousePosition)
{
  for (auto& b : myButtons)
    b.Update(dt);
}

void MainMenu::Draw()
{
  for (auto& b : myButtons)
    b.PushToQueue();
}

void MainMenu::OnEvent(const sf::Event& e)
{
  switch (e.type)
  {
  case sf::Event::Resized:
    UpdateUI();
  default:
    break;
  }
}

void MainMenu::TestPrint(std::string output)
{
  std::cout << output << std::endl;
}

void MainMenu::Print()
{
  std::cout << "Button pressed\n";
}

void MainMenu::UpdateUI()
{
  sf::Vector2f winSize(Global::WIN_X, Global::WIN_Y);
  sf::Vector2f winCenter = winSize * 0.5f;
  myButtons[OPTION_BUTTON].setPosition(winCenter);
  myButtons[START_BUTTON].setPosition(winCenter - sf::Vector2f(0.0f, myButtons[START_BUTTON].getSize().y * 1.5f));
  myButtons[EXIT_BUTTON].setPosition(winCenter + sf::Vector2f(0.0f, myButtons[START_BUTTON].getSize().y * 1.5f));
}
