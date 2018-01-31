#ifndef BLOCKREMOVE_H
#define BLOCKREMOVE_H
#include <chain.h>

class BlockRemove : public Chain
{
public:
  void handle(std::shared_ptr<FlyEnemy>& enemy, std::shared_ptr<Player>& actor);
};

#endif // BLOCKREMOVE_H
