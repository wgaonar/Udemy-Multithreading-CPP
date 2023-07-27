/*
  Example using std::promise and std::future
  Throw an exception from a producer thread to
  a consumer thread
*/
#include<iostream>
#include<thread>
#include<future>
#include<exception>

// The producer's task function takes an std::promise as argument
void produce(std::promise<int> & px)
{
  try
  {
    using namespace std::literals;

    // Produce the result
    int x {42};
    std::this_thread::sleep_for(2s);

    // Code that may throw an exception
    if (true)
    {
      throw std::out_of_range("Oops");
    }
    
    // No exception - store the result in the shared state
      std::cout << "Promise sets the shared state to " << x << "\n";
      px.set_value(x);
  }
  catch(...)
  {
    // Exception thrown - store it in the shared state
    // current_exception() get a pointer to the active exception
    px.set_exception(std::current_exception());
  }
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> & fx)
{
  std::cout << "Future calling get()..." << "\n";
  try
  {
    // Get the result from the shared state
    int x = fx.get();
    std::cout << "Future returns from calling get()" << "\n";
    std::cout << "The answer is " << x << "\n";
  }
  catch(const std::exception& e)
  {
    // Exception thrown - get it from the shared state
    std::cerr << "Exception caught: " << e.what() << '\n';
  }
}


int main()
{
  /*
    Create an std::promise object
    This creates an associated std::future object
    and sets up a shared state between them
  */
  std::promise<int> prom;

  // Get the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function receives a promise as argument
  std::thread thr_producer(produce, std::ref(prom));
  // The consumer task function receives a future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
}