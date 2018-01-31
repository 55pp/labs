#include "ianimation.h"

IAnimation::IAnimation(const std::string& file_name, int&& frame_count,
                       bool repeat)
  : end_frame_(frame_count)
  , repeat_(repeat)
{
  //  sf::Image image;
  //  image.loadFromFile(file_name);
  texture_ = std::make_shared<sf::Texture>();
  //  texture_->loadFromImage(image);
  texture_->loadFromFile(file_name);
  width_frame_ = int(texture_->getSize().x) / frame_count;
  height_frame_ = int(texture_->getSize().y);
  start_frame_ = 0;
  current_frame_ = start_frame_;
}

IAnimation::IAnimation(const std::string& file_name, int&& frame_count,
                       int&& start_frame, int&& end_frame, bool repeat)
  : start_frame_(start_frame)
  , end_frame_(end_frame)
  , repeat_(repeat)
{
  //  sf::Image image;
  //  image.loadFromFile(file_name);
  texture_ = std::make_shared<sf::Texture>();
  //  texture_->loadFromImage(image);
  texture_->loadFromFile(file_name);
  width_frame_ = int(texture_->getSize().x) / frame_count;
  height_frame_ = int(texture_->getSize().y);
  current_frame_ = start_frame_;
}

void
IAnimation::action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite)
{
  texture = texture_;
  //    x_pos = sprite.getTextureRect().left;
  if (current_frame_ < (end_frame_ - 1)) {
    ++current_frame_;
  } else if (repeat_) {
    current_frame_ = start_frame_;
  }
  auto x_pos = current_frame_ * width_frame_;
  //    x_pos = (x_pos / 32) * 32;
  sf::IntRect new_rect = sf::IntRect(x_pos, 0, width_frame_, height_frame_);
  sprite.setTexture(*texture);
  sprite.setTextureRect(new_rect);
}

void
IAnimation::action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite,
                   int& current_frame)
{
  texture = texture_;
  //    x_pos = sprite.getTextureRect().left;
  if (current_frame < (end_frame_ - 1)) {
    ++current_frame;
  } else if (repeat_) {
    current_frame = start_frame_;
  }
  auto x_pos = current_frame * width_frame_;
  //    x_pos = (x_pos / 32) * 32;
  sf::IntRect new_rect = sf::IntRect(x_pos, 0, width_frame_, height_frame_);
  sprite.setTexture(*texture);
  sprite.setTextureRect(new_rect);
}
