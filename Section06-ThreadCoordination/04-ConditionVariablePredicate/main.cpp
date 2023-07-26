/*
  Condition variable example

  The reader thread waits for a notification
  The writer thread modifies the shared variable "sdata"
  The writer thread sends a notification
  The reader thread receives the notification and resumes
  The reader thread uses the new value of the shared data
*/
#include<iostream>
#include<string>
#include<thread>
#include<condition_variable>

using namespace std::literals;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// bool flag for predicate
bool condition {false};

// Waiting thread
void reader ()
{
  // Lock the mutex
  std::cout << "Reader thread locking the mutex" << "\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex" << "\n";

  // Call wait() will unlock the mutex and make this thread
  // sleep until the condition variable wakes up
  std::cout << "Reader thread sleeping..." << "\n";

  // Lambda predicate that checks the flag
  cond_var.wait(uniq_lck, [] {return condition;});

  // Display the new value of the string
  std::cout << "Data is \"" << sdata << "\n";

  // The condition variable has woken up thread up
  // and locked the mutex
  std::cout << "Reader thead unlocks the mutex" << "\n";
}

// Notifying thread
void writer()
{
  {
    std::cout << "Writer thread locking the mutex" << "\n";

    // Lock the mutex. This will not be explicitly unlocked
    // std::lock_guard is sufficient
    std::lock_guard<std::mutex> lck_guard(mut);
    std::cout << "Writer has locked the mutex" << "\n";

    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    // Modify the string
    std::cout << "Writer thread modifying data..." << "\n";
    sdata = "Populated";

    // Set the flag
    condition = true;

    std::cout << "Writer thread unlocks the mutex" << "\n";
  }

  // Notify the condition variable
  std::cout << "Writer thread sends notification" << "\n";
  cond_var.notify_one();
}

int main()
{
  // Initializing the shared string
  sdata = "Empty";

  // Displays its initial value
  std::cout << "Data is \"" << sdata << "\"\n";
  
  /*
    The notification is NOT lost, even if the writer thread
    finishes before the reader thread starts or there is a 
    "spurious wake up", i.e.m wait returns without a notification 
  */

  std::thread write(writer);
  std::this_thread::sleep_for(500ms);
  std::thread read(reader);

  // Wait for the tasks to complete
  write.join();
  read.join();
}