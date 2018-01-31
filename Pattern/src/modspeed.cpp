#include "modspeed.h"

ModSpeed::ModSpeed(std::shared_ptr<Dummy> bul)
  : Modifications(bul)
{
  bullet->setSpeed(bullet->speed_ + more_speed);
}

void
ModSpeed::update(const double& time)
{
  bullet->update(time);
  position_x_ = bullet.get()->position_x_;
}
