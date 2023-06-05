// Example of NULL vs C++11's nullptr
#include <iostream>

// Two functions which are overloaded
void func(int i)
{
  std::cout << "func(int) called" << std::endl;
}

void func(int *i)
{
  std::cout << "func(int *) called" << std::endl;
}


int main()
{
  // func(NULL);        // Compiler error with g++
  func (10);

  func(nullptr);
}