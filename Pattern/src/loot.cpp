#include "loot.h"

Loot::Loot(std::string&& _name, double&& x, double&& y, int&& w, int&& h)
  : Entity(std::move(_name), std::move(x), std::move(y), std::move(w),
           std::move(h))
{
}

Loot::Loot(std::string&& _name, sf::FloatRect rect)
  : Entity(std::move(_name), std::move(double(rect.left)),
           std::move(double(rect.top)), std::move(int(rect.width)),
           std::move(int(rect.height)))
{
}

void
Loot::update(const double& time)
{
  //  std::cout << position_x << " " << position_y << std::endl;
  //  if (life == false)
  sprite_.setPosition(float(position_x_ + width_ / 2),
                      float(position_y_ + height_ / 2));
  frame_ += 0.005 * time;
  if (frame_ > 1) {
    animate_->action(texture_, sprite_);
    frame_ = 0;
  }
}
