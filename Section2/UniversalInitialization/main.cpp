// Example of C++11 universal initialization
#include <iostream>
#include <string>
#include <vector>

int main()
{
  int x{7};                         // Equivalent to int x = 7
  std::string str{"Let us begin"};  // Equivalent to std::string str("Let us begin")

  std::cout << "x = " << x << std::endl; 
  std::cout << "str = " << str << std::endl; 

  // Narrowing conversions are not allowed
  int y = 7.7;                      // Legal, although compilers may warn you
  // int y {7.7}                    // Illegal
  std::cout << "y = " << y << std::endl;

  // Can be used with multiple initial values
  std::vector<int> vec{1, 2, 3, 4, 5};
  std::cout << "vec = ";
  for (auto i = vec.begin(); i != vec.end(); i++)
  {
    std::cout << *i << ", ";
  }
  std::cout << std::endl;
}