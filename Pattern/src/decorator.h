#ifndef DECORATOR_H
#define DECORATOR_H

class Decorator
{
public:
  Decorator();
  virtual void update(const double& time) = 0;
  virtual ~Decorator() {}
};

#endif // DECORATOR_H
