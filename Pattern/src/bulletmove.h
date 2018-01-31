#ifndef BULLETMOVE_H
#define BULLETMOVE_H
#include "ianimation.h"

class BulletMove : public IAnimation
{
public:
  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
  {
    sf::Image image_move;
    image_move.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
                            "Sprites/misc/shoot.png");
    //    sf::Texture txt;
    texture->loadFromImage(image_move);
    //    texture = txt;
    x_pos = sprite.getTextureRect().left;
    if (x_pos >= 42) {
      x_pos = 0;
    } else {
      x_pos += width;
    }
    x_pos = (x_pos / width) * width;
    sf::IntRect new_rect = sf::IntRect(x_pos, 0, width, height);
    sprite.setTexture(*texture);
    sprite.setTextureRect(new_rect);
  }
  ~BulletMove() {}
private:
  int x_pos = 0;
  int width = 21;
  int height = 11;
};

#endif // BULLETMOVE_H
