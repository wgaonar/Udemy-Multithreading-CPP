/* 
  Example of using std::accumulate algorithm
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
  std::vector<int> v{1,2,3,4,5,6,7,8};

  int initial_value {0};

  // Sum elements of v using initial value 0
  auto sum = std::accumulate(v.cbegin(),v.cend(),initial_value);

  DisplayVectorWithAuto(v);
  std::cout << "Sum of elements is " << sum << "\n";
}