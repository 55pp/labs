#ifndef PLAYER_H
#define PLAYER_H
#include "dummy.h"
#include "gun.h"
#include <iostream>
#include <list>

class Player : public Dummy
{

public:
  explicit Player(Level* lvl, double&& x, double&& y);

  //  void control();
  virtual void update(const double& time);
  void handleInput();
  void Send();
  void getHeal(int&& heal);
  std::shared_ptr<Bullet> shoot();
  ~Player();

  int score_ = 0;
  int experience_ = 0;
  int level_cap_ = 500;
  int level_ = 0;
  std::shared_ptr<Gun> gun_;

private:
};

#endif // PLAYER_H
