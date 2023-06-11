// Example of lambda expressions
#include <iostream>

int main()
{
  // In C++14, the compiler can deduce the return type
  [] (int arg) { return 2 * arg; };

  /*
    In C++11, it must be specified with a trailing return type
    when we have more than one statement
  */
  // [](int arg) -> int { arg = 2 * arg; return arg; };

  /*
    A lambda expression is a callable object
    It can be invoked by putting () after the body, with any arguments
  */
  [] (int arg) { return 2 * arg; }(3);

  // A lambda expression can be stored in a variable of type "auto"
  auto lam = [] (int arg) { return 2 * arg; };
  std::cout << "Calling lam with an argument: 3" << std::endl; 
  std::cout << "Returns: " << lam(3) << std::endl << std::endl; 

  // Capture a local variable for using it inside the lambda
  int n{10};
  auto l1 = [n] (int arg) { return n * arg; };
  std::cout << "n: " << n << std::endl;
  std::cout << "l1(3): " << l1(3) << std::endl << std::endl; 

  // Capture a local variable for modifying it inside the lambda
  int m{10};
  std::cout << "m before lambda: " << m << std::endl;

  auto l2 = [&m] (int arg) { return ++m * arg; };
  std::cout << "l2(3): " << l2(3) << std::endl ;   
  std::cout << "m after lambda: " << m << std::endl << std::endl;
}