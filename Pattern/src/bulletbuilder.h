#ifndef BULLETBUILDER_H
#define BULLETBUILDER_H
#include "bullet.h"

class BulletBuilder
{
public:
  BulletBuilder(Level* level, double x, double y, int&& dir);
  virtual ~BulletBuilder() {}
  virtual std::shared_ptr<Bullet> getBullet();
  virtual BulletBuilder* setSize() {}
  virtual BulletBuilder* setColor() {}
  virtual BulletBuilder* setSpeed() {}
protected:
  std::shared_ptr<Bullet> bullet_;
};

#endif // BULLETBUILDER_H
