#ifndef ENTYTIITERATOR_H
#define ENTYTIITERATOR_H
#include "entity.h"

class EntytiIterator
{
public:
  EntytiIterator(std::vector<std::shared_ptr<Entity>>& entitys);
  void first();
  void next();
  bool isDone();
  std::shared_ptr<Entity> currentItem();

private:
  std::vector<std::shared_ptr<Entity>>& vec;
  size_t index;
};

#endif // ENTYTIITERATOR_H
