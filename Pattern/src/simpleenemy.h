#ifndef SIMPLEENEMY_H
#define SIMPLEENEMY_H
#include "factorymethod.h"

class SimpleEnemy : public FactoryMethod
{
public:
  SimpleEnemy();
  std::shared_ptr<Enemy> createObject(Player* gamer, Level* lvl, double&& x,
                                      double&& y);
};

#endif // SIMPLEENEMY_H
