#ifndef ZIGZAGFLY_H
#define ZIGZAGFLY_H
#include "strategy.h"

class ZigZagFly : public Strategy
{
public:
  ZigZagFly(Bullet* bullet);
  void doIt(Bullet* bullet);
  virtual ~ZigZagFly();

  int direction_y_ = -1;
  int angle_rotation = 30;
  int delay = 100;
};

#endif // ZIGZAGFLY_H
