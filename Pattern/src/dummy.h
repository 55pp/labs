#ifndef DUMMY_H
#define DUMMY_H
#include "entity.h"
#include "level.h"
#include "mediator.h"
#include "state.h"
#include <iostream>

class Bullet;
class Dummy : public Entity
{
public:
  explicit Dummy(sf::Image& image, std::string&& name, Level* lvl_, double&& x,
                 double&& y, int&& w, int&& h);

  explicit Dummy(std::string&& name, Level* lvl_, double&& x, double&& y,
                 int&& w, int&& h);

  virtual void setSpeed(const double& new_speed);

  virtual std::shared_ptr<Bullet> shoot() { throw 1; }

  virtual ~Dummy() {}

  //  double getVelocity_x() const;
  //  void setVelocity_x(double value);

  //  double getVelocity_y() const;
  //  void setVelocity_y(double value);

  //  double getSpeed() const;
  //  void setSpeed(double value);

  //  double getTimer() const;
  //  void setTimer(double value);

  //  bool getMove() const;
  //  void setMove(bool value);

  //  bool getOn_ground() const;
  //  void setOn_ground(bool value);

  double velocity_x_ = 0;
  double velocity_y_ = 0;
  double speed_ = 0;
  double timer_ = 0;
  std::vector<int> dOTs;
  //  bool move = false;
  //  bool on_ground = false;
  //  bool direction_ = true;
  std::vector<Object> objects_;
  State* state_;
  Level* lvl_;
  Mediator* mediator;

private:
};

#endif // DUMMY_H
