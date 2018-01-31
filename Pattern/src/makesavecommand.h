#ifndef MAKESAVECOMMAND_H
#define MAKESAVECOMMAND_H
#include "command.h"
#include "memento.h"
#include <memory>

class ListEntities;
class Memento;
class MakeSaveCommand : public Command
{
public:
  MakeSaveCommand(ListEntities* visor);
  Memento* getSave();
  void execute();
  ~MakeSaveCommand();

private:
  Memento* save_state_;
  ListEntities* visor_;
};

#endif // MAKESAVECOMMAND_H
