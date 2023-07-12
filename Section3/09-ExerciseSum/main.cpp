// Exercise: Do and print the sum of 2 ints
#include <iostream>
#include <thread>

// Callable object - thread entry point
void sum(int a, int b) 
{
  std::cout << "In a function, the sum of "<< a << " and " << b;
  std::cout << " is " << a + b << "\n";
}

// Functor class with overload () operator
class Addition 
{
public:
  // Overload operator() WITH arguments
  void operator() (int input_a, int input_b) 
  {
    std::cout << "As a functor, the sum of "<< input_a << 
    " and " << input_b << " is " << input_a + input_b << "\n";
  }

  // Class function to do the sum
  void sum(int input_a, int input_b)
  {
    std::cout << "As a member class function, the sum of "
    << input_a << " and " << input_b << " is " 
    << input_a + input_b << "\n";
  }
};

int main()
{
  int num1 {2}, num2 {3};

  /* 
    Create an std::thread object and pass the 
    task function to the thread constructor WITH arguments
  */
  std::thread thr1(sum, num1, num2);

 
  // Create a class object
  Addition addition;

  /* 
    Create an std::thread object, and pass the functor 
    WITH arguments to the thread constructor
  */
  std::thread thr2(addition, num1, num2);

  /*
    Create an std::thread object and pass a pointer 
    to the member function, a pointer to the object, and
    the arguments to call it on
  */
  std::thread thr3(&Addition::sum, &addition, num1, num2);

  /*
    Use the lambda expression WITH arguments as the 
    thread's entry point
  */
  std::thread thr4(
    // The first argument is the lambda expression
    [] (int a, int b) 
    {
      std::cout << "As a Lambda expression, the sum of " << a 
      << " and " << b << " is: " << a + b << "\n";
    },
    // The remaining arguments are passed to the lambda expression
    num1, num2
  );

  // Wait for the threads to complete
  thr1.join();
  thr2.join();
  thr3.join();
  thr4.join();
}