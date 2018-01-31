#include "redenemy.h"
#include "bigenemy.h"

RedEnemy::RedEnemy()
{
}

std::shared_ptr<Enemy>
RedEnemy::createObject(Player* gamer, Level* lvl, double&& x, double&& y)
{
  return std::make_shared<BigEnemy>(gamer, lvl, std::move(x), std::move(y));
}
