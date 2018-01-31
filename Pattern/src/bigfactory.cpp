#include "bigfactory.h"

BigFactory::BigFactory()
{
}

std::shared_ptr<Enemy>
BigFactory::createEnemy(Player* gamer, Level* lvl, double&& x, double&& y)
{
  return std::make_shared<BigEnemy>(gamer, lvl, std::move(x), std::move(y));
}

std::shared_ptr<NPC>
BigFactory::createNPC(Level* lvl, double&& x, double&& y)
{
  return std::make_shared<BigNPC>(lvl, std::move(x), std::move(y));
}
