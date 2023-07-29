/*
  Example of using a shared mutex to let concurrency in 
  the multiple reader operations and force locked access
  in the single writer operations.
  The write thread uses an exclusive lock
  The read thread uses a shared lock
*/ 

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

// Global mutex object
std::shared_mutex shmutex;

// Global shared variable
int x {0};

void write()
{
  std::lock_guard<std::shared_mutex> lck_guard(shmutex);
  
  // If you prefer to work with the shared mutex object directly
  // shmutex.lock(); 

  // Start of critical section
  x++;
  // End of critical section

  // If you prefer to work with the shared mutex object directly
  // shmutex.unlock();
}

void read()
{
  std::shared_lock<std::shared_mutex> lck_guard(shmutex);

  // If you prefer to work with the shared mutex object directly
  // shmutex.lock_shared();

  // Start of critical section
  using namespace std::literals;
  std::this_thread::sleep_for(100ms);
  // End of critical section

  // If you prefer to work with the shared mutex object directly
  //shmutex.unlock_shared();
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