#ifndef MEDIATOR_H
#define MEDIATOR_H

class Dummy;
class Mediator
{
public:
  Mediator();
  virtual int Send(int&&, Dummy*) = 0;
};

#endif // MEDIATOR_H
