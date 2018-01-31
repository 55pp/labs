#ifndef PLAYSOUND_H
#define PLAYSOUND_H
#include "operation.h"
#include <SFML/Audio.hpp>

class PlaySound : public Operation
{
public:
  void visit(Enemy* target);
};

#endif // PLAYSOUND_H
