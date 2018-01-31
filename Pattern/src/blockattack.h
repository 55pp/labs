#ifndef BLOCKATTACK_H
#define BLOCKATTACK_H
#include "chain.h"

class BlockAttack : public Chain
{
public:
  virtual void handle(std::shared_ptr<FlyEnemy>& enemy,
                      std::shared_ptr<Player>& actor);
};

#endif // BLOCKATTACK_H
