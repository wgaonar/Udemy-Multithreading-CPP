/* 
  Example of using unsequenced (Vectorized) execution policy on a vector of data
  Using std::atomic to prevent a data race
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <atomic>
#include <execution>

void DisplayVectorWithAuto (const std::vector<int> &inVector) 
{
  for (auto element : inVector) {
      std::cout << element << ", ";
  }
  std::cout << "\n";
}

int main()
{
  // Make atomic the variable to work with parallel sequence
  std::atomic<int> count {0};

 // Create a vector
  std::vector<int> v(2000);

  // explicit sequential execution
  std::for_each(std::execution::par_unseq,v.begin(), v.end(), [&](int& x){x = ++count;});
  DisplayVectorWithAuto(v);
}