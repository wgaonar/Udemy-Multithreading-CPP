/* 
  Use std::packaged_task
*/

#include <iostream>
#include <future>

int main()
{
  /* 
    Packaged task with lambda expression as task function
    The argument is the signature of the function
    e.g. parameters: int, int
    return: int
    The parameter of the associated promise is the return type. e.g. int
  */
  std::packaged_task<int(int, int)> pck_task([](int a, int b){return a + b;});

  // Create the future for the associated packaged_task's promise
  std::future<int> fut = pck_task.get_future();

  // Create the thread to run the task
  std::thread thr(std::move(pck_task), 6, 7);

  // Wait to complete the task
  thr.join();

  std::cout << "6 + 7 is: " << fut.get() << "\n";
}