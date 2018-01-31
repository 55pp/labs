#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include "bridge.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

class RenderWindow : public Bridge
{
public:
  RenderWindow(sf::VideoMode&& video_mode, std::string&& title);
  void draw(sf::Sprite& sprite, std::string&& name_object);
  void display();
  sf::RenderWindow& getWindow();
  ~RenderWindow();

private:
  std::shared_ptr<sf::RenderWindow> window_;
};

#endif // RENDERWINDOW_H
