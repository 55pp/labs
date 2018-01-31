#include "healthmediator.h"
#include "npc.h"
#include "player.h"

int
HealthMediator::Send(int&& health, Dummy* body)
{
  if (body == actor) {
    get_pay = false;
    if (actor->score_ >= 10) {
      actor->score_ -= 10;
      get_pay = true;
      npc->getPay(10);
    }
  } else if (body == npc) {
    if (get_pay)
      actor->getHeal(int(npc->health_restore));
  }
}

void
HealthMediator::setPlayer(Player* body)
{
  actor = body;
}

void
HealthMediator::setNPC(NPC* body)
{
  npc = body;
}
