#ifndef BLOCKIDLE_H
#define BLOCKIDLE_H
#include "chain.h"

class BlockIdle : public Chain
{
public:
  void handle(std::shared_ptr<FlyEnemy>& enemy, std::shared_ptr<Player>& actor);
};

#endif // BLOCKIDLE_H
