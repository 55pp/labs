#ifndef IDLESTATE_H
#define IDLESTATE_H
#include "dummy.h"
#include "enemyidle.h"
#include "playeridle.h"
#include "state.h"

class IdleState : public State
{
public:
  ~IdleState() {}
  virtual State* handleInput(Dummy& actor);
  virtual void update(Dummy& actor, const double& time);
  explicit IdleState(Dummy& actor);
};

#endif // IDLESTATE_H
