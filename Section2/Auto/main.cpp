// Example of loop using the "auto" type specifier
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> vec{4, 2, 3, 5, 1};

  for (auto it = vec.begin(); it != vec.end(); it++)
  {
    *it += 10;
  }

  /* 
    Show the vector elements. Note the use of vec.cbegin()
    and vec.cend()
  */
  std::cout << "Vector elements: ";
  for (auto it = vec.cbegin(); it != vec.cend(); it++)
  {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}