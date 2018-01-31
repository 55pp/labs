#ifndef SIMPLEFLY_H
#define SIMPLEFLY_H
#include "strategy.h"

class SimpleFly : public Strategy
{
public:
  SimpleFly(Bullet* bullet);
  void doIt(Bullet* bullet);
  virtual ~SimpleFly();
};

#endif // SIMPLEFLY_H
