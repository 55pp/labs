#ifndef BULLETCONSTRUCTOR_H
#define BULLETCONSTRUCTOR_H
#include "bulletbuilder.h"

class BulletConstructor
{
public:
  std::shared_ptr<Bullet> makeBullet(BulletBuilder& builder);
};

#endif // BULLETCONSTRUCTOR_H
