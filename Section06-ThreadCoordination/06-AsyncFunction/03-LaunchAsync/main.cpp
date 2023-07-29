/* 
  Example of using std::async with explicit async launch option
*/

#include <iostream>
#include <future>

using namespace std::literals;

// Callable object - thread entry point
int func ()
{
  std::cout << "Executing in func from thread with ID: "
            << std::this_thread::get_id() << "\n";
  std::this_thread::sleep_for(5s);

  std::cout << "After 5s, returning \"42\" from func" << "\n";
  return 42;
}
int main()
{
  std::cout << "In main thread with ID " 
            << std::this_thread::get_id() << "\n";
  std::cout << "Calling func" << "\n";

  // Launch the task          
  auto result = std::async(std::launch::async, func);

  // Sleep the main thread
  std::this_thread::sleep_for(2s);

  // Calling the results
  std::cout << "After 2s, calling get()" << "\n";
  std::cout << result.get() << "\n";
}