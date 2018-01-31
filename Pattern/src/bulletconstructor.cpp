#include "bulletconstructor.h"

std::shared_ptr<Bullet>
BulletConstructor::makeBullet(BulletBuilder& builder)
{
  return builder.setColor()->setSize()->setSpeed()->getBullet();
}
