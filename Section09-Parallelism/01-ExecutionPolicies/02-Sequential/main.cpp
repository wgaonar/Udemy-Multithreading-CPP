/* 
  Example of using sequential execution policy on a vector of data
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

  // Create 4 different vectors
  std::vector<int> v1(2000);
  std::vector<int> v2(2000);
  std::vector<int> v3(2000);
  std::vector<int> v4(2000);

  // explicit sequential execution
  std::for_each(std::execution::seq,v1.begin(), v1.end(), [&](int& x){x = ++count;});
  DisplayVectorWithAuto(v1);
}