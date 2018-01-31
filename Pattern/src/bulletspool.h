#ifndef BULLETSPOOL_H
#define BULLETSPOOL_H
#include "bullet.h"
#include <vector>

class BulletsPool
{
public:
  static BulletsPool* getInstance(Level* level);
  static BulletsPool* getInstance();
  std::shared_ptr<Bullet> getBullet(double& x, double& y, int dir);
  void releaseBullet(std::shared_ptr<Bullet> bullet);

  BulletsPool(BulletsPool const&) = delete;
  BulletsPool& operator=(BulletsPool const&) = delete;

private:
  static BulletsPool* hide_pool;
  BulletsPool(Level* level);
  std::vector<std::shared_ptr<Bullet>> pool_;
};

#endif // BULLETSPOOL_H
