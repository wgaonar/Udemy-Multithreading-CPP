/*
  Example using std::async with exceptions
*/
#include<iostream>
#include<thread>
#include<future>
#include<exception>

// The producer's task function
int produce()
{
  using namespace std::literals;

  // Produce the result
  int x {42};
  std::this_thread::sleep_for(5s);

  // Code that may throw an exception
  if (true)
  {
    throw std::out_of_range("Oops");
  }
  
  // No exception - produce the result
  std::cout << "Produce returning after 5s: " << x << "\n";
  return x;
}

int main()
{
  // Launch the task
  auto f = std::async(produce);

  std::cout << "Future calling get()..." << "\n";
  try
  {
    // Calling the results
    int x = f.get();
    std::cout << "Future returns from calling get()" << "\n";
    std::cout << "The answer is " << x << "\n";
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n';
  }
}