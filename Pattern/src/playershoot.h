#ifndef PLAYERSHOOT_H
#define PLAYERSHOOT_H
#include "ianimation.h"

class PlayerShoot : public IAnimation
{
public:
  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
  {
    sf::Image image_jump;
    image_jump.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
                            "Sprites/player/player-shoot.png");
    //    sf::Texture txt;
    texture->loadFromImage(image_jump);
    //    texture = txt;
    x_pos = sprite.getTextureRect().left;
    if (x_pos >= 37) {
      x_pos = 37;
    } else {
      x_pos += 37;
    }
    x_pos = (x_pos / 37) * 37;
    sf::IntRect new_rect = sf::IntRect(x_pos, 0, 37, 37);
    sprite.setTexture(*texture);
    sprite.setTextureRect(new_rect);
  }
  ~PlayerShoot() {}
private:
  int x_pos = 0;
};

#endif // PLAYERSHOOT_H
