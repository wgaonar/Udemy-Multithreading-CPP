/* 
  Example of using default execution policy on a vector of data
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>

void DisplayVectorWithAuto (const std::vector <int> &inVector) 
{
  for (auto element : inVector) {
      std::cout << element << ", ";
  }
  std::cout << "\n";
}

int main()
{
  int count {0};

  // Create a vector
  std::vector<int> v(2000);

  // default execution for_each() is sequential in order
  std::for_each(v.begin(), v.end(), [&](int& x){x = ++count;});
  DisplayVectorWithAuto(v);
}