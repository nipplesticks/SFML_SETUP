#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Atlas
{
private:
  Atlas() = default;
  ~Atlas() = default;
public:
  static Atlas* GetInstance();
  void LoadTexture(const std::string& textureName, const std::string& path);
  void LoadFont(const std::string& fontName, const std::string& path);
  sf::Texture* GetTexture(const std::string& textureName);
  sf::Font* GetFont(const std::string& fontName);

private:
  static Atlas gAtlas;
  std::unordered_map<std::string, sf::Texture> myTextureAtlas;
  std::unordered_map<std::string, sf::Font> myFontAtlas;
};