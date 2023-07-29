/*
  Simulation of a program which performs a download

  One thread fetches the data.
  Another thread displays a progress bar
  A third thread processes the data when the download is complete

  Implemented using condition variables to communicate between threads
*/
#include<iostream>
#include<string>
#include<thread>
#include<mutex>

using namespace std::literals;

// Shared variable for the data being fetched
std::string sdata;

// Flags for predicates in the wait()
bool update_progress {false};
bool completed {false};

// Mutexes to protect the shared variables
std::mutex data_mutex;  // For the data
std::mutex completed_mutex; // For the completed flag

// The condition variables
std::condition_variable data_cv;
std::condition_variable completed_cv;

// Data fetching thread
void fetch_data ()
{
  for (size_t i = 0; i < 5; i++)
  {
    std::cout << "Fetcher thread waiting for the data..." << "\n";
    std::this_thread::sleep_for(2s);

    //Update sdata variable, the notify the progress bar thread
    std::unique_lock<std::mutex> uniq_lck(data_mutex);
    sdata += "Block" + std::to_string(i+1);
    std::cout << "sdata: " << sdata << "\n";
    update_progress = true;
    uniq_lck.unlock();
    data_cv.notify_all();
  }
  std::cout << "\nFetch sdata has ended!" << "\n";

  // Tell the progress bar thread to exit and 
  // wake up the processing thread
  std::lock_guard<std::mutex> completed_lck(completed_mutex);
  completed = true;
  completed_cv.notify_all();
}

// Progress bar thread
void progress_bar()
{
  size_t len {0};
  while (true)
  {
    std::cout << "\nProgress bar thread waiting for data..." << "\n";

    // Wait until there is some new data do display
    std::unique_lock<std::mutex> data_lck(data_mutex);
    data_cv.wait(data_lck, [] {return update_progress;});

    // Wake up und use the new value
    len = sdata.size();

    // Set the flag back to false
    update_progress = false;
    data_lck.unlock();

    std::cout << "Received " << len << " bytes so far" << "\n";

    // Check if the download has finished
    std::unique_lock<std::mutex> compl_lck(completed_mutex);

    // Use wait_for() to avoid blocking
    if (completed_cv.wait_for(compl_lck, 10ms, [] {return completed;}))
    {
      std::cout << "Progress bar thread has ended" << "\n";
      break;
    }
  }
}

void process_data()
{
  std::this_thread::sleep_for(200ms);
  std::cout << "Processing thread waiting for data..." << "\n";

  // Wait until the download is complete
  std::unique_lock<std::mutex> completed_lck(completed_mutex);  // Acquire the lock
  completed_cv.wait(completed_lck, [] {return completed;});
  completed_lck.unlock();

  std::lock_guard<std::mutex> data_lck(data_mutex);
  std::cout << "Processing sdata: " << sdata << "\n";

  // Process the data
  std::cout << "Process data thread has ended" << sdata << "\n";
}

int main()
{
  // Start the threads concurrently
  std::thread fetcher(fetch_data);
  std::thread prog(progress_bar);
  std::thread processor(process_data);

  // Wait for the tasks to complete
  fetcher.join();
  prog.join();
  processor.join();
}