/* 
  Example of using std::partial_sum algorithm
  Calculates the sum of the elements so far.
  It NOT supports execution policies
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

void DisplayVectorWithAuto (const std::vector <int> &inVector) 
{
  for (auto element : inVector) {
      std::cout << element << ", ";
  }
  std::cout << "\n";
}

int main()
{
  // Create a vector
  std::vector<int> v1{1,2,3,4};
  std::vector<int> v2((v1.size()));

  // Partial sum of the elements of v using initial value 0
  std::partial_sum(v1.cbegin(),v1.cend(),v2.begin());

  // Display original vector v1
  std::cout << "Original vector: " << "\n";
  DisplayVectorWithAuto(v1);
  
  // Display hte calculated vector v2
  std::cout << "Partial sum vector elements: " << "\n";
  DisplayVectorWithAuto(v2);
}