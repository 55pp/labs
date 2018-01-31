#include "commandrestart.h"
#include "listentities.h"
#include "memento.h"

CommandRestart::CommandRestart(ListEntities* visor, MakeSaveCommand* save_own)
  : visor_(visor)
  , save_own_(save_own)
{
}

void
CommandRestart::execute()
{
  visor_->setState(save_own_->getSave());
}
