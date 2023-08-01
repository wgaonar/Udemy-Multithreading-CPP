// Program to test the concurrent queue class

#include "concurrent_queue_cv.h"
#include <iostream>
#include <future>
#include <string>

using namespace std;

concurrent_queue_cv<string> cq;

// Waiting thread
void reader()
{
  string strdata;
  try
  {
    cout << "Reader calling pop.." << "\n";
    // cq.pop(strdata); // Option 1
    strdata = cq.pop(); // Option 2
    cout << "Reader received data: " << strdata << "\n";
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: "<< e.what() << '\n';
  }
}

// Modifying thread
void writer()
{
  cout << "Writer calling push..." << "\n";
  cq.push("Populated");
  cout << "Writer returned from push..." << "\n";
}

int main()
{
  /* 
    Create an instance fo std::async with explicit 
    async launch option for launching in a separate
    thread.
    Return future value
  */
  auto w = async(std::launch::async, writer);

  // Pretend to be busy
  std::this_thread::sleep_for(5s);

  auto r = async(std::launch::async, reader);

  r.wait();
  w.wait();
}