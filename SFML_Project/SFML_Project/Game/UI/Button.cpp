#include "Button.h"
#include "../Utility/Atlas.h"
#include <iostream>

Button::Button() : RenderObject({ this, &myText }), sf::RectangleShape()
{
  setTexture(myDefaultTexture_p = myHoverTexture_p = myPressTexture_p = Atlas::GetInstance()->GetTexture("default_button"));
  myText.setFont(*Atlas::GetInstance()->GetFont("default_font"));
  myText.setFillColor(myDefaultTxtColor = myHoverTxtColor = myPressTxtColor = sf::Color::White);
  setFillColor(myDefaultBckColor = myHoverBckColor = myPressBckColor = sf::Color::White);
  setPosition(0, 0);
  setSize(sf::Vector2f(128, 64));
  Subscribe(sf::Event::EventType::MouseMoved);
  Subscribe(sf::Event::EventType::MouseButtonPressed);
  Subscribe(sf::Event::EventType::MouseButtonReleased);
}

Button::Button(const Button& other) : RenderObject(other), EventSubscriber(other), sf::RectangleShape(other)
{
  _copy(other);
}

Button::~Button()
{
  _cleanup();
}
void Button::OnEvent(const sf::Event& e)
{
  sf::Vector2f mp;
  switch (e.type)
  {
  case sf::Event::EventType::MouseMoved:
  {
    mp.x = (float)e.mouseMove.x;
    mp.y = (float)e.mouseMove.y;
    break;
  }
  case sf::Event::EventType::MouseButtonReleased:
  case sf::Event::EventType::MouseButtonPressed:
  {
    mp.x = (float)e.mouseButton.x;
    mp.y = (float)e.mouseButton.y;
    break;
  }
  default:
    return;
  }
  if (getGlobalBounds().contains(mp))
  {
    setTexture(myHoverTexture_p);
    setFillColor(myHoverBckColor);
    myText.setFillColor(myHoverTxtColor);
    if (e.type == sf::Event::EventType::MouseButtonReleased && myFunction_p)
    {
      myFunction_p->Run();
    }
    else if (e.type == sf::Event::EventType::MouseButtonPressed)
    {
      setTexture(myPressTexture_p);
      setFillColor(myPressBckColor);
      myText.setFillColor(myPressTxtColor);
    }
  }
  else
  {
    setTexture(myDefaultTexture_p);
    setFillColor(myDefaultBckColor);
    myText.setFillColor(myDefaultTxtColor);
  }
}

void Button::Update(float dt)
{
  sf::Vector2f rectanglePos = getPosition() - getOrigin();
  sf::Vector2f rectangleSize = getSize();
  myText.setPosition(rectanglePos + rectangleSize * 0.5f);
  myText.setOrigin(sf::Vector2f(myText.getGlobalBounds().width * 0.5f, myText.getGlobalBounds().height * 0.75f));
}

Button& Button::operator=(const Button& other)
{
  if (this != &other)
  {
    _cleanup();
    RenderObject::operator=(other);
    sf::RectangleShape::operator=(other);
    EventSubscriber::operator=(other);
    _copy(other);
  }
  return *this;
}

void Button::SetupTextures(sf::Texture* defaultTexture_p, sf::Texture* hoverTexture_p, sf::Texture* pressTexture_p)
{
  myDefaultTexture_p = defaultTexture_p;
  myHoverTexture_p = myHoverTexture_p;
  myPressTexture_p = pressTexture_p;
}

void Button::SetupBackgroundColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& pressColor)
{
  myDefaultBckColor = defaultColor;
  myHoverBckColor = hoverColor;
  myPressBckColor = pressColor;
}

void Button::SetupTextColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& pressColor)
{
  myDefaultTxtColor = defaultColor;
  myHoverTxtColor = hoverColor;
  myPressTxtColor = pressColor;
}

std::string Button::GetString() const
{
  return myText.getString();
}

void Button::SetString(const std::string& str)
{
  myText.setString(str);
}

void Button::SetCharSize(unsigned int size)
{
  myText.setCharacterSize(size);
}

void Button::SetTextColor(const sf::Color& color)
{
  myText.setFillColor(color);
}

void Button::SetTextOutlineColor(const sf::Color& color)
{
  myText.setOutlineColor(color);
}

void Button::SetTextOutlineThickness(float t)
{
  myText.setOutlineThickness(t);
}

unsigned int Button::GetCharSize() const
{
  return myText.getCharacterSize();
}

void Button::_copy(const Button& other)
{
  myText = other.myText;
  myDefaultTexture_p = other.myDefaultTexture_p;
  myHoverTexture_p = other.myHoverTexture_p;
  myPressTexture_p = other.myPressTexture_p;
  myDefaultBckColor = other.myDefaultBckColor;
  myHoverBckColor = other.myHoverBckColor;
  myPressBckColor = other.myPressBckColor;
  myDefaultTxtColor = other.myDefaultTxtColor;
  myHoverTxtColor = other.myHoverTxtColor;
  myPressTxtColor = other.myPressTxtColor;

  SetDrawables({ this, &myText });

  if (other.myFunction_p != nullptr)
  {
    myFunction_p = (BaseFunction*)malloc(other.myFunction_p->ByteSize());
    if (myFunction_p)
      memcpy(myFunction_p, other.myFunction_p, other.myFunction_p->ByteSize());
  }
}

void Button::_cleanup()
{
  if (myFunction_p)
    delete myFunction_p;
  myFunction_p = nullptr;
}
