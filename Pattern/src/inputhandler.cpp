#include "inputhandler.h"
#include "commandrestart.h"
#include "listentities.h"
#include "makesavecommand.h"
#include "memento.h"

InputHandler::InputHandler()
{
}

void
InputHandler::inputHandle()
{
  for (auto& el : control) {
    if (sf::Keyboard::isKeyPressed(el.first))
      el.second->execute();
  }
}

void
InputHandler::setRestartCommand(ListEntities* visor,
                                MakeSaveCommand* save_state)
{
  CommandRestart* command = new CommandRestart(visor, save_state);
  control.insert({ sf::Keyboard::R, command });
}

void
InputHandler::setSaveCommand(ListEntities* visor)
{
  MakeSaveCommand* command = new MakeSaveCommand(visor);
  control.insert({ sf::Keyboard::U, command });
  setRestartCommand(visor, command);
}
