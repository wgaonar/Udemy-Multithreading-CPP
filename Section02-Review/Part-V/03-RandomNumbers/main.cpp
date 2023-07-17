// Example of using the features in <random>
#include <iostream>
#include <random>

// Create the random engine object
std::mt19937 mt; // mersenne_twister_engine with no seed

// Create another random engine object with seed
std::random_device rd;  // a seed source for the random number engine
std::mt19937 mt_seed(rd()); // mersenne_twister_engine seeded with rd()

int main()
{
  /*
    Create a sequence of random integers with uniform 
    distribution in the range 0 to 100
  */
  std::uniform_int_distribution<int> uid(0,100);

  // Get 5 random integers
  std::cout << "The same 5 random integers between 0 and 100:\n";
  for (size_t i = 0; i < 5; i++)
  {
    // Invoking the distribution returns the next number in sequence
    std::cout << uid(mt) << ", ";
  }
  std::cout << "\n\n";
  
  /*
    Create a sequence of random doubles with uniform 
    distribution in the range 0 to 1
  */
  std::uniform_real_distribution<double> udd(0,1);

  // Get 5 random floating-point numbers different each time 
  std::cout << "Different each time 5 random floating-point between 0 and 1:\n";
  for (size_t i = 0; i < 5; i++)
  {
    // Invoking the distribution returns the next number in sequence
    std::cout << udd(mt_seed) << ", ";
  }
  std::cout << std::endl;
}