/* 
  Application for a real case of using std::transform_reduce() 
  algorithm overloading the binary operators "*" and "+.
  It is the equivalent of std::inner_product() but 
  with execution polices.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

template <typename t>
void DisplayVectorWithAuto (const std::vector <t> &inVector) 
{
  for (auto element : inVector) {
      std::cout << element << ", ";
  }
  std::cout << "\n";
}

int main()
{
  // Create a vector
  std::vector<double> expected{0.1, 0.2, 0.3, 0.4, 0.5};
  std::vector<double> actual{0.09, 0.22, 0.27, 0.41, 0.52};

  double initial_value {0.0};

  // Calculate the inner product between two vectors
  auto max_diff = std::transform_reduce(expected.cbegin(),expected.cend(),
                                      actual.cbegin(), initial_value,
                                      [](auto a, auto b){ return std::max(a,b); }, // Reduce operation (Replace +)
                                      [](auto l, auto r){ return std::fabs(r-l); }  // Transform operation (Replace *)
  );

  // Display original vector expected
  std::cout << "First input vector: " << "\n";
  DisplayVectorWithAuto(expected);
  
  // Display the vector actual
  std::cout << "Second input vector: " << "\n";
  DisplayVectorWithAuto(actual);

  std::cout << "Max difference is : " 
            << max_diff << "\n";
}