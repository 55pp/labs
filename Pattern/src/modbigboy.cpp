#include "modbigboy.h"

ModBigBoy::ModBigBoy(std::shared_ptr<Dummy> bul)
  : Modifications(bul)
{
  bullet->health_ = 500;
  bullet->sprite_.setScale(4, 4);
  bullet->width_ *= 4;
  bullet->height_ *= 4;
}

void
ModBigBoy::update(const double& time)
{
  bullet->update(time);
  position_x_ = bullet->position_x_;
  position_y_ = bullet->position_y_;
}
