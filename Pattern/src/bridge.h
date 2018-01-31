#ifndef BRIDGE_H
#define BRIDGE_H
#include <SFML/Graphics.hpp>

class Bridge
{
public:
  virtual void draw(sf::Sprite& sprite, std::string&& name_object) = 0;
  virtual void display() = 0;
  virtual ~Bridge() {}
};
#endif // BRIDGE_H
