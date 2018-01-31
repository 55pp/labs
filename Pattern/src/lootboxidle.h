//#ifndef LOOTBOXIDLE_H
//#define LOOTBOXIDLE_H
//#include "ianimation.h"
//#include <iostream>

// class LootBoxIdle : public IAnimation
//{
// public:
//  LootBoxIdle() {}
//  virtual void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite&
//  sprite)
//  {
//    sf::Image image;
//    image.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
//                       "Sprites/misc/health.png");
//    //    sf::Texture txt;
//    texture->loadFromImage(image);
//    //    texture = txt;
//    //    texture.loadFromImage(image);
//    if (x_pos >= (frame_count - 1) * width) {
//      x_pos = 0;
//    } else {
//      x_pos += width;
//      //      x_pos = 0;
//    }
//    //    std::cout << x_pos << std::endl;
//    x_pos = (x_pos / width) * width;
//    sf::IntRect new_rect = sf::IntRect(x_pos, 0, width, height);
//    sprite.setTexture(*texture);
//    sprite.setTextureRect(new_rect);
//  }
//  ~LootBoxIdle() {}
// private:
//  int x_pos = 0;
//  int frame_count = 4;
//  int width = 14;
//  int height = 19;
//};

//#endif // LOOTBOXIDLE_H
