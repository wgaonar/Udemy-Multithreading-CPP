#ifndef CONCURRENT_QUEUE_CV_H
#define CONCURRENT_QUEUE_CV_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class concurrent_queue
{
private:
  std::mutex m;
  std::queue<T> q;
  std::condition_variable cv;
public:
  // Explicitly Default constructor
  concurrent_queue() = default;

  // Overload push() method with a lock_guard() statement
  void push (T value)
  {
    std::lock_guard<std::mutex> lg(m);
    q.push(value);

    // Notify the condition variable
    cv.notify_one();
  }
  
  /*
    Overload pop() method with a lock_guard() statement
    Use T& by reference to save the value in the queue 
    before the pop 
  */
  void pop (T& value)
  {
    std::unique_lock<std::mutex> ul(m);
    // Call wait() will unlock the mutex and make this thread
    cv.wait(ul,[this]{ return !q.empty(); });
    value = q.front();
    q.pop();
  }

  /*
    Overload pop() method with a lock_guard() statement
    Using a return T type value instead of saving it by 
    reference.
  */
  T pop ()
  {
    std::unique_lock<std::mutex> ul(m);
    /* 
      Call wait() will unlock the mutex
      Keep waiting while the queue is empty 
    */
    cv.wait(ul,[this]{ return !q.empty(); });
    T value = q.front();
    q.pop();
    return value;
  }
};

#endif