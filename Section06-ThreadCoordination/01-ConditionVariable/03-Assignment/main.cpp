/*
  Condition variable example rewritten using boolean flags instead

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
std::string strdata {"Empty"};

// Mutexes to protect the shared variables
std::mutex mut;

// Flags for thread communication
bool writing_finished {false};

// Waiting thread
void reader ()
{
  // Lock the mutex
  std::cout << "Reader thread locking the mutex" << "\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex" << "\n";

  // sleep until the condition variable wakes up
  std::cout << "Reader thread sleeping..." << "\n";

  // Wait until the writer notify
  while (!writing_finished)
  {
    uniq_lck.unlock();
    std::this_thread::sleep_for(10ms);
    uniq_lck.lock();
  }

  // Set the flat back to false
  writing_finished = false;
  uniq_lck.unlock();

  std::cout << "Reader thread wakes up" << "\n";

  // Display the new value of the string
  std::cout << "Data is \"" << strdata << "\"\n";
}

// Notifying thread
void writer()
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

  // Notify the condition variable
  std::cout << "Writer thread sends notification" << "\n";
  writing_finished = true;
}

int main()
{
  // Initializing the shared string
  strdata = "Empty";

  // Displays its initial value
  std::cout << "Data is \"" << strdata << "\"\n";
  
  // Start the read thread before to avoid lost the notification
  std::thread read(reader);
  // std::this_thread::sleep_for(500ms); // With boolean flags it seems to be not necessary
  std::thread write(writer);

  // Wait for the tasks to complete
  write.join();
  read.join();
}