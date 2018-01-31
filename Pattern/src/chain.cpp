#include "chain.h"

Chain::Chain()
{
  next_ = 0;
}

void
Chain::setNext(Chain* next)
{
  next_ = next;
}

void
Chain::add(Chain* next)
{
  if (next_)
    next_->add(next);
  else
    next_ = next;
}

void
Chain::handle(std::shared_ptr<FlyEnemy>& enemy, std::shared_ptr<Player>& actor)
{
  next_->handle(enemy, actor);
}
