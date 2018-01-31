#ifndef STRATEGY_H
#define STRATEGY_H

class Bullet;
class Strategy
{
public:
  Strategy(Bullet* bullet);
  virtual void doIt(Bullet* bullet) = 0;
  virtual ~Strategy();

  Bullet* bullet_;
};

#endif // STRATEGY_H
