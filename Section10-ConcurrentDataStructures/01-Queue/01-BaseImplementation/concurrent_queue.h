#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>

class concurrent_queue_exception : public std::runtime_error
{
public:
  // Default constructor
  concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
  
  // Overload constructor
  concurrent_queue_exception(const char *str) : std::runtime_error(str) {}
};

template <class T>
class concurrent_queue
{
private:
  std::mutex m;
  std::queue<T> q;
public:
  // Explicitly Default constructor
  concurrent_queue() = default;

  // Overload push() method with a lock_guard() statement
  void push (T value)
  {
    std::lock_guard<std::mutex> lg(m);
    q.push(value);
  }
  
  /*
    Overload pop() method with a lock_guard() statement
    Use T& by reference to save the value in the queue 
    before the pop 
  */
  void pop (T& value)
  {
    std::lock_guard<std::mutex> lg(m);
    if (q.empty())
    {
      throw concurrent_queue_exception("Queue is empty");
    }
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
    std::lock_guard<std::mutex> lg(m);
    if (q.empty())
    {
      throw concurrent_queue_exception("Queue is empty");
    }
    T value = q.front();
    q.pop();
    return value;
  }
};

#endif