// Demonstrate member functions of atomic types

#include <iostream>
#include <atomic>

int main()
{
  std::atomic<int> x {0};
  std::cout << "After initialization: x = " << x << "\n";

  // Atomic assignment to x
  x = 2;
  std::cout << "After assignment: x = " << x << "\n";

  /*
    Atomic assignment from x to another variable.
    y can be non-atomic 
  */
  int y = x;
  std::cout << "Another non-atomic variable y = " << y << "\n";

  // Using store() and load() member functions
  x.store(3);
  std::cout << "After \"x.store(3)\" x has the new value: " << x << "\n";
  std::cout << "Get the value of x using load(): " << x.load() << "\n";

  // Using exchange() member function to swap x and y values
  std::cout << "Exchange returns the old value of x = " << x.exchange(y) << "\n";
  std::cout << "Exchange set the new value of x = " << x << "\n";
}