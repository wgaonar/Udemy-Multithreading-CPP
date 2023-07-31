/* 
  Example of using std::transform algorithm
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

  // Double the elements of a vector
  std::transform(v1.cbegin(),v1.cend(),v2.begin(),
    [](int n){return 2 * n;}
  );

  // Display original vector v1
  std::cout << "Original vector: " << "\n";
  DisplayVectorWithAuto(v1);
  
  // Display the vector v2
  std::cout << "Transformed vector: " << "\n";
  DisplayVectorWithAuto(v2);
}