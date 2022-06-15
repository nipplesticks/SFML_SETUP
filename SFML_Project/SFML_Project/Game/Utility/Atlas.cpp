#include "Atlas.h"

Atlas Atlas::gAtlas;

Atlas* Atlas::GetInstance()
{
  return &gAtlas;
}

void Atlas::LoadTexture(const std::string& textureName, const std::string& path)
{
  myTextureAtlas[textureName].loadFromFile(path);
}

void Atlas::LoadFont(const std::string& fontName, const std::string& path)
{
  myFontAtlas[fontName].loadFromFile(path);
}

sf::Texture* Atlas::GetTexture(const std::string& textureName)
{
  return &myTextureAtlas[textureName];
}

sf::Font* Atlas::GetFont(const std::string& fontName)
{
  return &myFontAtlas[fontName];
}
