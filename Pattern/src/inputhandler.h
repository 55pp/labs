#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "command.h"
#include <SFML/Graphics.hpp>

class ListEntities;
class Memento;
class MakeSaveCommand;
class InputHandler
{
public:
  InputHandler();
  void inputHandle();
  void setRestartCommand(ListEntities* visor, MakeSaveCommand* save_state);
  void setSaveCommand(ListEntities* visor);

private:
  std::map<sf::Keyboard::Key, Command*> control;
};

#endif // INPUTHANDLER_H
