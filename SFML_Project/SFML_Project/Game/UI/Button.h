#pragma once
#include "../RenderObject.h"
#include "../Utility/Function.h"
#include "../Utility/EventSubscriber.h"

class Button : public RenderObject, public EventSubscriber, public sf::RectangleShape
{
public:
  Button();
  Button(const Button& other);
  template <typename F>
  void Bind(F function);
  template <typename F, typename A>
  void Bind(F function, A argument);
  template <typename C>
  void Bind(void(C::* function)(), C* object);
  template <typename C, typename A>
  void Bind(void(C::* function)(A), C* object, A argument);

  ~Button();

  virtual void OnEvent(const sf::Event& e) override;

  void Update(float dt);

  Button& operator=(const Button& other);

  void SetupTextures(sf::Texture* defaultTexture_p,
                     sf::Texture* hoverTexture_p,
                     sf::Texture* pressTexture_p);

  void SetupBackgroundColors(const sf::Color& defaultColor,
                             const sf::Color& hoverColor,
                             const sf::Color& pressColor);

  void SetupTextColors(const sf::Color& defaultColor,
                       const sf::Color& hoverColor,
                       const sf::Color& pressColor);


  std::string GetString() const;
  void SetString(const std::string& str);
  void SetCharSize(unsigned int size);
  void SetTextColor(const sf::Color& color);
  void SetTextOutlineColor(const sf::Color& color);
  void SetTextOutlineThickness(float t);
  unsigned int GetCharSize() const;

private:
  void _copy(const Button& other);
  void _cleanup();
  sf::Text myText;

private:
  BaseFunction* myFunction_p = nullptr;
  sf::Texture* myDefaultTexture_p = nullptr;
  sf::Texture* myHoverTexture_p = nullptr;
  sf::Texture* myPressTexture_p = nullptr;
  sf::Color myDefaultBckColor;
  sf::Color myHoverBckColor;
  sf::Color myPressBckColor;
  sf::Color myDefaultTxtColor;
  sf::Color myHoverTxtColor;
  sf::Color myPressTxtColor;
};

template<typename F>
inline void Button::Bind(F function)
{
  _cleanup();
  myFunction_p = new Function<F>(function);
}

template<typename F, typename A>
inline void Button::Bind(F function, A argument)
{
  _cleanup();
  myFunction_p = new FunctionWithArgs<F, A>(function, argument);
}

template<typename C>
inline void Button::Bind(void(C::* function)(), C* object)
{
  _cleanup();
  myFunction_p = new MemberFunction<C>(function, object);
}

template<typename C, typename A>
inline void Button::Bind(void(C::* function)(A), C* object, A argument)
{
  _cleanup();
  myFunction_p = new MemberFunctionWithArgs<C, A>(function, object, argument);
}
