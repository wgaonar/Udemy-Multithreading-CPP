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

  // Casting vec to an rvalue
  func(std::move(vec));
  // func(vec);  // Compiler error: expects an rvalue
  
  // In this case the data is still available and usable, but it is not safe to rely on that
  std::cout << "After calling func, vector has " << vec.size() << " elements" << std::endl;
  
}