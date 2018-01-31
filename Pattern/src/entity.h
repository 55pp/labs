#ifndef ENTITY_H
#define ENTITY_H
#include "ianimation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Entity
{
public:
  Entity(sf::Image& image, std::string&& name, double&& x, double&& y, int&& w,
         int&& h);

  Entity(const std::string&& name, const double&& x, const double&& y,
         const int&& w, const int&& h);

  sf::FloatRect getRect();

  virtual sf::Sprite getPicture();

  virtual void update(const double& time) = 0;

  virtual ~Entity() {}

  // sf::FloatRect getRect();

  //  double getPosition_x() const;
  //  void setPosition_x(double value);

  //  double getPosition_y() const;
  //  void setPosition_y(double value);

  //  int getWidth() const;
  //  void setWidth(int value);

  //  int getHeight() const;
  //  void setHeight(int value);

  //  bool getLife() const;
  //  void setLife(bool value);

  //  sf::Texture getTexture() const;
  //  void setTexture(const sf::Texture& value);

  //  sf::Sprite getSprite() const;
  //  void setSprite(const sf::Sprite& value);

  //  sf::String getName() const;
  //  void setName(const sf::String& value);

  //  int getHealth() const;
  //  void setHealth(int value);

  double position_x_;
  double position_y_;
  int width_;
  int height_;
  bool life_;
  int health_ = 100;
  double frame_ = 0;
  std::shared_ptr<sf::Texture> texture_;
  sf::Sprite sprite_;
  std::string name_;
  //  IAnimation* animate_;
  std::shared_ptr<IAnimation> animate_;

private:
};

#endif // ENTITY_H
