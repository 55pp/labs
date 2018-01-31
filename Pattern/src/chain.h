#ifndef CHAIN_H
#define CHAIN_H
#include "flyenemy.h"
#include "player.h"

#include <memory>

class Chain
{
public:
  Chain();
  void setNext(Chain* next);
  void add(Chain* next);
  virtual void handle(std::shared_ptr<FlyEnemy>& enemy,
                      std::shared_ptr<Player>& actor);

  Chain* next_;
};

#endif // CHAIN_H
