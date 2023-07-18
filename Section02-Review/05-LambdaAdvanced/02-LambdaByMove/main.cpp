// Example of lambda expression which capture by move
#include <iostream>
#include <vector>
#include <string>

int main()
{
  std::vector<std::string> strings(5);
  
  // Capture by reference
  std::cout << "Capture by reference" << std::endl;

  // Lambda expression which captures "strings" by reference
  [&strings] () {
    std::cout << "Size in lambda = " << strings.size() << std::endl;  // 5
  }();
  // The "strings.size()" will be 5
  std::cout << "After calling lambda, size in main = " << strings.size() << "\n\n"; // 5

  // Capture by move
  std::cout << "Capture by move" << std::endl;
  /*
    Lambda expression which captures "strings" by move.
    It creates a new variable "vec_strings" which is local to the lambda body and
    initialize it by moving vector "strings" into it.
  */
  [vec_strings = std::move(strings)] () {
    std::cout << "Size in lambda = " << vec_strings.size() << std::endl;  // 5
  }();
  // The "strings.size()" will be 0 because it was moved 
  std::cout << "After calling lambda, size in main = " << strings.size() << "\n\n"; // 0
}