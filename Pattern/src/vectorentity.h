#ifndef VECTORENTITY_H
#define VECTORENTITY_H
#include "entytiiterator.h"

class VectorEntity
{
public:
  VectorEntity();
  int allUpdate(const double& time);
  int drawEntities(sf::RenderWindow& window);
  int push(std::shared_ptr<Entity> entity);

private:
  std::vector<std::shared_ptr<Entity>> vec;
};

#endif // VECTORENTITY_H
