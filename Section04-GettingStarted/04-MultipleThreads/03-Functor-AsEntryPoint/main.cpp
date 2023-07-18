/* 
  Example of starting multiple threads concurrently
  with functors as entry point
*/
#include <iostream>
#include <thread>

// Functor class with overload () operator
class Hello
{
public:
  void operator() (int num)
  {
    // Add a delay
    std::this_thread::sleep_for(std::chrono::seconds(num));
    std::cout << "Hello from thread " << num << "\n";
  }
};

int main()
{
  // Create objects of the functor class
  Hello hello1, hello2, hello3;

  std::cout << "Starting 3 threads:" << "\n";
  std::thread thr1(hello1, 1);
  std::thread thr2(hello2, 2);
  std::thread thr3(hello3, 3);
  
  // Wait for the threads to finish
  thr1.join();
  thr2.join();
  thr3.join();
}