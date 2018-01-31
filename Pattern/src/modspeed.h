#ifndef MODSPEED_H
#define MODSPEED_H
#include "modifications.h"

class ModSpeed : public Modifications
{
public:
  ModSpeed(std::shared_ptr<Dummy> bul);
  void update(const double& time);

private:
  double more_speed = 0.4;
};

#endif // MODSPEED_H
