/* 
  Example of using std::transform_reduce() algorithm
  It is the equivalent of std::inner_product() but 
  with execution polices
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
  std::vector<int> v2{5,6,7,8};

  int initial_value {0};

  // Calculate the inner product between two vectors
  auto result = std::transform_reduce(std::execution::par,
                                      v1.cbegin(),v1.cend(),
                                      v2.cbegin(), initial_value);

  // Display original vector v1
  std::cout << "First input vector: " << "\n";
  DisplayVectorWithAuto(v1);
  
  // Display the vector v2
  std::cout << "Second input vector: " << "\n";
  DisplayVectorWithAuto(v2);

  std::cout << "The inner product between v1 and v2 : " 
            << result << "\n";
}