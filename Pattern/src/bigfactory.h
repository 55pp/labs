#ifndef BIGFACTORY_H
#define BIGFACTORY_H
#include "abstractfactory.h"
#include "bigenemy.h"
#include "bignpc.h"

class BigFactory : public AbstractFactory
{
public:
  BigFactory();
  std::shared_ptr<Enemy> createEnemy(Player* gamer, Level* lvl, double&& x,
                                     double&& y);
  std::shared_ptr<NPC> createNPC(Level* lvl, double&& x, double&& y);
};

#endif // BIGFACTORY_H
