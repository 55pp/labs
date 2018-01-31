#include "zigzagfly.h"
#include "bullet.h"

ZigZagFly::ZigZagFly(Bullet* bullet)
  : Strategy(bullet)
{
}

void
ZigZagFly::doIt(Bullet* bullet)
{
  bullet->velocity_x_ = bullet->speed_ * bullet->direction_;
  bullet->sprite_.setRotation(angle_rotation);
  if (delay != 0) {
    delay--;
  } else {
    delay = 100;
    direction_y_ = -direction_y_;
    angle_rotation = -angle_rotation;
  }
  bullet->velocity_y_ = bullet->speed_ / 2 * direction_y_;
}

ZigZagFly::~ZigZagFly()
{
  delete bullet_;
}
