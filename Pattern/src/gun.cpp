#include "gun.h"

Gun::Gun(std::shared_ptr<Bullet> bullet)
  : prototype_(bullet)
{
}

std::shared_ptr<Bullet>
Gun::shoot(Level* lvl, double x, double y, int&& dir)
{
  //  std::cout << prototype_.use_count() << std::endl;
  return prototype_->clone(lvl, x, y, std::move(dir));
}

std::shared_ptr<Bullet>
Gun::prototype() const
{
  return prototype_;
}

void
Gun::setPrototype(const std::shared_ptr<Bullet>& prototype)
{
  prototype_ = std::move(prototype);
}
