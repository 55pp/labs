#ifndef DROPCOINUNTILDIE_H
#define DROPCOINUNTILDIE_H
#include "coin.h"
#include "operation.h"

class ListEntities;
class DropCoinUntilDie : public Operation
{
public:
  void visit(Enemy* target);
  static void setVisor(ListEntities* visor);
  virtual ~DropCoinUntilDie() {}

private:
  static ListEntities* visor_;
};

#endif // DROPCOINUNTILDIE_H
