#ifndef FLYACTION_H
#define FLYACTION_H
#include "dummy.h"
#include "state.h"

class FlyAction : public State
{
public:
  FlyAction(Dummy& actor);
  State* handleInput(Dummy& actor);
  void update(Dummy& actor, const double& time);
  ~FlyAction() {}
};

#endif // FLYACTION_H
