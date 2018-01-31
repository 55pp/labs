#ifndef FALLSTATE_H
#define FALLSTATE_H
#include "dummy.h"
#include "playerfall.h"
#include "state.h"

class FallState : public State
{
public:
  ~FallState() {}
  virtual State* handleInput(Dummy& actor);
  virtual void update(Dummy& actor, const double& time);
  explicit FallState(Dummy& actor);
};

#endif // FALLSTATE_H
