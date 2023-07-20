/*
  Example of using a mutex forced in all the 
  multiple reader and a single writer operations
*/ 

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// Global mutex object
std::mutex the_mutex;

// Global shared variable
int x {0};

void write()
{
  std::lock_guard<std::mutex> lck_guard(the_mutex);
  // Start of critical section
  x++;
  // End of critical section
}

void read()
{
  std::lock_guard<std::mutex> lck_guard(the_mutex);
  // Start of critical section
  using namespace std::literals;
  std::this_thread::sleep_for(100ms);
  // End of critical section
}

int main()
{
  // Create a vector of threads
  std::vector<std::thread> threads;

  // Push back 20 read threads
  for (size_t i = 0; i < 20; i++)
  {
    threads.push_back(std::thread(read));
  }
  
  // Push back 2 write threads
  threads.push_back(std::thread(write));
  threads.push_back(std::thread(write));

   // Push back another 20 read threads
  for (size_t i = 0; i < 20; i++)
  {
    threads.push_back(std::thread(read));
  }

  // Wait for the task to complete
  for (auto & thr : threads)
  {
    thr.join();
  }
}