#ifndef BIGNPC_H
#define BIGNPC_H
#include "npc.h"

class BigNPC : public NPC
{
public:
  BigNPC(Level* lvl, double&& x, double&& y);
  ~BigNPC();
};

#endif // BIGNPC_H
