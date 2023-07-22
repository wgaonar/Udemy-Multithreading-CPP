/*
  Lazy initialization (multi-threaded)
  It is now thread-safe and uses Meyers Singleton
  to ensure that one and only one thread initializes the
  object
*/
#include<iostream>
#include<thread>
#include<mutex>

class Test
{
private:
  /* data */
public:
  // Default constructor 
  Test()
  {
    std::cout << "Test constructor called" 
              << " using the Meyers Singleton" << "\n";
  }
  void func() {/*...*/}
};

void process()
{
  /*
    Variable to be lazily initialized
    The use of static ensures that it will be initialized
    only once, and then skip over that and call the func() directly
  */ 
  static Test test;
  // Use it
  test.func();
}

int main()
{
  // Create the threads
  std::thread thr1(process);
  std::thread thr2(process);

  // Wait to complete the process
  thr1.join();
  thr2.join();
}