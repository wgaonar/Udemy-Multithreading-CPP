// Example of using std::unique_ptr
#include <iostream>
#include <memory>

// Data structure representing a point on the screen
struct Point
{
  int x;
  int y;
}; 

int main()
{
  // Create a unique_ptr to an Point object which has initial values {3,6}
  // From C++14 We use make_unique() function
  auto uniq_ptr = std::make_unique<Point>(Point{3,6});

  // In C++11 We have to provide the pointer
  // std::unique_ptr<Point> uniq_ptr(new Point{3,6});

  std::cout << uniq_ptr->x << " , " << uniq_ptr->y << "\n";
}