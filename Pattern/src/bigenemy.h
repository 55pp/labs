#ifndef BIGENEMY_H
#define BIGENEMY_H
#include "enemy.h"

class BigEnemy : public Enemy
{
public:
  BigEnemy(Player* gamer, Level* lvl, double&& x, double&& y);
  ~BigEnemy();
};

#endif // BIGENEMY_H
