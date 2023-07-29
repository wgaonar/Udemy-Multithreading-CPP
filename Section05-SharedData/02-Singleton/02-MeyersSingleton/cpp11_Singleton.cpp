#include "cpp11_Singleton.h"

Singleton & getSingleton()
{
  // Initialized once and only by the first thread that executes this code
  static Singleton single;
  return single;
}