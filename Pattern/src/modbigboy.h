#ifndef MODBIGBOY_H
#define MODBIGBOY_H
#include "modifications.h"

class ModBigBoy : public Modifications
{
public:
  ModBigBoy(std::shared_ptr<Dummy> bul);
  void update(const double& time);
  ~ModBigBoy() {}
};

#endif // MODBIGBOY_H
