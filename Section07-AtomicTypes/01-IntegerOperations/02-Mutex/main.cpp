/*
  A shared variable is modified by multiple threads
  Integer operations take a single instruction
  Using std::mutex to avoid data race
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mut;
int counter {0};

void task()
{
  for (int i = 0; i < 100'000; i++)
  {
    std::lock_guard<std::mutex> lck_guard(mut);
    counter++;
  }
}

int main()
{
  std::vector<std::thread> tasks;

  // Start the threads
  for (size_t i = 0; i < 10; i++)
  {
    tasks.push_back(std::thread(task));
  }

  // Wait for join each thread
  for (auto &  thr : tasks)
  {
    thr.join();
  }
  
  std::cout << counter << "\n";
  
}