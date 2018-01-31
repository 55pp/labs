#include "entytiiterator.h"

EntytiIterator::EntytiIterator(std::vector<std::shared_ptr<Entity>>& entitys)
  : vec(entitys)
{
  index = 0;
}

void
EntytiIterator::first()
{
  index = 0;
}

void
EntytiIterator::next()
{
  ++index;
}

bool
EntytiIterator::isDone()
{
  return index == vec.size();
}

std::shared_ptr<Entity>
EntytiIterator::currentItem()
{
  return vec[index];
}
