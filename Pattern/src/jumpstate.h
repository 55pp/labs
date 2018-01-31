#ifndef JUMPSTATE_H
#define JUMPSTATE_H
#include "dummy.h"
#include "state.h"
#include <playerfall.h>
#include <playerjump.h>

class JumpState : public State
{
public:
  virtual ~JumpState() {}
  virtual State* handleInput(Dummy& actor);
  virtual void update(Dummy& actor, const double& time);
  explicit JumpState(Dummy& actor);

private:
  double jump_strength = 0.7;
};

#endif // JUMPSTATE_H
