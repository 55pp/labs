#ifndef MENUSTRING_H
#define MENUSTRING_H
#include <SFML/Graphics.hpp>

class MenuString
{
public:
  MenuString();
  MenuString(const std::string& text, const sf::Font& font, const uint& size,
             const int& x, const int& y);
  sf::Text text() const;
  void setText(const sf::Text& text);

  void setColor(const sf::Color& color);

private:
  sf::Text text_;
};

#endif // MENUSTRING_H
