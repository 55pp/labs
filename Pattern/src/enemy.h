#ifndef ENEMY_H
#define ENEMY_H
#include "dummy.h"

class Player;
class Operation;
class Enemy : public Dummy
{
public:
  Enemy(Player* gamer, Level* lvl, double&& x, double&& y);
  Enemy(std::string name, Player* gamer, Level* lvl, double&& x, double&& y);
  void update(const double& time);
  void setSubject(Player* gamer);
  void accept(Operation* o);
  ~Enemy();

  Player* gamer_;
  int experience_ = 600;
};

#endif // ENEMY_H
