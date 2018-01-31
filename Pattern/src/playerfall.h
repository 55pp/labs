#ifndef PLAYERFALL_H
#define PLAYERFALL_H

#include "ianimation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

class PlayerFall : public IAnimation
{
public:
  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
  {
    sf::Image image_jump;
    image_jump.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
                            "Sprites/player/player-jump.png");
    texture->loadFromImage(image_jump);
    int width = sprite.getTextureRect().width;
    int height = sprite.getTextureRect().height;
    int x_pos = sprite.getTextureRect().left;
    if (x_pos >= 96) {
      x_pos = 96;
      // std::cout << "yep" << std::endl;
    } else {
      x_pos += 32;
      // std::cout << "nope" << std::endl;
    }
    sf::IntRect new_rect = sf::IntRect(x_pos, 0, width, height);
    //    std::cout << sprite.getTextureRect().left << " " << new_rect.left
    //              << std::endl;
    sprite.setTexture(*texture);
    sprite.setTextureRect(new_rect);
  }
  ~PlayerFall() {}
};

#endif // PLAYERFALL_H
