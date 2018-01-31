#include "modcolor.h"

ModColor::ModColor(std::shared_ptr<Dummy> bul)
  : Modifications(bul)
{
  bullet->sprite_.setColor(sf::Color(0, 255, 0));
}

void
ModColor::update(const double& time)
{
  bullet->update(time);
  position_x_ = bullet->position_x_;
}
