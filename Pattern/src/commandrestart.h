#ifndef COMMANDRESTART_H
#define COMMANDRESTART_H
#include "command.h"
#include "makesavecommand.h"

class ListEntities;
class Memento;
class CommandRestart : public Command
{
public:
  CommandRestart(ListEntities* visor, MakeSaveCommand* save_own);
  void execute();

private:
  ListEntities* visor_;
  MakeSaveCommand* save_own_;
};

#endif // COMMANDRESTART_H
