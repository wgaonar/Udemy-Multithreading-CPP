// Example of intervals in std::chrono
#include <iostream>
#include <chrono>

// Namespace alias to simplify the code
namespace sc = std::chrono;

int main()
{
  // Interval types defined in the std::chrono library
  sc::seconds(2);         // 2 seconds interval
  sc::milliseconds(20);    // 20 milliseconds interval
  sc::microseconds(50);    // 50 microseconds interval

  // Literal suffixes added in C++14
  using namespace std::literals;
  2s;
  20ms;
  50us;
}