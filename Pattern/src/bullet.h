#ifndef BULLET_H
#define BULLET_H
//#include "bulletmove.h"
#include "bulletmodel.h"
#include "dummy.h"
#include "strategy.h"

class Bullet : public Dummy
{
public:
  explicit Bullet(Level* lvl, double x, double y, int&& dir);
  virtual ~Bullet();
  void update(const double& time);
  std::shared_ptr<Bullet> clone(Level* lvl, double x, double y, int&& dir);

  int direction_;

private:
  static std::unique_ptr<BulletModel> model_;
  int current_frame_ = 0;
  Strategy* str_fly;
};

#endif // BULLET_H
