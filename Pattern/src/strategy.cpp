#include "strategy.h"
#include "bullet.h"

Strategy::Strategy(Bullet* bullet)
{
  bullet_ = bullet;
}

Strategy::~Strategy()
{
  delete bullet_;
}
