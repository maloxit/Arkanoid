#include "Destroyable.hpp"

Destroyable::Destroyable() : isNeedDestruction(false)
{
}

bool Destroyable::NeedDestruction()
{
  return isNeedDestruction;
}

void Destroyable::Destroy()
{
  isNeedDestruction = true;
}
