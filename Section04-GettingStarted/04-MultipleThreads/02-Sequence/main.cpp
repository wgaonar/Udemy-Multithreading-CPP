// Example of starting multiple threads
#include <iostream>
#include <thread>

void hello (int num)
{
  // Add a delay
  std::this_thread::sleep_for(std::chrono::seconds(num));
  std::cout << "Hello from thread " << num << "\n";
}

int main()
{
  // Start and wait to finish each thread
  std::cout << "Start thread 1:" << "\n";
  std::thread thr1(hello, 1);
  thr1.join();
  
  std::cout << "Start thread 2:" << "\n";
  std::thread thr2(hello, 2);
  thr2.join();
  
  std::cout << "Start thread 3:" << "\n";
  std::thread thr3(hello, 3);
  thr3.join();
}