#include "simpleenemy.h"

SimpleEnemy::SimpleEnemy()
{
}

std::shared_ptr<Enemy>
SimpleEnemy::createObject(Player* gamer, Level* lvl, double&& x, double&& y)
{
  return std::make_shared<Enemy>(gamer, lvl, std::move(x), std::move(y));
}
