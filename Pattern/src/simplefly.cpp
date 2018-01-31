#include "simplefly.h"
#include "bullet.h"

SimpleFly::SimpleFly(Bullet* bullet)
  : Strategy(bullet)
{
}

void
SimpleFly::doIt(Bullet* bullet)
{
  bullet->velocity_x_ = bullet->speed_ * bullet->direction_;
}

SimpleFly::~SimpleFly()
{
  delete bullet_;
}
