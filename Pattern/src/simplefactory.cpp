#include "simplefactory.h"

SimpleFactory::SimpleFactory()
{
}

std::shared_ptr<Enemy>
SimpleFactory::createEnemy(Player* gamer, Level* lvl, double&& x, double&& y)
{
  return std::make_shared<Enemy>(gamer, lvl, std::move(x), std::move(y));
}

std::shared_ptr<NPC>
SimpleFactory::createNPC(Level* lvl, double&& x, double&& y)
{
  return std::make_shared<NPC>(lvl, std::move(x), std::move(y));
}
