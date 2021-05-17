#pragma once
class Destroyable
{
private:
  bool isNeedDestruction;
public:
  Destroyable();
  bool NeedDestruction();
  virtual void Destroy();
};

