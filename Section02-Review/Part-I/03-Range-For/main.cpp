// Example of range-for loop
#include <iostream>
#include <vector>

// Function to display a vector of type int
void display_vector(const std::vector<int> &vec) 
{
  std::cout << "[ ";
  for (const auto &elem: vec)
    std::cout << elem << " ";
  std::cout <<  "]"<< std::endl;
}

int main()
{
  std::vector<int> vec{4, 2, 3, 5, 1};

  std::cout << "Vector elements before: ";
  for (auto i : vec) // Disadvantage: Creates a copy of each vector element 
  {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  // We need to use a reference to modify the elements
  for (auto& i : vec)
  {
    i += 10;
  }

  // Display the vector using a function
  std::cout << "Vector elements after: ";
  display_vector(vec);
}