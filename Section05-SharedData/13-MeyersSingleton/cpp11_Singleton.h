/*
  Singleton class definition based on C++11
  (Meyers Singleton) guarantees about initializing
  static variables
*/
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton
{
public:
  // Default constructor
  Singleton() 
  {
    std::cout << "Initializing Singleton" << "\n";
  }

  // Deep copy constructor and copy assignment operator are deleted
  Singleton(const Singleton &) = delete;
  Singleton& operator=(const Singleton &) = delete;

  // Move constructor and move assignment operator are deleted
  Singleton(Singleton &&) = delete;
  Singleton& operator=(Singleton &&) = delete;
};

// Function to obtain the Singleton object
Singleton & getSingleton();

#endif