#include "bulletspool.h"

BulletsPool* BulletsPool::hide_pool = NULL;

BulletsPool*
BulletsPool::getInstance(Level* level)
{
  if (hide_pool == NULL) {
    hide_pool = new BulletsPool(level);
  }
  return BulletsPool::hide_pool;
}

BulletsPool*
BulletsPool::getInstance()
{
  return BulletsPool::hide_pool;
}

BulletsPool::BulletsPool(Level* level)
{
  for (int i = 0; i < 50; ++i) {
    auto tmp_bullet = std::make_shared<Bullet>(level, 0, 0, 1);
    pool_.push_back(tmp_bullet);
  }
}

std::shared_ptr<Bullet>
BulletsPool::getBullet(double& x, double& y, int dir)
{
  for (auto& el : pool_) {
    if (el.use_count() == 1) {
      el->position_x_ = x;
      el->position_y_ = y;
      el->direction_ = dir;
      return el;
    }
  }
  return nullptr;
}

void
BulletsPool::releaseBullet(std::shared_ptr<Bullet> bullet)
{
  for (auto& el : pool_) {
    if (el == bullet) {
      //      el->lvl_ = nullptr;
      el->position_x_ = 0;
      el->position_y_ = 0;
    }
  }
}
