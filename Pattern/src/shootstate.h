#ifndef SHOOTSTATE_H
#define SHOOTSTATE_H
#include "dummy.h"
#include "listentities.h"
#include "playershoot.h"
#include "state.h"

class ShootState : public State
{
public:
  ~ShootState() {}
  virtual State* handleInput(Dummy& actor);
  virtual void update(Dummy& actor, const double& time);
  explicit ShootState(Dummy& actor);
  static void setVisor(ListEntities* visor);

private:
  static ListEntities* visor_;
  int delay_ = 200;
};

#endif // SHOOTSTATE_H
