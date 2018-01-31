#include "firebullet.h"

FireBullet::FireBullet(Level* level, double x, double y, int&& dir)
  : BulletBuilder(level, x, y, std::move(dir))
{
}

BulletBuilder*
FireBullet::setColor()
{
  bullet_->sprite_.setColor(sf::Color(255, 0, 0));
  return this;
}

BulletBuilder*
FireBullet::setSpeed()
{
  bullet_->speed_ = 0.2;
  return this;
}
