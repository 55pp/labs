#ifndef MOVESTATE_H
#define MOVESTATE_H
#include "dummy.h"
#include "playermove.h"
#include "state.h"

// class IdleState;
class MoveState : public State
{
public:
  virtual ~MoveState() {}
  virtual State* handleInput(Dummy& actor);
  virtual void update(Dummy& actor, const double& time);
  explicit MoveState(Dummy& actor);
};

#endif // MOVESTATE_H
