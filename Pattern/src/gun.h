#ifndef GUN_H
#define GUN_H
#include "bullet.h"

class Gun
{
public:
  Gun(std::shared_ptr<Bullet> bullet);
  std::shared_ptr<Bullet> shoot(Level* lvl, double x, double y, int&& dir);

  std::shared_ptr<Bullet> prototype() const;
  void setPrototype(const std::shared_ptr<Bullet>& prototype);

private:
  std::shared_ptr<Bullet> prototype_;
};

#endif // GUN_H
