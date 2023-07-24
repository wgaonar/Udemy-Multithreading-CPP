/*
  Dining philosophers problem (part 1)
  5 philosophers sit at a round table which has 5 forks on it.
  A philosopher has a fork at each side of them.
  A philosopher can only eat if they can pick up both forks.
  If a philosopher picks up the fork on their right,
  that prevents the next philosopher from picking up their left fork.

  All the philosophers pick up their left fork at the same time
  They wait to pick up their right fork (which is also their neighbour's left fork)
  Their neighbour is waiting to pick up their own right fork
  All the philosophers are waiting for their neighbour

  The philosophers are blocked indefinitely.
  Deadlock
*/
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<string>

using namespace std::literals;

// Some data about the problem
constexpr int n_forks = 5;
constexpr int n_philosophers = n_forks;
std::string names[n_philosophers] {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[n_philosophers] {0};

/*
  A philosopher who has not picked up both forks is thinking
  and he thinks in multiples of 2 seconds
*/
constexpr auto think_time {2s};

/*
  A philosopher has picked up both forks is eating
  and he eats in multiples of 1 second
*/
constexpr auto eat_time {1s};

/*
  A mutex prevents more than one philosopher picking up the same fork
  A philosopher thread can only pick up a fork, if it can lock the
  corresponding mutex
*/
std::mutex fork_mutex[n_forks];

// Mutex to prevent the output from scrambling up
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with a fork
void print(int n, const std::string& str, int fork_no)
{
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << fork_no << "\n";
}

// Philosopher's state
void print(int n, const std::string& str)
{
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << "\n";

}

// Thread which represent a dining philosopher
void dine(int n_philo)
{
  /* 
    Philosopher A has fork 0 on their left and fork 1 on their right
    Philosopher B has fork 1 on their left and fork 2 on their right
    ...
    Philosopher E has fork 4 on their left and fork 0 on their right
    Each philosopher must pick up their left fork first 
  */
  int lfork = n_philo;
  int rfork = (n_philo + 1) % n_forks;

  print(n_philo, "\'s left fork is number ", lfork);
  print(n_philo, "\'s right fork is number ", rfork);
  print(n_philo, " is thinking...");

  std::this_thread::sleep_for(think_time);

  // Make an attempt to eat
  print(n_philo, " reaches for fork number ", lfork);

  // Try to pick up the left fork
  fork_mutex[lfork].lock();

  // Succeeded - now try to pick up the right fork
  print(n_philo, " picks up fork ", lfork);
  print(n_philo, " is thinking...");

  // Time to think
  std::this_thread::sleep_for(think_time);

  print(n_philo, " reaches for fork number ", rfork);

  fork_mutex[rfork].lock();

  // Succeeded - this philosopher can now eat
  print(n_philo, " picks up fork ", rfork);
  print(n_philo, " is eating...");

  // Time to eat
  std::this_thread::sleep_for(eat_time);

  print(n_philo, " puts down fork ", lfork);
  print(n_philo, " puts down fork ", rfork);
  print(n_philo, " is thinking...");

  fork_mutex[lfork].unlock();
  fork_mutex[rfork].unlock();

  // Go back to thinking
  std::this_thread::sleep_for(think_time);
}

int main()
{
  // Start a separate thread for each philosopher
  std::vector<std::thread> philos;

  for (size_t i = 0; i < n_philosophers; i++)
  {
    philos.push_back(std::move(std::thread{dine,i}));
  }

  for (auto & philo: philos)
  {
    philo.join();
  }
  
  // How many times were the philosophers able to eat?
  for (size_t i = 0; i < n_philosophers; i++)
  {
    std::cout << " Philosopher " << names[i];
    std::cout << " had " << mouthfuls[i] << " mouthfuls" << "\n";
  }
  
}