/* 
  Example of using std::transform algorithm
  with a binary argument
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
  std::vector<int> v2{5,6,7,8};
  std::vector<int> v3;

  /* 
    Add each element of v1 to the corresponding element in v2
    and store the result un v.
    Use std::back_inserter() which return an interator to the last
    element of the container
  */
  std::transform(v1.cbegin(),v1.cend(),v2.cbegin(), std::back_inserter(v3),
    [](int n1, int n2){return n1 + n2;}
  );

  // Display original vector v1
  std::cout << "First input vector: " << "\n";
  DisplayVectorWithAuto(v1);
  
  // Display the vector v2
  std::cout << "Second input vector: " << "\n";
  DisplayVectorWithAuto(v2);

  std::cout << "Output vector: " << "\n";
  DisplayVectorWithAuto(v3);
}