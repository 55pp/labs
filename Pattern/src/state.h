#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <memory>

class Dummy;
class State
{
public:
  virtual ~State() {}
  virtual State* handleInput(Dummy& actor) = 0;
  virtual void update(Dummy& actor, const double& time) = 0;

  std::string path_to_image;
};

#endif // STATE_H
