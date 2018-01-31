#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H
#include "ianimation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

class PlayerMove : public IAnimation
{
public:
  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
  {
    sf::Image image_move;
    image_move.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
                            "Sprites/player/player-run.png");
    texture->loadFromImage(image_move);
    //    int width = sprite.getTextureRect().width;
    //    int height = sprite.getTextureRect().height;
    x_pos = sprite.getTextureRect().left;
    if (x_pos >= 224) {
      x_pos = 0;
    } else {
      x_pos += 32;
    }
    x_pos = (x_pos / 32) * 32;
    // std::cout << "move: " << x_pos << std::endl;
    sf::IntRect new_rect = sf::IntRect(x_pos, 0, 32, 37);
    sprite.setTexture(*texture);
    sprite.setTextureRect(new_rect);
  }
  ~PlayerMove() {}
private:
  int x_pos = 0;
};
#endif // PLAYERMOVE_H
