/*
  Condition variable example

  The reader thread waits for a notification
  The writer thread modifies the shared variable "strdata"
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
std::string strdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

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
  cond_var.wait(uniq_lck);

  // Display the new value of the string
  std::cout << "Data is \"" << strdata << "\n";

  // The condition variable has woken up thread up
  // and locked the mutex
  std::cout << "Reader thread unlocks the mutex" << "\n";
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
    strdata = "Populated";
  }
  
  // Notify the condition variable
  std::cout << "Writer thread sends notification" << "\n";
  cond_var.notify_one();
}

int main()
{
  // Initializing the shared string
  strdata = "Empty";

  // Displays its initial value
  std::cout << "Data is \"" << strdata << "\"\n";
  
  // Start the read thread before to avoid lost the notification
  std::thread read(reader);
  std::this_thread::sleep_for(500ms);
  std::thread write(writer);

  // Wait for the tasks to complete
  write.join();
  read.join();
}