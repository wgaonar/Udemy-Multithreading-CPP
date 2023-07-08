// Example of using a member function as a thread's entry point
#include <iostream>
#include <thread>
#include <string>

/* 
  Class whose member function will be used as
  the thread's entry point
*/
class greeter
{
public:
  void hello()
  {
    std::cout << "Hello, Member Function Thread!\n";
  }
  void greetings(std::string str)
  {
    std::cout << "Greetings with arguments: " << str << "\n";
  }
};

int main()
{
  // Create an object of the class
  greeter greet;

  /*
    Create an std::thread object
    Pass a pointer to the member function and
    a pointer to the object to call it on
  */
  std::thread thr(&greeter::hello, &greet);

  /*
    Create an std::thread object
    Pass a pointer to the member function and
    a pointer to the object to call it on and the argument
  */
  std::thread thr2(&greeter::greetings, &greet, "String from main");

  // Wait for the threads to complete
  thr.join();
  thr2.join();
}