#include "makesavecommand.h"
#include "listentities.h"

MakeSaveCommand::MakeSaveCommand(ListEntities* visor)
  : visor_(visor)
{
  save_state_ = new Memento(*visor_);
}

Memento*
MakeSaveCommand::getSave()
{
  return save_state_;
}

void
MakeSaveCommand::execute()
{
  Memento* save = new Memento(*visor_);
  delete save_state_;
  save_state_ = save;
}

MakeSaveCommand::~MakeSaveCommand()
{
  delete visor_;
}
