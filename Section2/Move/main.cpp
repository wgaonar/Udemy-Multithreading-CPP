/*
Program which passes an lvalue to a function
which takes an rvalue reference as argument
*/
#include <iostream>
#include <vector>
#include <string>

// Pass by move
// The object passed by the caller is moved into arg
void func(std::vector<std::string>&& arg)
{
  std::cout << "Argument vector has " << arg.size() << " elements" << std::endl;
}
int main()
{
  std::vector<std::string> vec(1000000);
  std::cout << "Before calling func, vector has " << vec.size() << " elements" << std::endl;

  // Casts vec to an rvalue
  func(std::move(vec));
  std::cout << "After calling func, vector has " << vec.size() << " elements" << std::endl;
}