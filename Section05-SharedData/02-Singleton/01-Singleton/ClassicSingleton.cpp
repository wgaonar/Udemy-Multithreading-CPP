#include "ClassicSingleton.h"

Singleton* Singleton::getSingleton()
{
  if (single == nullptr)
    single = new Singleton;
  return single;
}