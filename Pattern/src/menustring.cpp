#include "menustring.h"

MenuString::MenuString()
{
}

MenuString::MenuString(const std::string& text, const sf::Font& font,
                       const uint& size, const int& x, const int& y)
{
  text_.setString(text);
  text_.setFont(font);
  text_.setCharacterSize(size);
  text_.setPosition(x, y);
}

void
MenuString::setColor(const sf::Color& color)
{
  text_.setFillColor(color);
}

sf::Text
MenuString::text() const
{
  return text_;
}

void
MenuString::setText(const sf::Text& text)
{
  text_ = text;
}
