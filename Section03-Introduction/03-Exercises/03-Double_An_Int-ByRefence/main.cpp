// Exercise: Double an integer passed by reference
#include <iostream>
#include <thread>

// Callable object - thread entry point
void doubling(int & num) 
{
  std::cout << "In a function, the double of "<< num;
  num *= 2;
  std::cout << " is " << num << "\n";
}

// Functor class with overload () operator
class Doubling 
{
public:
  // Overload operator() WITH arguments
  void operator() (int & num) 
  {
    std::cout << "As a functor, the double of "<< num;
    num *= 2;
    std::cout << " is " << num << "\n";
  }

  // Class function to do the doubling
  void doubling(int & num)
  {
    std::cout << "As a member class function, the double of " << num;
    num *= 2;
    std::cout << " is " << num << "\n";
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
  std::thread thr1(doubling, std::ref(num));

  // Create a class object
  Doubling doubled;

  /* 
    Case 2: Functor
    Create an std::thread object, and pass the class
    object WITH arguments by reference using std::ref()
    to the thread constructor
  */
  std::thread thr2(doubled, std::ref(num));

  /*
    Case 3: Member class function
    Create an std::thread object and pass a pointer 
    to the member function, a pointer to the object, and
    the arguments by reference using std::ref() to call it on
  */
  std::thread thr3(&Doubling::doubling, &doubled, std::ref(num));

  /*
    Case 4: Lambda expression
    Use the lambda expression WITH arguments by reference using std::ref()
    as the thread's entry point
  */
  std::thread thr4(
    // The first argument is the lambda expression
    [&num] () 
    {
      std::cout << "As a Lambda expression, the double of " << num;
      num *= 2;
      std::cout << " is " << 2 * num << "\n";
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