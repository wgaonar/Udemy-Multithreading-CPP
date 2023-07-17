// Example of overloading on value type
#include <iostream>

// Define moveable object
// The compiler will provide move operators 
class Test {};

// Function which takes lvalue reference
void func(const Test& test)
{
  std::cout << "lvalue reference " << std::endl;
}

// Function which takes rvalue reference
void func(const Test&& test)
{
  std::cout << "rvalue reference " << std::endl;
}

int main()
{
  Test test;

  std::cout << "Argument is test variable:\t\t";
  func(test); // lvalue reference

  std::cout << "Argument is temporary variable:\t\t";
  func(Test()); // rvalue reference

  std::cout << "Argument through std::move():\t\t";
  func(std::move(test));  // rvalue reference

  std::cout << std::endl;
}