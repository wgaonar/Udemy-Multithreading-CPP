/*
  Write a task function that increments a global int 
  variable 100,000 times in a for loop.
  
  Write a program that runs this function in concurrent 
  threads. When all the threads have completed execution, 
  print out the final value of the counter.

  Increase the number of threads until you see 
  anomalous results.
*/
#include <iostream>
#include <thread>

int counter {0};

void task ()
{
  // Repeat the output 5 times
  int count {100000};
  for (size_t i = 0; i < count; i++)
  {
    counter++;
  }
}

int main()
{
  // Start the threads concurrently
  std::thread thr1 (task);
  std::thread thr2 (task);
  std::thread thr3 (task);

  // Wait for the tasks to complete
  thr1.join();
  thr2.join();
  thr3.join();

  std::cout << "The final value of counter is: " << counter << "\n";
}