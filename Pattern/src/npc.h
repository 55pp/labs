#ifndef NPC_H
#define NPC_H
#include "dummy.h"

class NPC : public Dummy
{
public:
  NPC(Level* lvl, double&& x, double&& y);
  void update(const double& time);
  void Send();
  void getPay(int&& pay);
  ~NPC();

  int health_restore = 0;
};

#endif // NPC_H
