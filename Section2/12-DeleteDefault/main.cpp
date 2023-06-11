// Example of a class with defaulted and deleted operators
#include <iostream>
#include <utility>  // Defines std::move() function

// Move only class
class Test
{
public:
  /*
  = delete means the function exists but cannot be called
  In older C++, we had to declare the member function private
  */

  // Deep Copy Constructor
  Test (const Test&) = delete;

  // Overloading assignment operator
  Test& operator=(const Test&) = delete;

  /* 
    = default means the compiler will synthesize
    the default version of the operator
  */

  // Move constructor
  Test(Test&&) noexcept = default;

  // Move assignment operator
  Test& operator=(Test&&) = default;

  Test() = default;
};

int main()
{
  Test test1, test2, test3;

  // Test test4(test1);  // Compiler error
  // Using the move constructor
  Test test4(std::move(test1));

  // test2 = test1;  // Compiler error
  // Using the move assignment operator
  test2 = std::move(test1);
}