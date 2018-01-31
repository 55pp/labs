#ifndef REDENEMY_H
#define REDENEMY_H
#include "factorymethod.h"

class RedEnemy : public FactoryMethod
{
public:
  RedEnemy();
  std::shared_ptr<Enemy> createObject(Player* gamer, Level* lvl, double&& x,
                                      double&& y);
};

#endif // REDENEMY_H
