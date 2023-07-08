/* 
  Assignment 1: Fizzbuzz game
  A group of children sit in a circle, counting numbers out loud.
  The first child says "one", the second child says "two", and so on.
  However, if the number is divisible by 3, they say "fizz" instead of the number. If the number is divisible by 5, they say "buzz", and if the number is divisible by 3 and by 5, they say "fizzbuzz".
  
  Write a function which produces the output from a game of Fizzbuzz
  Example:
  Abdul says 1, Bart says 2, Claudia says fizz!, Divya says 4, Abdul says buzz!
  Bart says fizz!, Claudia says 7, Divya says 8, and so on...
*/ 
#include <iostream>
#include <thread>

using namespace std;

// Callable object - thread entry point
void FizzBuzz ()
{
  int n{1}, max{15};
  for (int i = 1; i <= max; i++)
  {
    if (n % 3 == 0 && n % 5 != 0)
    {
      cout << "fizz!\n";
    }
    else if (n % 3 != 0 && n % 5 == 0)
    {
      cout << "buzz!\n";
    }
      else if (n % 3 == 0 && n % 5 == 0)
    {
      cout << "fizzbuzz!\n";
    }
    else
    {
      cout << n << endl;
    }
    n++;
  }
}

int main()
{
  // Create an std::thread object and pass the task function to the constructor
  thread thr(FizzBuzz);

  // Wait for the thread to complete
  thr.join();
}