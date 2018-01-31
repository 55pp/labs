#include "entity.h"

Entity::Entity(sf::Image& image, std::string&& name, double&& x, double&& y,
               int&& w, int&& h)
  : position_x_(x)
  , position_y_(y)
  , width_(w)
  , height_(h)
  , life_(true)
  , name_(name)
  , animate_(nullptr)
{
  //  sf::Texture txt;
  texture_ = std::make_shared<sf::Texture>();
  texture_->loadFromImage(image);
  //  texture_ = txt;
  //  texture.loadFromImage(image);
  sprite_.setTexture(*texture_);
  sprite_.setOrigin(width_ / 2, height_ / 2);
  sprite_.setTextureRect(sf::IntRect(0, 0, width_, height_));
}

Entity::Entity(const std::string&& name, const double&& x, const double&& y,
               const int&& w, const int&& h)
  : position_x_(x)
  , position_y_(y)
  , width_(w)
  , height_(h)
  , life_(true)
  , name_(name)
  , animate_(nullptr)
{
  sprite_.setOrigin(width_ / 2, height_ / 2);
  sprite_.setTextureRect(sf::IntRect(0, 0, width_, height_));
  texture_ = std::make_shared<sf::Texture>();
}

sf::FloatRect
Entity::getRect()
{
  return sf::FloatRect(float(position_x_), float(position_y_), width_, height_);
}

sf::Sprite
Entity::getPicture()
{
  return sprite_;
}

// double
// Entity::getPosition_x() const
//{
//  return position_x;
//}

// void
// Entity::setPosition_x(double value)
//{
//  position_x = value;
//}

// double
// Entity::getPosition_y() const
//{
//  return position_y;
//}

// void
// Entity::setPosition_y(double value)
//{
//  position_y = value;
//}

// int
// Entity::getWidth() const
//{
//  return width;
//}

// void
// Entity::setWidth(int value)
//{
//  width = value;
//}

// int
// Entity::getHeight() const
//{
//  return height;
//}

// void
// Entity::setHeight(int value)
//{
//  height = value;
//}

// bool
// Entity::getLife() const
//{
//  return life;
//}

// void
// Entity::setLife(bool value)
//{
//  life = value;
//}

// sf::Texture
// Entity::getTexture() const
//{
//  return texture;
//}

// void
// Entity::setTexture(const sf::Texture& value)
//{
//  texture = value;
//}

// sf::Sprite
// Entity::getSprite() const
//{
//  return sprite;
//}

// void
// Entity::setSprite(const sf::Sprite& value)
//{
//  sprite = value;
//}

// sf::String
// Entity::getName() const
//{
//  return name;
//}

// void
// Entity::setName(const sf::String& value)
//{
//  name = value;
//}

// int
// Entity::getHealth() const
//{
//  return health;
//}

// void
// Entity::setHealth(int value)
//{
//  health = value;
//}
