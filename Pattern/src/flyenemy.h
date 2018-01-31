#ifndef FLYENEMY_H
#define FLYENEMY_H
#include "enemy.h"

class FlyEnemy : public Enemy
{
public:
  FlyEnemy(Player* gamer, Level* lvl, double&& x, double&& y);
  void update(const double& time);
  ~FlyEnemy();

  double spawn_x = 0;
  double spawn_y = 0;
  enum States
  {
    IDLE,
    ATTACK,
    REMOVE
  };
  States current_state;
};

#endif // FLYENEMY_H
