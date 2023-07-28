/* 
  Example of using std::async
*/

#include <iostream>
#include <future>

// Callable object - thread entry point
void hello ()
{
  std::cout << "Hello, Async!" << "\n";
}
int main()
{
  // Create an instance fo std::async and initialize with the task
  std::async(hello);
}