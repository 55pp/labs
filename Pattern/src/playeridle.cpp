//#include "playeridle.h"

// void
// PlayerIdle::action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
//{
//  texture = texture_;
//  x_pos = sprite.getTextureRect().left;
//  if (x_pos >= 96) {
//    x_pos = 0;
//  } else {
//    x_pos += 32;
//  }
//  x_pos = (x_pos / 32) * 32;
//  sf::IntRect new_rect = sf::IntRect(x_pos, 0, 32, 37);
//  sprite.setTexture(*texture);
//  sprite.setTextureRect(new_rect);
//}

// PlayerIdle::PlayerIdle()
//{
//  sf::Image image;
//  image.loadFromFile("/home/konstantin/QtProjects/Pattern/src/Resource/"
//                     "Sprites/player/player-idle.png");
//  texture_ = std::make_shared<sf::Texture>();
//  texture_->loadFromImage(image);
//}
