#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H
#include "abstractfactory.h"
#include "enemy.h"
#include "npc.h"

class SimpleFactory : public AbstractFactory
{
public:
  SimpleFactory();
  std::shared_ptr<Enemy> createEnemy(Player* gamer, Level* lvl, double&& x,
                                     double&& y);
  std::shared_ptr<NPC> createNPC(Level* lvl, double&& x, double&& y);
};

#endif // SIMPLEFACTORY_H
