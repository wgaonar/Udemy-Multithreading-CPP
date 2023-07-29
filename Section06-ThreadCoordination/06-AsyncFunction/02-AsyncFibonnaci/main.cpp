/* 
  Example of using std::async with return value
*/

#include <iostream>
#include <future>

// Callable object - thread entry point
unsigned long long fibonacci (unsigned long long n)
{
  if (n <= 1)
  {
    return 1;
  }
  return fibonacci (n - 1) + fibonacci (n - 2);
}
int main()
{
  std::cout << "Calling fibonacci(40)" << "\n";
  auto result = std::async(fibonacci, 40);
  std::cout << "Calculating result..." << "\n";
  std::cout << result.get() << "\n";
}