// Exercise: Print an integer passed by move
#include <iostream>
#include <thread>

// Callable object - thread entry point
void printing(int && num) 
{
  std::cout << "In a function, printing: "<< num << "\n";
}

// Functor class with overload () operator
class Printing 
{
public:
  // Overload operator() WITH arguments
  void operator() (int && num) 
  {
    std::cout << "As a functor, printing: "<< num << "\n";
  }

  // Class function to print the number
  void printing(int && num)
  {
    std::cout << "As a member class function, printing: "<< num << "\n";
  }
};

int main()
{
  int num {10};

  /*
    Case 1: Regular function
    Create an std::thread object and pass the 
    task function to the thread constructor WITH arguments
    by reference using std::ref()
  */
  std::thread thr1(printing, std::move(num));

  // Create a class object
  Printing printed;

  /* 
    Case 2: Functor
    Create an std::thread object, and pass the class
    object WITH arguments by reference using std::ref()
    to the thread constructor
  */
  std::thread thr2(printed, std::move(num));

  /*
    Case 3: Member class function
    Create an std::thread object and pass a pointer 
    to the member function, a pointer to the object, and
    the arguments by reference using std::ref() to call it on
  */
  std::thread thr3(&Printing::printing, &printed, std::move(num));

  /*
    Case 4: Lambda expression
    Use the lambda expression WITH arguments by reference using std::ref()
    as the thread's entry point
  */
  std::thread thr4(
    // The first argument is the lambda expression
    // Capture a move-only variable initializing and use it in a another variable
    [number = std::move(num)] () 
    {
      std::cout << "As a Lambda expression, printing: "<< number << "\n";
    }
  );

  // Wait for the threads to complete
  thr1.join();
  thr2.join();
  thr3.join();
  thr4.join();

  // Verify that num has been modified
  std::cout << "num is now: " << num << "\n"; // 10 * 2 * 2 * 2 * 2 = 160
}