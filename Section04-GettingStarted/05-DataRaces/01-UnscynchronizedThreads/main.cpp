/*
  Example of unsynchronized threads which make conflicting accesses.
  But, where is the shared memory location?. -> Answer: in the std::cout 
  of line std::cout << str.at(j);
*/
#include <iostream>
#include <thread>

void print (std::string str)
{
  // Repeat the output 5 times
  int count {5};
  for (size_t i = 0; i < count; i++)
  {
    // A very artificial way to display a string!
    for (size_t j = 0; j < str.length(); j++)
    {
      std::cout << str.at(j);
    }
    std::cout << "\n";
  }
}

int main()
{
  // Start the threads concurrently
  std::thread thr1 (print, "abc");
  std::thread thr2 (print, "def");
  std::thread thr3 (print, "xyz");

  // Wait for the tasks to complete
  thr1.join();
  thr2.join();
  thr3.join();
}