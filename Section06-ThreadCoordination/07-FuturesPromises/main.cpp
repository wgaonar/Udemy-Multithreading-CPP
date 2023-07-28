/*
  Example using std::promise and std::future
  Send a result from a producer thread to
  a consumer thread
*/
#include<iostream>
#include<thread>
#include<future>

// The producer's task function takes an std::promise as argument
void produce(std::promise<int> & px)
{
  using namespace std::literals;

  // Produce the result
  int x {42};
  std::this_thread::sleep_for(2s);

  // Store the result in the shared state
  std::cout << "Promise sets the shared state to " << x << "\n";
  px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> & fx)
{
  // Get the result from the shared state
  std::cout << "Future calling get()..." << "\n";
  int x = fx.get();
  std::cout << "Future returns from calling get()" << "\n";
  std::cout << "The answer is " << x << "\n";
}


int main()
{
  /*
    Create an std::promise object
    This creates an associated std::future object
    and sets up a shared state between them
  */
  std::promise<int> prom;

  // Create the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function receives a promise as argument
  std::thread thr_producer(produce, std::ref(prom));
  // The consumer task function receives a future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
}