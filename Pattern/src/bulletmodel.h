#ifndef BULLETMODEL_H
#define BULLETMODEL_H
#include "ianimation.h"
#include <memory>

class BulletModel
{
public:
  BulletModel();
  void update(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite,
              int& current_frame);

private:
  std::shared_ptr<IAnimation> animate_;
};

#endif // BULLETMODEL_H
