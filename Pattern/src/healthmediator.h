#ifndef HEALTHMEDIATOR_H
#define HEALTHMEDIATOR_H
#include "mediator.h"

class Player;
class NPC;
class HealthMediator : public Mediator
{
public:
  int Send(int&& health, Dummy* body);
  void setPlayer(Player* body);
  void setNPC(NPC* body);

protected:
  Player* actor;
  NPC* npc;
  bool get_pay = false;
};

#endif // HEALTHMEDIATOR_H
