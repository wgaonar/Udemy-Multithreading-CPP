/*
  Simulation of a program which performs a download

  One thread fetches the data.
  Another thread displays a progress bar
  A third thread processes the data when the download is complete

  Implemented using bools to communicate between threads
*/
#include<iostream>
#include<string>
#include<thread>
#include<mutex>

using namespace std::literals;

// Shared variable for the data being fetched
std::string sdata;

// Flags for thread communication
bool update_progress {false};
bool completed {false};

// Mutexes to protect the shared variables
std::mutex data_mutex;  // For the data
std::mutex completed_mutex; // For the completed flag

// Data fetching thread
void fetch_data ()
{
  for (size_t i = 0; i < 5; i++)
  {
    std::cout << "Fetcher thread waiting for the data..." << "\n";
    std::this_thread::sleep_for(2s);

    //Update sdata variable, the notify the progress bar thread
    std::lock_guard<std::mutex> data_lck(data_mutex);
    sdata += "Block" + std::to_string(i+1);
    std::cout << "sdata: " << sdata << "\n";
    update_progress = true;
  }
  std::cout << "\nFetch sdata has ended!" << "\n";

  // Tell the progress bar thread to exit and 
  // wake up the processing thread
  std::lock_guard<std::mutex> completed_lck(completed_mutex);
  completed = true;
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
    while (!update_progress)
    {
      data_lck.unlock();
      std::this_thread::sleep_for(10ms);
      data_lck.lock();
    }

    // Wake up und use the new value
    len = sdata.size();

    // Set the flag back to false
    update_progress = false;
    data_lck.unlock();

    std::cout << "Received " << len << " bytes so far" << "\n";

    // Terminate when the download has finished
    std::lock_guard<std::mutex> complete_lck(completed_mutex);
    if (completed)
    {
      std::cout << "Progress bar thread has ended" << "\n";
      break;
    }
    
  }
}

void process_data()
{
  std::cout << "Processing thread waiting for data..." << "\n";

  // Wait until the download is complete
  std::unique_lock<std::mutex> completed_lck(completed_mutex);  // Acquire the lock

  while (!completed)
  {
    completed_lck.unlock();
    std::this_thread::sleep_for(10ms);
    completed_lck.lock();
  }
  completed_lck.unlock();

  std::lock_guard<std::mutex> data_lck(data_mutex);
  std::cout << "Processing sdata: " << sdata << "\n";

  // Process the data
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