#include "modifications.h"

Modifications::Modifications(std::shared_ptr<Dummy> bul)
  : Dummy(std::move(bul->name_), bul->lvl_, std::move(bul->position_x_),
          std::move(bul->position_y_), std::move(bul->width_),
          std::move(bul->height_))
{
  bullet = bul;
  objects_.clear();
}

sf::Sprite
Modifications::getPicture()
{
  return bullet->getPicture();
}

void
Modifications::setSpeed(const double& new_speed)
{
  bullet->setSpeed(new_speed);
}

void
Modifications::update(const double& time)
{
  bullet->update(time);
}
