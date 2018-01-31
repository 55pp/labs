//#ifndef ENEMYIDLE_H
//#define ENEMYIDLE_H
//#include "ianimation.h"

// class EnemyIdle : public IAnimation
//{
// public:
//  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite&
//  sprite)
//  {
//    sf::Image image_idle;
//    image_idle.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
//                            "Sprites/enemy/frog-idle.png");
//    texture->loadFromImage(image_idle);
//    //    int width = sprite.getTextureRect().width;
//    //    int height = sprite.getTextureRect().height;
//    x_pos = sprite.getTextureRect().left;
//    if (x_pos >= 48) {
//      x_pos = 0;
//    } else {
//      x_pos += 48;
//    }
//    x_pos = (x_pos / 48) * 48;
//    sf::IntRect new_rect = sf::IntRect(x_pos, 0, 48, 36);
//    sprite.setTexture(*texture);
//    sprite.setTextureRect(new_rect);
//  }
//  ~EnemyIdle() {}
//  EnemyIdle() {}
// private:
//  int x_pos = 0;
//};

//#endif // ENEMYIDLE_H
