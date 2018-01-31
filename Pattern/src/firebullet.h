#ifndef FIREBULLET_H
#define FIREBULLET_H
#include "bulletbuilder.h"

class FireBullet : public BulletBuilder
{
public:
  FireBullet(Level* level, double x, double y, int&& dir);
  BulletBuilder* setColor();
  BulletBuilder* setSpeed();
};

#endif // FIREBULLET_H
