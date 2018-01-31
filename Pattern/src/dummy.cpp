#include "dummy.h"

Dummy::Dummy(sf::Image& image, std::string&& name, Level* lvl, double&& x,
             double&& y, int&& w, int&& h)
  : Entity(image, std::move(name), std::move(x), std::move(y), std::move(w),
           std::move(h))
  , lvl_(lvl)
{
  state_ = nullptr;
  objects_ = lvl->GetAllObjects();
  //  this->lvl_ = lvl;
}

Dummy::Dummy(std::string&& name, Level* lvl, double&& x, double&& y, int&& w,
             int&& h)
  : Entity(std::move(name), std::move(x), std::move(y), std::move(w),
           std::move(h))
  , lvl_(lvl)
{
  state_ = nullptr;
  objects_ = lvl->GetAllObjects();
  //  this->lvl_ = lvl;
}

void
Dummy::setSpeed(const double& new_speed)
{
  speed_ = new_speed;
}

// double
// Dummy::getVelocity_x() const
//{
//  return velocity_x;
//}

// void
// Dummy::setVelocity_x(double value)
//{
//  velocity_x = value;
//}

// double
// Dummy::getVelocity_y() const
//{
//  return velocity_y;
//}

// void
// Dummy::setVelocity_y(double value)
//{
//  velocity_y = value;
//}

// double
// Dummy::getSpeed() const
//{
//  return speed;
//}

// void
// Dummy::setSpeed(double value)
//{
//  speed = value;
//}

// double
// Dummy::getTimer() const
//{
//  return timer;
//}

// void
// Dummy::setTimer(double value)
//{
//  timer = value;
//}

// bool
// Dummy::getMove() const
//{
//  return move;
//}

// void
// Dummy::setMove(bool value)
//{
//  move = value;
//}

// bool
// Dummy::getOn_ground() const
//{
//  return on_ground;
//}

// void
// Dummy::setOn_ground(bool value)
//{
//  on_ground = value;
//}
