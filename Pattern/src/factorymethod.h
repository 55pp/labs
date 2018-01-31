#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H
#include "enemy.h"

class FactoryMethod
{
public:
  FactoryMethod();
  virtual std::shared_ptr<Enemy> createObject(Player* gamer, Level* lvl,
                                              double&& x, double&& y) = 0;
};

#endif // FACTORYMETHOD_H
