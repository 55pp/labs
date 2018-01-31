#include "bulletbuilder.h"

BulletBuilder::BulletBuilder(Level* level, double x, double y, int&& dir)
{
  bullet_ = std::make_shared<Bullet>(level, x, y, std::move(dir));
}

std::shared_ptr<Bullet>
BulletBuilder::getBullet()
{
  return bullet_;
}
