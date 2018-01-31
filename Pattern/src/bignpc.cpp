#include "bignpc.h"

BigNPC::BigNPC(Level* lvl, double&& x, double&& y)
  : NPC(lvl, std::move(x), std::move(y))
{
  health_ = 500;
  sprite_.setScale(4, 4);
  width_ *= 4;
  height_ *= 4;
}

BigNPC::~BigNPC()
{
}
