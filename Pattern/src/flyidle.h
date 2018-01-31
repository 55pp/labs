#ifndef FLYIDLE_H
#define FLYIDLE_H
#include "dummy.h"
#include "state.h"

class FlyIdle : public State
{
public:
  FlyIdle(Dummy& actor);
  State* handleInput(Dummy& actor);
  void update(Dummy& actor, const double& time);
  ~FlyIdle() {}
};

#endif // FLYIDLE_H
