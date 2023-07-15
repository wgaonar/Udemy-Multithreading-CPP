// Example of lambda expression with lambda-local variables
#include <iostream>

int main()
{
  // y is local to the lambda body
  auto add_two = [y = 2] (int x) {
    return x + y;
  };
  std::cout << "Calling add_two(2) gives: " << add_two(2) << std::endl; // 4
  std::cout << "Calling add_two(3) gives: " << add_two(3) << std::endl; // 5

  // z is a local variable in the containing scope of the lambda
  int z = 1;

  // y is local to the lambda body
  // It is initialized using the local variable z
  auto add_z_plus_one = [y = z + 1] (int x) {
    return x + y;
  };
  std::cout << "Calling add_z_plus_one(2) gives: " << add_z_plus_one(2) << std::endl; // 4
  std::cout << "Calling add_z_plus_one(3) gives: " << add_z_plus_one(3) << std::endl; // 5

}