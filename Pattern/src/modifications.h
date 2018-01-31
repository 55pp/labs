#ifndef MODIFICATIONS_H
#define MODIFICATIONS_H
#include "dummy.h"

class Modifications : public Dummy
{
public:
  Modifications(std::shared_ptr<Dummy> bul);
  virtual ~Modifications() { /*delete animate_;*/}

  sf::Sprite getPicture();

  void setSpeed(const double& new_speed);

  void update(const double& time);

  // protected:
  std::shared_ptr<Dummy> bullet;
};

#endif // MODIFICATIONS_H
