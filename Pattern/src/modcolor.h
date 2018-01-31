#ifndef MODCOLOR_H
#define MODCOLOR_H
#include "modifications.h"

class ModColor : public Modifications
{
public:
  ModColor(std::shared_ptr<Dummy> bul);
  void update(const double& time);
  ~ModColor() {}
};

#endif // MODCOLOR_H
