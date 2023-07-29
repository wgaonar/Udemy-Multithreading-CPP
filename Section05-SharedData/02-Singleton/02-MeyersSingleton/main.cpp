// Test program for classic Singleton
#include "cpp11_Singleton.h"
#include <thread>
#include <vector>

void task()
{
  Singleton& single = getSingleton();
  std::cout << &single << "\n";
}

int main()
{
  std::vector<std::thread> threads;

  // Create the threads
  for (size_t i = 0; i < 10; i++)
  {
    threads.push_back(std::thread(task));
  }

  // Wait to finish the tasks
  for (auto & thr:  threads)
  {
    thr.join();
  }
}

