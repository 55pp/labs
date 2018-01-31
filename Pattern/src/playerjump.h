#ifndef PLAYERJUMP_H
#define PLAYERJUMP_H
#include "ianimation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

class PlayerJump : public IAnimation
{
public:
  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
  {
    sf::Image image_jump;
    image_jump.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
                            "Sprites/player/player-jump.png");
    texture->loadFromImage(image_jump);
    //    int width = sprite.getTextureRect().width;
    //    int height = sprite.getTextureRect().height;
    x_pos = sprite.getTextureRect().left;
    if (x_pos >= 64) {
      x_pos = 64;
      // std::cout << "yep" << std::endl;
    } else {
      x_pos += 32;
      // std::cout << "nope" << std::endl;
    }
    x_pos = (x_pos / 32) * 32;
    sf::IntRect new_rect = sf::IntRect(x_pos, 0, 32, 36);
    //    std::cout << sprite.getTextureRect().left << " " << new_rect.left
    //              << std::endl;
    sprite.setTexture(*texture);
    sprite.setTextureRect(new_rect);
  }
  ~PlayerJump() {}
private:
  int x_pos = 0;
};

#endif // PLAYERJUMP_H
